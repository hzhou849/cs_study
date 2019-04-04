/*
 * Kontron driver for Fintec ITE8516 controller for Kontron KT boards
 *
 * This driver supports the following functionality:
 *  - two temperature sensors;
 *  - one voltage sensor;
 *  - four fans(manual pwm, automatic rpm and thermal cruise modes);
 *  - 18xGPIO pins with alternative functions (4xDAC, 4xPWM, 5xADC);
 *  - watchdog;
 *  - SMBus.
 *
 * Copyright (C) 2012 Kontron AG
 * Author: Andrey Rusalin, KGSC Moscow
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/io.h>
#include <linux/errno.h>
#include <linux/platform_device.h>
#include <linux/delay.h>
#include <linux/gpio.h>
#include <linux/acpi.h>

#include <linux/hwmon.h>
#include <linux/hwmon-sysfs.h>
#include <linux/err.h>
#include <linux/init.h>
#include <linux/jiffies.h>
#include <linux/mutex.h>
#include <linux/sysfs.h>
#include <linux/watchdog.h>
#include <linux/i2c.h>

#define DRV_NAME "ite8516k"

#define ITE8516K_REG_CMD	1
#define ITE8516K_REG_STATUS	1
#define ITE8516K_REG_DATA	0

#define ITE8516K_STATUS_OBF	0x01
#define ITE8516K_STATUS_IBF	0x02
#define ITE8516K_STATUS_BMODE	0x80

#define ITE8516K_IOCMD_ERROR	0x80000000
#define ITE8516K_IODATA_ERROR	0x40000000
#define ITE8516K_IO_ERROR	(ITE8516K_IODATA_ERROR|ITE8516K_IOCMD_ERROR)

#define ITE8516K_CMD_GPIO_GETDIR	0x30
#define ITE8516K_CMD_GPIO_SETDIR	0x31
#define ITE8516K_CMD_GPIO_GET		0x32
#define ITE8516K_CMD_GPIO_SET		0x33
#define ITE8516K_CMD_GPIO_GETW		0x34
#define ITE8516K_CMD_GPIO_SETW		0x35

#define ITE8516K_GPIO_SET_INPUT		0x00
#define ITE8516K_GPIO_SET_OUTPUT	0x01
#define ITE8516K_GPIO_SET_ALTF		0x02
#define ITE8516K_GPIO_SET_PULLDOWN_MASK	0xfb
#define ITE8516K_GPIO_SET_PULLUP	0x08

#define ITE8516K_GPIO_NUMBER	18
#define ITE8516K_DAC_START	0
#define ITE8516K_DAC_NUMBER	4
#define ITE8516K_PWM_START	4
#define ITE8516K_PWM_NUMBER	4
#define ITE8516K_ADC_START	8
#define ITE8516K_ADC_NUMBER	5
#define ITE8516K_FAN_NUMBER	4
#define ITE8516K_TEMP_NUMBER	2
#define ITE8516K_INPUT_NUMBER	1

#define ITE8516K_CMD_INFO		0x01
#define ITE8516K_CMD_INFO2		0x02
#define ITE8516K_CMD_SET_WATCHDOG	0x08
#define ITE8516K_CMD_SET_FANMODE	0x11
#define ITE8516K_CMD_GET_FANRPM		0x1d
#define ITE8516K_CMD_GET_FANPWM		0x12
#define ITE8516K_CMD_SET_FANPWM		0x13
#define ITE8516K_CMD_GET_FANSPEED	0x14
#define ITE8516K_CMD_SET_FANSPEED	0x15
#define ITE8516K_CMD_GET_AUTOTEMP	0x16
#define ITE8516K_CMD_SET_AUTOTEMP	0x17
#define ITE8516K_CMD_GET_FANDIV		0x18
#define ITE8516K_CMD_SET_FANDIV		0x19
#define ITE8516K_CMD_GET_CPUTEMP	0x20
#define ITE8516K_CMD_GET_12V		0x28

#define ITE8516K_FANMODE_AUTO		0x80
#define ITE8516K_FANMODE_PWM		0x01
#define ITE8516K_FANMODE_SPEED		0x02
#define ITE8516K_FANMODE_CRUSE		0x03
#define ITE8516K_DEFAULT_FANDIV		0x01

#define ITE8516K_CMD_SMBUS_QUICK_COM	0x40
#define ITE8516K_CMD_SMBUS_SEND_BYTE	0x41
#define ITE8516K_CMD_SMBUS_RECEIVE_BYTE	0x42
#define ITE8516K_CMD_SMBUS_WRITE_BYTE	0x43
#define ITE8516K_CMD_SMBUS_READ_BYTE	0x44
#define ITE8516K_CMD_SMBUS_WRITE_WORD	0x45
#define ITE8516K_CMD_SMBUS_READ_WORD	0x46
#define ITE8516K_CMD_SMBUS_WRITE_BLOCK	0x48
#define ITE8516K_CMD_SMBUS_READ_BLOCK	0x49

#define OP_INPUT	1
#define OP_MIN		2
#define OP_MAX		3
#define OP_CTRL		4
#define OP_NAME		5
#define OP_DAC		6
#define OP_ADC		7
#define OP_PWM		8

struct ite8516k_fan {
	char	name[20];
	u32	min;
	u32	max;
	u32	mode;
	u32	sens;
	u32	div;
};

struct ite8516k_temp {
	char	name[20];
	u32	min;
	u32	max;
	u32	crit;
};

struct ite8516k_input {
	char	name[20];
	u32	value;
};

static bool  gpio_altf[ITE8516K_GPIO_NUMBER] = {0};
module_param_array(gpio_altf, bool, NULL, 0);
MODULE_PARM_DESC(gpio_altf, "Setup alternative function for gpio (describe all pins)");

static DEFINE_SPINLOCK(ite8516k_io_lock);
static DEFINE_SPINLOCK(ite8516k_gpio_lock);
static DEFINE_SPINLOCK(ite8516k_hwmon_lock);

u32 ite8516k_baddr;
static struct device *ite8516k_hwmon;
static struct i2c_adapter ite8516k_adapter;

struct ite8516k_fan ite8516k_fan_data[ITE8516K_FAN_NUMBER] = {
	{
		.name = "CPU-Fan",
		.min = 500,
		.max = 9000,
		.mode = ITE8516K_FANMODE_AUTO,
		.sens = 0,
		.div = 1,
	},
	{
		.name = "SYS-Fan",
		.min = 500,
		.max = 9000,
		.mode = ITE8516K_FANMODE_AUTO,
		.sens = 0,
		.div = 1,
	},
	{
		.name = "Fan3",
		.min = 500,
		.max = 9000,
		.mode = ITE8516K_FANMODE_AUTO,
		.sens = 0,
		.div = 1,
	},
	{
		.name = "Fan4",
		.min = 500,
		.max = 9000,
		.mode = ITE8516K_FANMODE_AUTO,
		.sens = 0,
		.div = 1,
	},

};

struct ite8516k_temp ite8516k_temp_data[ITE8516K_TEMP_NUMBER] = {
	{
		.name = "CPU-Temp",
		.min = -1,
		.max = 0,
		.crit = 90,
	},
	{
		.name = "SYS-Temp",
		.min = -1,
		.max = 0,
		.crit = 90,
	}
};

struct ite8516k_input ite8516k_input_data[ITE8516K_INPUT_NUMBER] = {
	{
		.name = "12V",
		.value = 0,
	},
};

/* fan_target will store either target PWM, RPM or temperature depending on
 * current fan mode */
struct ite8516k_resume {
	u32 gpio_directions;
	u32 gpio_values;
	u16 fan_target[ITE8516K_FAN_NUMBER];
	s8  fan_div[ITE8516K_FAN_NUMBER];
	u8 dac[ITE8516K_DAC_NUMBER];
	u8 pwm[ITE8516K_PWM_NUMBER];
};

static struct ite8516k_resume ite8516k_resume_data;

static struct gpio kt_cpld_gpios[] = {
	{0, GPIOF_EXPORT_DIR_CHANGEABLE, "GPIO0"},
	{1, GPIOF_EXPORT_DIR_CHANGEABLE, "GPIO1"},
	{2, GPIOF_EXPORT_DIR_CHANGEABLE, "GPIO2"},
	{3, GPIOF_EXPORT_DIR_CHANGEABLE, "GPIO3"},
	{4, GPIOF_EXPORT_DIR_CHANGEABLE, "GPIO4"},
	{5, GPIOF_EXPORT_DIR_CHANGEABLE, "GPIO5"},
	{6, GPIOF_EXPORT_DIR_CHANGEABLE, "GPIO6"},
	{7, GPIOF_EXPORT_DIR_CHANGEABLE, "GPIO7"},
	{8, GPIOF_DIR_IN|GPIOF_EXPORT_DIR_FIXED, "GPI8"},
	{9, GPIOF_DIR_IN|GPIOF_EXPORT_DIR_FIXED, "GPI9"},
	{10, GPIOF_DIR_IN|GPIOF_EXPORT_DIR_FIXED, "GPI10"},
	{11, GPIOF_DIR_IN|GPIOF_EXPORT_DIR_FIXED, "GPI11"},
	{12, GPIOF_DIR_IN|GPIOF_EXPORT_DIR_FIXED, "GPI12"},
	{13, GPIOF_EXPORT_DIR_CHANGEABLE, "GPIO13"},
	{14, GPIOF_EXPORT_DIR_CHANGEABLE, "GPIO14"},
	{15, GPIOF_EXPORT_DIR_CHANGEABLE, "GPIO15"},
	{16, GPIOF_EXPORT_DIR_CHANGEABLE, "GPIO16"},
	{17, GPIOF_EXPORT_DIR_CHANGEABLE, "GPIO17"},
};

static inline u32 ite8516k_wait_obf(void)
{
	u32 timeout = 10000;

	while ((!(inb(ite8516k_baddr+ITE8516K_REG_STATUS)&ITE8516K_STATUS_OBF))
								&& (--timeout));
	return timeout;
}

static inline  u32 ite8516k_wait_ibf(void)
{
	u32 timeout = 10000;

	while ((inb(ite8516k_baddr+ITE8516K_REG_STATUS)&ITE8516K_STATUS_IBF)
								&& (--timeout));
	return timeout;
}

static u32 ite8516k_send_cmd(u8 cmd)
{
	int timeout = 10000;

	if (!ite8516k_wait_ibf())
		return ITE8516K_IOCMD_ERROR;

	while ((inb(ite8516k_baddr+ITE8516K_REG_STATUS)&ITE8516K_STATUS_BMODE)
								&& (timeout)) {
		outb(0x00, ite8516k_baddr+ITE8516K_REG_CMD);
		if (!ite8516k_wait_ibf())
			return ITE8516K_IOCMD_ERROR;
		inb(ite8516k_baddr+ITE8516K_REG_DATA);
		timeout--;
	}
	if (!timeout)
		return ITE8516K_IOCMD_ERROR;

	outb(cmd, ite8516k_baddr+ITE8516K_REG_CMD);

	return 0;
}

static inline  u32 ite8516k_in(void)
{
	if (!ite8516k_wait_obf())
		return ITE8516K_IODATA_ERROR;

	return inb(ite8516k_baddr+ITE8516K_REG_DATA);
}

static inline  u32 ite8516k_out(u8 data)
{
	if (!ite8516k_wait_ibf())
		return ITE8516K_IODATA_ERROR;

	outb(data, ite8516k_baddr+ITE8516K_REG_DATA);
	return 0;
}

#define ite8516k_inb(__cmd) ite8516k_inX(__cmd, 1)
#define ite8516k_inw(__cmd) ite8516k_inX(__cmd, 2)
#define ite8516k_inwb(__cmd) ite8516k_inX(__cmd, 3)

static u32 ite8516k_inX(u8 cmd, u8 size)
{
	u32 data = 0;
	int i;

	spin_lock(&ite8516k_io_lock);

	data |= ite8516k_send_cmd(cmd);
	if (data)
		goto exit;

	for (i = 0; i < size; i++) {
		data |= ite8516k_in() << (i*8);
		if (data&ITE8516K_IODATA_ERROR)
			break;
	}

	udelay(10);
exit:
	spin_unlock(&ite8516k_io_lock);
	return data;
}

#define ite8516k_outb(__cmd, __data) ite8516k_outX(__cmd, __data, 1)
#define ite8516k_outw(__cmd, __data) ite8516k_outX(__cmd, __data, 2)
#define ite8516k_outwb(__cmd, __data) ite8516k_outX(__cmd, __data, 3)
#define ite8516k_outww(__cmd, __data) ite8516k_outX(__cmd, __data, 4)

static u32 ite8516k_outX(u8 cmd, u32 data, u8 size)
{
	int i;
	u32 err;
	spin_lock(&ite8516k_io_lock);

	err = ite8516k_send_cmd(cmd);
	if (err)
		goto exit;

	for (i = 0; i < size; i++) {
		err = ite8516k_out((data>>(i*8))&0xFF);
		if (err&ITE8516K_IODATA_ERROR)
			break;
	}

	udelay(10);
exit:
	spin_unlock(&ite8516k_io_lock);
	return err;
}

#define ite8516k_outb_inb(__cmd, __data) \
	ite8516k_outX_inX(__cmd, __data, 1, 1)
#define ite8516k_outb_inw(__cmd, __data) \
	ite8516k_outX_inX(__cmd, __data, 1, 2)
#define ite8516k_outb_inwb(__cmd, __data) \
	ite8516k_outX_inX(__cmd, __data, 1, 3)
#define ite8516k_outw_inb(__cmd, __data) \
	ite8516k_outX_inX(__cmd, __data, 2, 1)
#define ite8516k_outwb_inb(__cmd, __data) \
	ite8516k_outX_inX(__cmd, __data, 3, 1)
#define ite8516k_outww_inb(__cmd, __data) \
	ite8516k_outX_inX(__cmd, __data, 4, 1)
#define ite8516k_outw_inw(__cmd, __data) \
	ite8516k_outX_inX(__cmd, __data, 2, 2)
#define ite8516k_outw_inwb(__cmd, __data) \
	ite8516k_outX_inX(__cmd, __data, 2, 3)

static u32 ite8516k_outX_inX(u8 cmd, u32 data_out, u8 size_out, u8 size_in)
{
	u32 data_in = 0;
	u8 i;

	spin_lock(&ite8516k_io_lock);

	data_in = ite8516k_send_cmd(cmd);
	if (data_in)
		goto exit;

	for (i = 0; i < size_out; i++) {
		data_in |= ite8516k_out((data_out>>(i*8))&0xFF);
		if (data_in&ITE8516K_IODATA_ERROR)
			break;
	}

	for (i = 0; i < size_in; i++) {
		data_in |= ite8516k_in()<<(i*8);
		if (data_in&ITE8516K_IODATA_ERROR)
			break;
	}
	udelay(10);

exit:
	spin_unlock(&ite8516k_io_lock);
	return data_in;
}


/*---------------------------GPIO--------------------------------------------*/

unsigned ite8516k_gpio_to_offset(unsigned num)
{
	return num;
}

static int ite8516k_gpio_request(struct gpio_chip *gc, unsigned gpio_num)
{
	if (gpio_altf[gpio_num] == TRUE)
		return -EINVAL;

	return 0;
}

static int ite8516k_gpio_direction_in(struct gpio_chip *gc, unsigned  gpio_num)
{
	u16 data;

	ite8516k_resume_data.gpio_directions &=
					 (0xFFFFFFFF & ~(1 << gpio_num));
	spin_lock(&ite8516k_gpio_lock);

	data = ite8516k_gpio_to_offset(gpio_num) | (((ITE8516K_GPIO_SET_INPUT |
		ITE8516K_GPIO_SET_PULLUP) & ITE8516K_GPIO_SET_PULLDOWN_MASK )<<8);

	if (ite8516k_outw(ITE8516K_CMD_GPIO_SETDIR, data)&ITE8516K_IO_ERROR)
		pr_err("%s Error setting of GPIO\n", DRV_NAME);

	spin_unlock(&ite8516k_gpio_lock);
	return 0;
}

static int ite8516k_gpio_direction_out(struct gpio_chip *gc,
						unsigned gpio_num, int val)
{
	u16 data;

	/* If gpio do not support changing of direction */
	if (!(kt_cpld_gpios[gpio_num].flags&GPIOF_EXPORT_CHANGEABLE))
		return -EINVAL;

	ite8516k_resume_data.gpio_directions |= (1 << gpio_num);
	spin_lock(&ite8516k_gpio_lock);

	data = ite8516k_gpio_to_offset(gpio_num)
					| (ITE8516K_GPIO_SET_OUTPUT<<8);

	if (ite8516k_outw(ITE8516K_CMD_GPIO_SETDIR, data)&ITE8516K_IO_ERROR)
		pr_err("%s Error setting of GPIO\n", DRV_NAME);

	spin_unlock(&ite8516k_gpio_lock);
	return 0;
}

static u8 ite8516k_gpio_get_data(unsigned gpio_num)
{
	u8 data;

	spin_lock(&ite8516k_gpio_lock);

	data = ite8516k_outb_inb(ITE8516K_CMD_GPIO_GET, gpio_num);

	if (data&ITE8516K_IO_ERROR)
		pr_err("%s Error setting of GPIO\n", DRV_NAME);

	spin_unlock(&ite8516k_gpio_lock);

	return data;
}

static u32 ite8516k_gpio_get_adc(unsigned gpio_num)
{
	u32 data;

	spin_lock(&ite8516k_gpio_lock);

	/* adc on ITE is 10-bit, so we take only 10 bit */
	data = 0x000003FF & ite8516k_outb_inw(ITE8516K_CMD_GPIO_GETW, gpio_num);

	if (data&ITE8516K_IO_ERROR)
		pr_err("%s Error setting of GPIO\n", DRV_NAME);

	spin_unlock(&ite8516k_gpio_lock);

	return data;
}

static int ite8516k_gpio_get(struct gpio_chip *gc, unsigned gpio_num)
{
	u8 index;
	u32 data;

	index = ite8516k_gpio_to_offset(gpio_num);

	data = ite8516k_gpio_get_data(index) & 1;

	return data;
}

static void ite8516k_gpio_set_data(unsigned gpio_num, u32 data)
{
	spin_lock(&ite8516k_gpio_lock);

	data = (data<<8) | gpio_num;
	data = ite8516k_outw(ITE8516K_CMD_GPIO_SET, data);

	if (data&ITE8516K_IO_ERROR)
		pr_err("%s Error setting of GPIO\n", DRV_NAME);

	spin_unlock(&ite8516k_gpio_lock);

	return;
}

static void ite8516k_gpio_set(struct gpio_chip *gc, unsigned gpio_num, int val)
{
	u8 index;
	u32 data;

	index = ite8516k_gpio_to_offset(gpio_num);

	data = ite8516k_gpio_get_data(index);
	if (data&ITE8516K_IO_ERROR)
		return;

	if (val)
		data |= 1;
	else
		data &= 0xFE;

	ite8516k_gpio_set_data(index, data);

	return;
}

static struct gpio_chip ite8516k_gpio = {
	.label			= DRV_NAME,
	.owner			= THIS_MODULE,
	.request		= ite8516k_gpio_request,
	.direction_input	= ite8516k_gpio_direction_in,
	.get			= ite8516k_gpio_get,
	.direction_output	= ite8516k_gpio_direction_out,
	.set			= ite8516k_gpio_set,
	.base                   = 0,
	.ngpio                  = ITE8516K_GPIO_NUMBER,
};

static void ite8516k_gpio_altf_enable(int gpio_num)
{
	u16 data;

	spin_lock(&ite8516k_gpio_lock);

	data = ite8516k_gpio_to_offset(gpio_num)
					| (ITE8516K_GPIO_SET_ALTF<<8);

	if (ite8516k_outw(ITE8516K_CMD_GPIO_SETDIR, data) & ITE8516K_IO_ERROR)
		pr_err("%s Error setting of GPIO\n", DRV_NAME);

	spin_unlock(&ite8516k_gpio_lock);

	return;
}


/*---------------------------HW MON-----------------------------------------*/

static ssize_t show_temp(struct device *dev, struct device_attribute *attr,
				char *buf)
{
	struct sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	int data;

	switch (sattr->nr) {
	case OP_INPUT:
		data = ite8516k_outb_inw(ITE8516K_CMD_GET_CPUTEMP + 
							2 * sattr->index, 0);
		if (data&ITE8516K_IO_ERROR)
			data = 0;
		else
			data = (data * 1000) / 64;
		if (ite8516k_temp_data[sattr->index].min > data)
			ite8516k_temp_data[sattr->index].min = data;
		if (ite8516k_temp_data[sattr->index].max < data)
			ite8516k_temp_data[sattr->index].max = data;
		break;
	case OP_MAX:
		data = ite8516k_temp_data[sattr->index].max;
		break;
	case OP_MIN:
		data = ite8516k_temp_data[sattr->index].min;
		break;
	case OP_CTRL:
		data = ite8516k_temp_data[sattr->index].crit;
		break;
	case OP_NAME:
		return sprintf(buf, "%s\n",
					ite8516k_temp_data[sattr->index].name);
		break;
	default:
		data = 0;
		break;
	}

	return sprintf(buf, "%d\n", data);
}

static ssize_t set_temp(struct device *dev, struct device_attribute *attr,
			const char *buf, size_t count)
{
	struct sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	long int val;

	if (strict_strtol(buf, 10, &val))
		return -EINVAL;

	spin_lock(&ite8516k_hwmon_lock);
	switch (sattr->nr) {
	case OP_CTRL:
		ite8516k_temp_data[sattr->index].crit = val;
		break;
	default:
		break;
	}

	spin_unlock(&ite8516k_hwmon_lock);

	return count;
}

static ssize_t show_fan(struct device *dev, struct device_attribute *attr,
			 char *buf)
{
	struct sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	u32 data = 0;

	switch (sattr->nr) {
	case OP_INPUT:
		data = ite8516k_outb_inw(ITE8516K_CMD_GET_FANRPM, sattr->index);
		if (data&ITE8516K_IO_ERROR)
			data = 0;
		break;
	case OP_MAX:
		data = ite8516k_fan_data[sattr->index].max;
		break;
	case OP_MIN:
		data = ite8516k_fan_data[sattr->index].min;
		break;
	case OP_NAME:
		return sprintf(buf, "%s\n",
					ite8516k_fan_data[sattr->index].name);
		break;
	default:
		break;
	}

	return sprintf(buf, "%d\n", data);
}

static ssize_t show_pwm(struct device *dev, struct device_attribute *attr,
			char *buf)
{
	struct sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	u32 data;

	if (ite8516k_fan_data[sattr->index].mode == ITE8516K_FANMODE_SPEED) {
		data = ite8516k_outb_inw(ITE8516K_CMD_GET_FANSPEED,
								sattr->index);
		if (data&ITE8516K_IO_ERROR)
			data = 0;
	} else {
		data = ite8516k_outb_inb(ITE8516K_CMD_GET_FANPWM, sattr->index);
		if (data&ITE8516K_IO_ERROR)
			data = 0;
	}

	return sprintf(buf, "%d\n", data);
}

static ssize_t set_pwm(struct device *dev, struct device_attribute *attr,
			const char *buf, size_t count)
{
	struct sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	unsigned long val;
	u32 data;

	if (strict_strtoul(buf, 10, &val))
		return -EINVAL;

	if (ite8516k_fan_data[sattr->index].mode == ITE8516K_FANMODE_SPEED) {
		data = ((val&0xFFFF) << 8) | (sattr->index&0xFF);
		if (ite8516k_outwb(ITE8516K_CMD_SET_FANSPEED, data)&ITE8516K_IO_ERROR)
			count = 0;
	} else {
		data = ((val&0xFF) << 8) | (sattr->index&0xFF);
		if (ite8516k_outw(ITE8516K_CMD_SET_FANPWM, data)&ITE8516K_IO_ERROR)
			count = 0;
	}

	return count;
}

static ssize_t show_pwmmode(struct device *dev, struct device_attribute *attr,
			    char *buf)
{
	struct sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	u32 data;

	switch (ite8516k_fan_data[sattr->index].mode) {
	case ITE8516K_FANMODE_PWM:
		data = 1;
		break;
	case ITE8516K_FANMODE_CRUSE:
		data = 2;
		break;
	case ITE8516K_FANMODE_SPEED:
		data = 3;
		break;
	case ITE8516K_FANMODE_AUTO:
	default:
		data = 0;
		break;
	}
	return sprintf(buf, "%d\n", data);
}

static ssize_t set_pwmmode(struct device *dev, struct device_attribute *attr,
			const char *buf, size_t count)
{
	struct sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	unsigned long val;
	u32 data;

	if (strict_strtoul(buf, 10, &val))
		return -EINVAL;

	switch (val) {
	case 1:
		val = ITE8516K_FANMODE_PWM;
		break;
	case 2:
		val = ITE8516K_FANMODE_CRUSE;
		break;
	case 3:
		val = ITE8516K_FANMODE_SPEED;
		break;
	default:
		val = ITE8516K_FANMODE_AUTO;
		break;
	}

	ite8516k_fan_data[sattr->index].mode = val;
	data = ((val&0xFF) << 8) | (sattr->index&0xFF);

	if (ite8516k_outw(ITE8516K_CMD_SET_FANMODE, data)&ITE8516K_IO_ERROR)
		count = 0;

	return count;
}

static ssize_t show_pwmauto(struct device *dev, struct device_attribute *attr,
			    char *buf)
{
	struct sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	u32 data;

	if (sattr->nr == OP_CTRL)
		return sprintf(buf, "%d\n",
					ite8516k_fan_data[sattr->index].sens);

	data = ite8516k_outb_inw(ITE8516K_CMD_GET_AUTOTEMP, sattr->index);
	if (data&ITE8516K_IO_ERROR)
		data = 0;
	else
		data = (data * 1000) / 64;

	return sprintf(buf, "%d\n", data);
}

static ssize_t set_pwmauto(struct device *dev, struct device_attribute *attr,
				const char *buf, size_t count)
{
	struct sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	unsigned long val;
	u32 data;

	if (strict_strtoul(buf, 10, &val))
		return -EINVAL;

	if (sattr->nr == OP_CTRL) {
		ite8516k_fan_data[sattr->index].sens = val;
		return count;
	}

	val = val * 64 / 1000;
	data = ((val&0xFFFF) << 8) | (sattr->index&0xFF);
	if (ite8516k_outwb(ITE8516K_CMD_SET_AUTOTEMP, data)&ITE8516K_IO_ERROR)
		count = 0;

	return count;
}

static ssize_t show_pwmctrl(struct device *dev, struct device_attribute *attr,
			    char *buf)
{
	struct sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	u32 data = 0;

	if (sattr->nr == OP_CTRL) {
		data = ite8516k_outb_inb(ITE8516K_CMD_GET_FANDIV, sattr->index);
		if (data&ITE8516K_IO_ERROR)
			data = -1;
	}

	return sprintf(buf, "%d\n", data);
}

static ssize_t set_pwmctrl(struct device *dev, struct device_attribute *attr,
			const char *buf, size_t count)
{
	struct sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	unsigned long val;
	u32 data;

	if (strict_strtoul(buf, 10, &val))
		return -EINVAL;

	if (sattr->nr == OP_CTRL) {
		data = ((val&0xFF) << 8) | (sattr->index&0xFF);
		if (ite8516k_outw(ITE8516K_CMD_SET_FANDIV, data)&ITE8516K_IO_ERROR)
			count = 0;
	}

	return count;
}

static ssize_t show_input(struct device *dev, struct device_attribute *attr,
				char *buf)
{
	struct sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	int data;

	switch (sattr->nr) {
	case OP_INPUT:
		data = ite8516k_outb_inw(ITE8516K_CMD_GET_12V, sattr->index);
		if (data&ITE8516K_IO_ERROR)
			data = 0;
		else
			data &= 0x0FFF ;
		ite8516k_input_data[sattr->index].value = data;
		break;
	case OP_NAME:
		return sprintf(buf, "%s\n",
					ite8516k_input_data[sattr->index].name);
		break;
	default:
		data = 0;
		break;
	}

	return sprintf(buf, "%d\n", data);
}


static ssize_t show_name(struct device *dev, struct device_attribute *attr,
			 char *buf)
{
	return sprintf(buf, DRV_NAME"\n");
}


static ssize_t set_altf(struct device *dev, struct device_attribute *attr,
			const char *buf, size_t count)
{
	struct sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	unsigned long val;
	u16 data, index;
	int err;

	err = kstrtoul(buf, 10, &val);
	if (err)
		return -EINVAL;

	if (val > 0xFF)
		return -EINVAL;

	if (sattr->nr == OP_DAC)
		index = ite8516k_gpio_to_offset(sattr->index
							+ ITE8516K_DAC_START);

	else /* sattr->nr == OP_PWM */
	{
		index = ite8516k_gpio_to_offset(sattr->index
							+ ITE8516K_PWM_START);
		val = val * 100 / 255;
	}

	spin_lock(&ite8516k_gpio_lock);

	data = (val<<8) | index;
	data = ite8516k_outw(ITE8516K_CMD_GPIO_SET, data);

	if (data&ITE8516K_IO_ERROR) {
		pr_err("%s Error setting of GPIO\n", DRV_NAME);
		count = 0;
	}

	spin_unlock(&ite8516k_gpio_lock);

	return count;
}

static ssize_t show_altf(struct device *dev, struct device_attribute *attr,
				char *buf)
{
	struct sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	u32 data, index;

	if (sattr->nr == OP_DAC)
		index = ite8516k_gpio_to_offset(sattr->index
				+ ITE8516K_DAC_START);

	else if (sattr->nr == OP_PWM)
		index = ite8516k_gpio_to_offset(sattr->index
				+ ITE8516K_PWM_START);

	else {
		index = ite8516k_gpio_to_offset(sattr->index
				+ ITE8516K_ADC_START);
		data = ite8516k_gpio_get_adc(index);
		return sprintf(buf, "%d\n", data);
	}

	data = ite8516k_gpio_get_data(index);

	if (sattr->nr == OP_PWM)
		data = data * 255 / 100;

	return sprintf(buf, "%d\n", data);
}

#define ite8516k_altf_dac_declaration(offset)        \
static SENSOR_DEVICE_ATTR_2(dac##offset, S_IRUGO | S_IWUSR, show_altf, \
						set_altf, OP_DAC, offset);

#define ite8516k_altf_dac_attribute(offset)          \
		(&sensor_dev_attr_dac##offset.dev_attr.attr),

#define ite8516k_altf_adc_declaration(offset)        \
static SENSOR_DEVICE_ATTR_2(adc##offset##_in, S_IRUGO, show_altf, NULL, \
							OP_ADC, offset);

#define ite8516k_altf_adc_attribute(offset)          \
		(&sensor_dev_attr_adc##offset##_in.dev_attr.attr),

/* first 1..4 pwm attributes is binded with fans control, so start from 5 */
#define ite8516k_altf_pwm_declaration(offset)        \
static SENSOR_DEVICE_ATTR_2(pwm##offset, S_IRUGO | S_IWUSR, show_altf, \
						set_altf, OP_PWM, offset - 5);

#define ite8516k_altf_pwm_attribute(offset)          \
		(&sensor_dev_attr_pwm##offset.dev_attr.attr),

/* 4 dacs start from 0 */
ite8516k_altf_dac_declaration(0);
ite8516k_altf_dac_declaration(1);
ite8516k_altf_dac_declaration(2);
ite8516k_altf_dac_declaration(3);

/* 4 pwms start from 5 */
ite8516k_altf_pwm_declaration(5);
ite8516k_altf_pwm_declaration(6);
ite8516k_altf_pwm_declaration(7);
ite8516k_altf_pwm_declaration(8);
/* 5 adc start from 0 */
ite8516k_altf_adc_declaration(0);
ite8516k_altf_adc_declaration(1);
ite8516k_altf_adc_declaration(2);
ite8516k_altf_adc_declaration(3);
ite8516k_altf_adc_declaration(4);

static struct attribute *ite8516k_altf_attributes[] = {
	ite8516k_altf_dac_attribute(0)
	ite8516k_altf_dac_attribute(1)
	ite8516k_altf_dac_attribute(2)
	ite8516k_altf_dac_attribute(3)
	ite8516k_altf_pwm_attribute(5)
	ite8516k_altf_pwm_attribute(6)
	ite8516k_altf_pwm_attribute(7)
	ite8516k_altf_pwm_attribute(8)
	ite8516k_altf_adc_attribute(0)
	ite8516k_altf_adc_attribute(1)
	ite8516k_altf_adc_attribute(2)
	ite8516k_altf_adc_attribute(3)
	ite8516k_altf_adc_attribute(4)
	NULL
};

#define ite8516k_fan_declaration(offset)	\
static SENSOR_DEVICE_ATTR_2(fan##offset##_name, S_IRUGO, show_fan, NULL, OP_NAME, offset - 1);	\
static SENSOR_DEVICE_ATTR_2(fan##offset##_input, S_IRUGO, show_fan, NULL, OP_INPUT, offset - 1); \
static SENSOR_DEVICE_ATTR_2(fan##offset##_min, S_IRUGO,	show_fan, NULL, OP_MIN, offset - 1); \
static SENSOR_DEVICE_ATTR_2(fan##offset##_max, S_IRUGO,	show_fan, NULL, OP_MAX, offset - 1); \
static SENSOR_DEVICE_ATTR_2(pwm##offset, S_IRUGO | S_IWUSR, show_pwm, set_pwm, 0, offset - 1); \
static SENSOR_DEVICE_ATTR_2(pwm##offset##_enable, S_IRUGO | S_IWUSR, show_pwmmode, set_pwmmode, OP_CTRL, offset - 1); \
static SENSOR_DEVICE_ATTR_2(pwm##offset##_target, S_IRUGO | S_IWUSR, show_pwmauto, set_pwmauto, OP_INPUT, offset - 1);	\
static SENSOR_DEVICE_ATTR_2(pwm##offset##_tolerance, S_IRUGO | S_IWUSR, show_pwmauto, set_pwmauto, OP_CTRL, offset - 1); \
static SENSOR_DEVICE_ATTR_2(pwm##offset##_div, S_IRUGO | S_IWUSR, show_pwmctrl, set_pwmctrl, OP_CTRL, offset - 1);

#define ite8516k_fan_attribute(offset)		\
		&sensor_dev_attr_fan##offset##_name.dev_attr.attr,		\
		&sensor_dev_attr_fan##offset##_input.dev_attr.attr,		\
		&sensor_dev_attr_fan##offset##_min.dev_attr.attr,		\
		&sensor_dev_attr_fan##offset##_max.dev_attr.attr,		\
		&sensor_dev_attr_pwm##offset.dev_attr.attr,			\
		&sensor_dev_attr_pwm##offset##_enable.dev_attr.attr,		\
		&sensor_dev_attr_pwm##offset##_target.dev_attr.attr,		\
		&sensor_dev_attr_pwm##offset##_tolerance.dev_attr.attr,		\
		&sensor_dev_attr_pwm##offset##_div.dev_attr.attr,

#define ite8516k_temp_declaration(offset)	\
static SENSOR_DEVICE_ATTR_2(temp##offset##_name, S_IRUGO, show_temp, NULL, OP_NAME, offset - 1);	\
static SENSOR_DEVICE_ATTR_2(temp##offset##_input, S_IRUGO, show_temp, NULL, OP_INPUT, offset - 1);	\
static SENSOR_DEVICE_ATTR_2(temp##offset##_max, S_IRUGO, show_temp, NULL, OP_MAX, offset - 1);		\
static SENSOR_DEVICE_ATTR_2(temp##offset##_min, S_IRUGO, show_temp, NULL, OP_MIN, offset - 1);		\
static SENSOR_DEVICE_ATTR_2(temp##offset##_crit, S_IRUGO|S_IWUSR, show_temp, set_temp, OP_CTRL, offset - 1);	\

#define ite8516k_temp_attribute(offset)		\
		&sensor_dev_attr_temp##offset##_name.dev_attr.attr,		\
		&sensor_dev_attr_temp##offset##_input.dev_attr.attr,		\
		&sensor_dev_attr_temp##offset##_max.dev_attr.attr,		\
		&sensor_dev_attr_temp##offset##_min.dev_attr.attr,		\
		&sensor_dev_attr_temp##offset##_crit.dev_attr.attr,


#define ite8516k_input_declaration(offset)	\
static SENSOR_DEVICE_ATTR_2(in##offset##_name, S_IRUGO, show_input, NULL, OP_NAME, offset -1);	\
static SENSOR_DEVICE_ATTR_2(in##offset##_input, S_IRUGO, show_input, NULL, OP_INPUT, offset -1);	\

#define ite8516k_input_attribute(offset)	\
		&sensor_dev_attr_in##offset##_name.dev_attr.attr,		\
		&sensor_dev_attr_in##offset##_input.dev_attr.attr,		

ite8516k_fan_declaration(1);
ite8516k_fan_declaration(2);
ite8516k_fan_declaration(3);
ite8516k_fan_declaration(4);
ite8516k_temp_declaration(1);
ite8516k_temp_declaration(2);
ite8516k_input_declaration(1);

static DEVICE_ATTR(name, S_IRUGO, show_name, NULL);

static struct attribute *ite8516k_attributes[] = {
	ite8516k_temp_attribute(1)
	ite8516k_temp_attribute(2)
	ite8516k_fan_attribute(1)
	ite8516k_fan_attribute(2)
	ite8516k_fan_attribute(3)
	ite8516k_fan_attribute(4)
	ite8516k_input_attribute(1)
	&dev_attr_name.attr,
	NULL
};

static const struct attribute_group ite8516k_group = {
	.attrs = ite8516k_attributes,
};


/*
 * Watchdog
 */

static int set_wd(uint8_t sec)
{
	if (ite8516k_outb(ITE8516K_CMD_SET_WATCHDOG, sec) & ITE8516K_IO_ERROR)
		pr_err("%s Error setting watchdog timer\n", DRV_NAME);

	return 0;
}

static int ite8516k_wdt_start(struct watchdog_device *wdt_dev)
{
	return set_wd(wdt_dev->timeout);
}

static int ite8516k_wdt_stop(struct watchdog_device *wdt_dev)
{
	return set_wd(0);
}

static int ite8516k_wdt_ping(struct watchdog_device *wdt_dev)
{
	return set_wd(wdt_dev->timeout);
}

static int ite8516k_wdt_set_timeout(struct watchdog_device *wdt_dev,
					unsigned int timeout)
{
	wdt_dev->timeout = timeout;
	return set_wd(wdt_dev->timeout);
}

static const struct watchdog_info ite8516k_wdt_info = {
	.options        = WDIOF_SETTIMEOUT | WDIOF_KEEPALIVEPING |
				 WDIOF_MAGICCLOSE,
	.identity       = "Kontron ite8516k Watchdog",
};

static const struct watchdog_ops ite8516k_wdt_ops = {
	.owner = THIS_MODULE,
	.start = ite8516k_wdt_start,
	.stop = ite8516k_wdt_stop,
	.ping = ite8516k_wdt_ping,
	.set_timeout = ite8516k_wdt_set_timeout,
};

static struct watchdog_device ite8516k_wdt = {
	.info = &ite8516k_wdt_info,
	.ops = &ite8516k_wdt_ops,
	.min_timeout = 1,
	.max_timeout = 255,
	.timeout = 5,
};

/*
 * SMBus
 */

static int convert_status(u32 res)
{
	if (res & ITE8516K_IO_ERROR)
		return -ETIMEDOUT;
	res &= 0xFF;
	if (res == 1)
		return 0;
	if (res == 2)
		return -ETIMEDOUT;
	return -EIO;
}

static s32 ite8516k_access(struct i2c_adapter *adap, u16 addr,
		unsigned short flags, char read_write,
		u8 command, int size, union i2c_smbus_data *data)
{
	int i, len;
	u32 res = 0;

	dev_dbg(&ite8516k_adapter.dev, "access size: %d %s\n", size,
		(read_write) ? "READ" : "WRITE");
	switch (size) {
	case I2C_SMBUS_QUICK:
		res = ite8516k_outb_inb(ITE8516K_CMD_SMBUS_QUICK_COM,
					 (addr << 1) | read_write);
		return convert_status(res);
	case I2C_SMBUS_BYTE:
		if (read_write == I2C_SMBUS_READ) {
			res = ite8516k_outb_inw(ITE8516K_CMD_SMBUS_RECEIVE_BYTE,
						(addr << 1) | read_write);
			if (res & ITE8516K_IOCMD_ERROR)
				return -ETIMEDOUT;
			data->byte = (res >> 8) & 0xFF;
			return convert_status(res);
		} else {
			res = ite8516k_outw_inb(ITE8516K_CMD_SMBUS_SEND_BYTE,
				(command << 8) | (addr << 1) | read_write);
			return convert_status(res);
		}
	case I2C_SMBUS_BYTE_DATA:
		if (read_write == I2C_SMBUS_READ) {
			res = ite8516k_outw_inw(ITE8516K_CMD_SMBUS_READ_BYTE,
				(command << 8) | (addr << 1) | read_write);
			if (res & ITE8516K_IOCMD_ERROR)
				return -ETIMEDOUT;
			data->byte = (res >> 8) & 0xFF;
			return convert_status(res);
		} else {
			res = ite8516k_outwb_inb(ITE8516K_CMD_SMBUS_WRITE_BYTE,
			      (data->byte << 16) | (command << 8) |
						(addr << 1) | read_write);
			return convert_status(res);
		}
	case I2C_SMBUS_WORD_DATA:
		if (read_write == I2C_SMBUS_READ) {
			res = ite8516k_outw_inwb(ITE8516K_CMD_SMBUS_READ_WORD,
				(command << 8) | (addr << 1) | read_write);
			if (res & ITE8516K_IOCMD_ERROR)
				return -ETIMEDOUT;
			data->word = (res >> 8) & 0xFFFF;
			return convert_status(res);
		} else {
			res = ite8516k_outww_inb(ITE8516K_CMD_SMBUS_WRITE_WORD,
				(data->word << 16) | (command << 8) |
						(addr << 1) | read_write);
			return convert_status(res);
		}
	case I2C_SMBUS_BLOCK_DATA:
		if (read_write == I2C_SMBUS_READ) {
			res = ite8516k_outw(ITE8516K_CMD_SMBUS_READ_BLOCK,
				(command << 8) | (addr << 1) | read_write);
			if (res & ITE8516K_IOCMD_ERROR)
				return -ETIMEDOUT;
			res = ite8516k_inb(ITE8516K_CMD_SMBUS_READ_BLOCK);
			if (res & ITE8516K_IOCMD_ERROR)
				return -ETIMEDOUT;
			if ((res & 0xFF) == 1) {
				len = ite8516k_inb(ITE8516K_CMD_SMBUS_READ_BLOCK);
				if (len & ITE8516K_IOCMD_ERROR)
					return -ETIMEDOUT;
				len &= 0xFF;
				if (len == 0 || len > I2C_SMBUS_BLOCK_MAX)
					return -EPROTO;
				data->block[0] = len;
				for (i = 1; i < data->block[0]; i++) {
					res = ite8516k_inb(ITE8516K_CMD_SMBUS_READ_BLOCK);
					if (res & ITE8516K_IOCMD_ERROR)
						return -ETIMEDOUT;
					data->block[i] = res & 0xFF;
				}
			}
			return convert_status(res);
		} else {
			len = data->block[0];
			if (len  == 0 || len > I2C_SMBUS_BLOCK_MAX)
				return -EINVAL;
			if (ite8516k_outww(ITE8516K_CMD_SMBUS_WRITE_BLOCK,
				(data->block[1] << 24) | (len << 16) |
				(command << 8) | (addr << 1) | read_write) &
							ITE8516K_IOCMD_ERROR);
				return -ETIMEDOUT;
			for (i = 2; i <= len; i++) {
				if (ite8516k_outb(ITE8516K_CMD_SMBUS_WRITE_BLOCK,
					data->block[i]) & ITE8516K_IOCMD_ERROR);
					return -ETIMEDOUT;
			}
			res = ite8516k_inb(ITE8516K_CMD_SMBUS_WRITE_BLOCK);
			return convert_status(res);
		}
	default:
		dev_warn(&ite8516k_adapter.dev, "Unsupported transaction %d\n",
									size);
		return -EOPNOTSUPP;
	}

	return 0;
}

static u32 ite8516k_func(struct i2c_adapter  *adapter)
{
	return I2C_FUNC_SMBUS_QUICK | I2C_FUNC_SMBUS_BYTE |
		I2C_FUNC_SMBUS_BYTE_DATA | I2C_FUNC_SMBUS_WORD_DATA |
		I2C_FUNC_SMBUS_BLOCK_DATA;
}

static const struct i2c_algorithm smbus_algorithm = {
	.smbus_xfer = ite8516k_access,
	.functionality = ite8516k_func,
};

static struct i2c_adapter ite8516k_adapter = {
	.owner = THIS_MODULE,
	.class = I2C_CLASS_HWMON | I2C_CLASS_SPD,
	.algo = &smbus_algorithm,
};

/*---------------------------Kernel------------------------------------------*/

int ite8516k_init(void)
{
	int i;
	u32 data;

	data = ite8516k_inwb(ITE8516K_CMD_INFO);
	/* Repeat the reading as incorrect value is returned after first
	 * attempt */
	data = ite8516k_inwb(ITE8516K_CMD_INFO);
	if (data&ITE8516K_IO_ERROR)
		return -EIO;

	pr_info("%s firmware version: v%d.%d\n", DRV_NAME,
		data & 0xFF, (data >> 8) & 0xFF);
	data = (data<<8) | ite8516k_inb(ITE8516K_CMD_INFO2);

	for (i = 0; i < ITE8516K_FAN_NUMBER; i++) {
		data = ((ITE8516K_DEFAULT_FANDIV&0xFF) << 8) | (i&0xFF);
		ite8516k_outw(ITE8516K_CMD_SET_FANDIV, data);
		data = ((ite8516k_fan_data[i].mode&0xFF) << 8) | (i&0xFF);
		ite8516k_outw(ITE8516K_CMD_SET_FANMODE, data);
	}

	return 0;
}

static int ite8516k_probe(struct platform_device *pdev)
{
	int err = 0;
	int err_gp = 0;
	int i;
	struct resource *res;

	res = platform_get_resource(pdev, IORESOURCE_IO, 0);
	if (!res) {
		err = -EINVAL;
		goto exit;
	}

	if (resource_size(res) != 2) {
		err = -ENODEV;
		goto exit;
	}

	if (!request_region(res->start, resource_size(res), pdev->name)) {
		err = -EBUSY;
		goto exit;
	}

	ite8516k_baddr = res->start;
	if (ite8516k_init()) {
		err = -EIO;
		goto release_resource;
	}

	ite8516k_gpio.dev = &pdev->dev;
	err = gpiochip_add(&ite8516k_gpio);
	if (err)
		goto release_resource;

	err = sysfs_create_group(&pdev->dev.kobj, &ite8516k_group);
	if (err)
		goto remove_gpio;

	for (i = 0; i < ARRAY_SIZE(ite8516k_altf_attributes) - 1; i++) {
		if (gpio_altf[i]) {
			ite8516k_gpio_altf_enable(i);

			err = sysfs_create_file(&pdev->dev.kobj,
						ite8516k_altf_attributes[i]);
			if (err)
				goto unreg_sysfs;
		}
	}

	ite8516k_hwmon = hwmon_device_register(&pdev->dev);
	if (IS_ERR(ite8516k_hwmon)) {
		err =  -PTR_ERR(ite8516k_hwmon);
		goto unreg_sysfs;
	}

	ite8516k_wdt.parent = &pdev->dev;
	err = watchdog_register_device(&ite8516k_wdt);
	if (err < 0)
		goto error_watchdog_register;

	ite8516k_adapter.dev.parent =  &pdev->dev;
	snprintf(ite8516k_adapter.name, sizeof(ite8516k_adapter.name),
		"SMBus ITE8516K adapter");
	err = i2c_add_adapter(&ite8516k_adapter);
	if (err)
		dev_err(&pdev->dev, "Couldn't register a SMBus adapter!\n");

	return 0;

error_watchdog_register:
	hwmon_device_unregister(ite8516k_hwmon);
unreg_sysfs:
	for (i = 0; i < ARRAY_SIZE(ite8516k_altf_attributes) - 1; i++)
		sysfs_remove_file(&pdev->dev.kobj, ite8516k_altf_attributes[i]);

	sysfs_remove_group(&pdev->dev.kobj, &ite8516k_group);
remove_gpio:
	err_gp = gpiochip_remove(&ite8516k_gpio);
	if (err_gp)
		dev_err(&pdev->dev, "gpiochip_remove failed %d\n", err);
release_resource:
	release_region(res->start, resource_size(res));
	platform_set_drvdata(pdev, NULL);
exit:

	return err;
}

static int ite8516k_remove(struct platform_device *pdev)
{
	struct resource *res;
	int i, err = 0;

	i2c_del_adapter(&ite8516k_adapter);
	watchdog_unregister_device(&ite8516k_wdt);
	hwmon_device_unregister(ite8516k_hwmon);

	for (i = 0; i < ARRAY_SIZE(ite8516k_altf_attributes) - 1; i++)
		sysfs_remove_file(&pdev->dev.kobj, ite8516k_altf_attributes[i]);

	sysfs_remove_group(&pdev->dev.kobj, &ite8516k_group);

	err = gpiochip_remove(&ite8516k_gpio);
	if (err) {
		dev_err(&pdev->dev, "gpiochip_remove failed %d\n", err);
		return err;
	}

	res = platform_get_resource(pdev, IORESOURCE_IO, 0);
	release_region(res->start, resource_size(res));
	platform_set_drvdata(pdev, NULL);

	return 0;
}

static int ite8516k_suspend(struct platform_device *pdev, pm_message_t msg)
{
	int gpio_num, fan_num;
	s32 data = 0;

	/* save gpio values and directions for output pins */
	for (gpio_num = 0; gpio_num < ITE8516K_GPIO_NUMBER; gpio_num++) {
		if (!gpio_altf[gpio_num]
			&& ((ite8516k_resume_data.gpio_directions >> gpio_num) & 1)) {
			if (ite8516k_gpio_get(&ite8516k_gpio, gpio_num))
				ite8516k_resume_data.gpio_values |=
							 (1 << gpio_num);
			else
				ite8516k_resume_data.gpio_values &=
					(0xFFFFFFFF & ~(1 << gpio_num));
		}
	}

	pr_debug("%s gpio_directions before suspend: 0x%8x\n", DRV_NAME,
				 ite8516k_resume_data.gpio_directions);
	pr_debug("%s gpio_values before suspend: 0x%8x\n", DRV_NAME,
				 ite8516k_resume_data.gpio_values);

	for (gpio_num = 0; gpio_num < ITE8516K_DAC_NUMBER; gpio_num++) {
		if (gpio_altf[gpio_num + ITE8516K_DAC_START]) {
			u8 index = ite8516k_gpio_to_offset(gpio_num + ITE8516K_DAC_START);
			ite8516k_resume_data.dac[gpio_num] = ite8516k_gpio_get_data(index);

			pr_debug("%s dac number 0x%x before suspend: 0x%8x\n",
				DRV_NAME, gpio_num, ite8516k_resume_data.dac[gpio_num]);
		}
	}

	for (gpio_num = 0; gpio_num < ITE8516K_PWM_NUMBER; gpio_num++) {
		if (gpio_altf[gpio_num + ITE8516K_PWM_START]) {
			u8 index = ite8516k_gpio_to_offset(gpio_num + ITE8516K_PWM_START);
			ite8516k_resume_data.pwm[gpio_num] = ite8516k_gpio_get_data(index);

			pr_debug("%s pwm number 0x%x before suspend: 0x%8x\n", DRV_NAME,
				gpio_num, ite8516k_resume_data.pwm[gpio_num]);
		}
	}


	for (fan_num = 0; fan_num < ITE8516K_FAN_NUMBER; fan_num++) {

		data =  ite8516k_outb_inb(ITE8516K_CMD_GET_FANDIV, fan_num);
		if (data & ITE8516K_IO_ERROR)
			data = -1;
		ite8516k_resume_data.fan_div[fan_num] = (s8) data;
		data = 0;

		switch (ite8516k_fan_data[fan_num].mode) {
		case ITE8516K_FANMODE_PWM:
			data = ite8516k_outb_inb(ITE8516K_CMD_GET_FANPWM,
								 fan_num);
			if (data & ITE8516K_IO_ERROR)
				data = 0;
			ite8516k_resume_data.fan_target[fan_num] = (u16) data;
			break;
		case ITE8516K_FANMODE_SPEED:
			data = ite8516k_outb_inw(ITE8516K_CMD_GET_FANSPEED,
								 fan_num);
			if (data & ITE8516K_IO_ERROR)
				data = 0;
			ite8516k_resume_data.fan_target[fan_num] = (u16) data;
			break;
		case ITE8516K_FANMODE_CRUSE:
			data = ite8516k_outb_inw(ITE8516K_CMD_GET_AUTOTEMP,
								 fan_num);
			if (data & ITE8516K_IO_ERROR)
				data = 0;
			ite8516k_resume_data.fan_target[fan_num] = (u16) data;
			break;
		case ITE8516K_FANMODE_AUTO:
		default:
			ite8516k_resume_data.fan_target[fan_num] = (u16) data;
			break;
		}
	}

#ifdef DEBUG
	for (fan_num = 0; fan_num < ITE8516K_FAN_NUMBER; fan_num++) {
		pr_debug("%s fan_mode[%d] before suspend: %d\n", DRV_NAME,
				 fan_num, ite8516k_fan_data[fan_num].mode);
		pr_debug("%s fan_target[%d] before suspend: %d\n", DRV_NAME,
			 fan_num, ite8516k_resume_data.fan_target[fan_num]);
		pr_debug("%s fan_div[%d] before suspend: %d\n", DRV_NAME,
			 fan_num, ite8516k_resume_data.fan_div[fan_num]);
	}
#endif

	return 0;
}

static int ite8516k_resume(struct platform_device *pdev)
{
	int gpio_num, gpio_value, fan_num;
	u32 data = 0;

	pr_debug("%s gpio_directions after resume: 0x%8x\n", DRV_NAME,
				 ite8516k_resume_data.gpio_directions);
	pr_debug("%s gpio_values after resume: 0x%8x\n", DRV_NAME,
				 ite8516k_resume_data.gpio_values);

	/* save gpio values and directions for output pins */
	for (gpio_num = 0; gpio_num < ITE8516K_GPIO_NUMBER; gpio_num++) {
		if ((ite8516k_resume_data.gpio_directions >> gpio_num) & 0x1) {
			gpio_value = (1 &
				(ite8516k_resume_data.gpio_values >> gpio_num));
			ite8516k_gpio_direction_out(&ite8516k_gpio, gpio_num,
								 gpio_value);
			ite8516k_gpio_set(&ite8516k_gpio, gpio_num, gpio_value);
		}

	}

	for (gpio_num = 0; gpio_num < ITE8516K_DAC_NUMBER; gpio_num++) {

		if (gpio_altf[gpio_num + ITE8516K_DAC_START]) {

			u8 index = ite8516k_gpio_to_offset(gpio_num + ITE8516K_DAC_START);
			ite8516k_gpio_set_data(index, ite8516k_resume_data.dac[gpio_num]);

			pr_debug("%s dac number 0x%x after suspend: 0x%8x\n", DRV_NAME,
				gpio_num, ite8516k_resume_data.dac[gpio_num]);
		}
	}

	for (gpio_num = 0; gpio_num < ITE8516K_PWM_NUMBER; gpio_num++) {

		if (gpio_altf[gpio_num + ITE8516K_PWM_START]) {

			u8 index = ite8516k_gpio_to_offset(gpio_num + ITE8516K_PWM_START);
			ite8516k_gpio_set_data(index, ite8516k_resume_data.pwm[gpio_num]);

			pr_debug("%s pwm number 0x%x after suspend: 0x%8x\n", DRV_NAME,
				gpio_num, ite8516k_resume_data.pwm[gpio_num]);
		}
	}


#ifdef DEBUG
	for (fan_num = 0; fan_num < ITE8516K_FAN_NUMBER; fan_num++) {
		pr_debug("%s fan_mode[%d] after resume: %d\n", DRV_NAME,
				 fan_num, ite8516k_fan_data[fan_num].mode);
		pr_debug("%s fan_target[%d] after resume: %d\n", DRV_NAME,
			 fan_num, ite8516k_resume_data.fan_target[fan_num]);
		pr_debug("%s fan_div[%d] after resume: %d\n", DRV_NAME,
			 fan_num, ite8516k_resume_data.fan_div[fan_num]);
	}
#endif

	for (fan_num = 0; fan_num < ITE8516K_FAN_NUMBER; fan_num++) {

		/* Restore a fan mode */
		data = ((ite8516k_fan_data[fan_num].mode & 0xFF) << 8)
							 | (fan_num & 0xFF);
		ite8516k_outw(ITE8516K_CMD_SET_FANMODE, data);
		data = 0;

		/* Restore a pwm_div value */
		data = ((ite8516k_resume_data.fan_div[fan_num] & 0xFF) << 8)
							 | (fan_num & 0xFF);
		ite8516k_outw(ITE8516K_CMD_SET_FANDIV, data);
		data = 0;

		/* Restore either a target pwm, rpm or temperature value */
		switch (ite8516k_fan_data[fan_num].mode) {
		case ITE8516K_FANMODE_PWM:
			data = ((ite8516k_resume_data.fan_target[fan_num]
					 & 0xFF) << 8) | (fan_num & 0xFF);
			ite8516k_outw(ITE8516K_CMD_SET_FANPWM, data);
			break;
		case ITE8516K_FANMODE_SPEED:
			data = ((ite8516k_resume_data.fan_target[fan_num]
					 & 0xFFFF) << 8) | (fan_num & 0xFF);
			ite8516k_outwb(ITE8516K_CMD_SET_FANSPEED, data);
			break;
		case ITE8516K_FANMODE_CRUSE:
			data = ((ite8516k_resume_data.fan_target[fan_num]
					 & 0xFFFF) << 8) | (fan_num & 0xFF);
			ite8516k_outwb(ITE8516K_CMD_SET_AUTOTEMP, data);
			break;
		case ITE8516K_FANMODE_AUTO:
		default:
			ite8516k_resume_data.fan_target[fan_num] = (u16) data;
			break;
		}
	}

	return 0;
}

static const struct platform_device_id ite_id_table[] = {
	{DRV_NAME, 0},
	{"", 0},
};

MODULE_DEVICE_TABLE(platform, ite_id_table);

static struct platform_driver ite_driver = {
	.probe = ite8516k_probe,
	.remove = ite8516k_remove,
	.suspend = ite8516k_suspend,
	.resume = ite8516k_resume,
	.id_table = ite_id_table,
	.driver = {
		.name = DRV_NAME,
		.owner = THIS_MODULE,
	},
};

static struct platform_device *ite_pdev;

static int __init ite_init(void)
{
	int err = 0;
	struct resource res;

	err = platform_driver_register(&ite_driver);
	if (err)
		return err;

	memset(&res, 0, sizeof(res));
	res.name = DRV_NAME;
	res.start = 0x20c;
	res.end = 0x20c + 1;
	res.flags = IORESOURCE_IO;

	err = acpi_check_resource_conflict(&res);
	if (err)
		goto exit_unregister;

	ite_pdev = platform_device_register_simple(DRV_NAME, -1, &res, 1);
	if (!ite_pdev)
		goto exit_unregister;

	return 0;

exit_unregister:
	platform_driver_unregister(&ite_driver);

	return err;
}

static void __exit ite_exit(void)
{
	platform_device_unregister(ite_pdev);
	platform_driver_unregister(&ite_driver);
}

module_init(ite_init);
module_exit(ite_exit);

MODULE_AUTHOR("Andrey Rusalin, <arusalin@dev.rtsoft.ru>");
MODULE_DESCRIPTION("ITE8516 driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:ite8516k");
