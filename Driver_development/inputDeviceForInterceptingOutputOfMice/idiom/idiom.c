/*
 *  idiom.c, sample code for USB drivers, heavily based on usbmouse.c
 *
 *  Copyright (c) 2000 Alessandro Rubini <rubini@gnu.org>
 *  Copyright (c) 1999 Vojtech Pavlik <vojtech@suse.cz>
 *
 */

/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or 
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#ifndef __KERNEL__
#  define __KERNEL__
#endif
#ifndef MODULE
#  define MODULE
#endif

#include <linux/module.h>

#include <linux/kernel.h> /* printk() */
#include <linux/malloc.h> /* kmalloc() */

/* usb stuff */
#include <linux/input.h>
#include <linux/usb.h>

/* miscdevice stuff */
#include <linux/poll.h>
#include <linux/miscdevice.h>
#include <asm/uaccess.h>

/*
 * We need a local data structure, as it must be allocated for each new
 * mouse device plugged in the USB bus
 */

struct idiom_device {
    signed char data[3];     /* use a three-byte protocol */
    struct urb urb;          /* USB Request block, to get USB data*/
    struct input_dev idev;   /* input device, to push out input  data */
    int x, y;                /* keep track of the position of this device */
};


/*
 * These two callbacks are invoked when an USB device is detached or attached
 * to the bus
 */

static void idiom_disconnect(struct usb_device *udev, void *clientdata)
{
    /* the clientdata is the idiom_device we passed originally */
    struct idiom_device *idiom = clientdata;

    /* remove the URB, remove the input device, free memory */
    usb_unlink_urb(&idiom->urb);
    input_unregister_device(&idiom->idev);
    kfree(idiom);
    printk(KERN_INFO "idiom: USB mouse disconnected\n");
}

static void *idiom_probe(struct usb_device *udev, unsigned int ifnum)
{
    /*
     * The probe procedure is maybe the least interesting one, as it
     * depends on hardware parameters of the mouse devices. This is
     * copied from usbmouse.c as found in the kernel sources
     */

    struct usb_interface_descriptor *interface;
    struct usb_endpoint_descriptor *endpoint;
    struct idiom_device *idiom;

    if (udev->descriptor.bNumConfigurations != 1) return NULL;
    interface = udev->config[0].interface[ifnum].altsetting + 0;

    /* check that the device is really a mouse */
    if (interface->bInterfaceClass != 3) return NULL;
    if (interface->bInterfaceSubClass != 1) return NULL;
    if (interface->bInterfaceProtocol != 2) return NULL;
    if (interface->bNumEndpoints != 1) return NULL;
    
    endpoint = interface->endpoint + 0;
    if (!(endpoint->bEndpointAddress & 0x80)) return NULL;
    if ((endpoint->bmAttributes & 3) != 3) return NULL;

    usb_set_protocol(udev, interface->bInterfaceNumber, 0);
    usb_set_idle(udev, interface->bInterfaceNumber, 0, 0);

    /* allocate and zero a new data structure for the new device */
    idiom = kmalloc(sizeof(struct idiom_device), GFP_KERNEL);
    if (!idiom) return NULL; /* failure */
    memset(idiom, 0, sizeof(*idiom));

    /* fill the URB data structure using the FILL_INT_URB macro */
    {
	static void idiom_irq(struct urb *urb); /* forward declaration */
	int pipe = usb_rcvintpipe(udev, endpoint->bEndpointAddress);
	int maxp = usb_maxpacket(udev, pipe, usb_pipeout(pipe));
	
	FILL_INT_URB(&idiom->urb, udev, pipe, idiom->data, maxp > 3 ? 3 : maxp,
		      idiom_irq, idiom, endpoint->bInterval);
    }

    /* register the URB within the USB subsystem */
    if (usb_submit_urb(&idiom->urb)) {
	kfree(idiom);
	return NULL;
    }

    /* tell the features of this input device: fake only keys */
    idiom->idev.evbit[0] = BIT(EV_KEY);

    /* and tell which keys: only the arrows */
    set_bit(KEY_UP,    idiom->idev.keybit);
    set_bit(KEY_LEFT,  idiom->idev.keybit);
    set_bit(KEY_RIGHT, idiom->idev.keybit);
    set_bit(KEY_DOWN,  idiom->idev.keybit);


    /* and register the input device itself */
    input_register_device(&idiom->idev);

    /* announce yourself */
    printk(KERN_INFO "idiom: input USB mouse being misused\n");

    /* and return the new structure */
    return idiom;
}


/*
 * The callbacks are registered within the USB subsystem using the
 * usb_driver data structure
 */
static struct usb_driver idiom_usb_driver = {
        name:        "idiom",
        probe:       idiom_probe,
        disconnect:  idiom_disconnect,
};

/* forward declaration */
struct file_operations idiom_file_operations;


struct miscdevice idiom_misc = {
    minor:      MISC_DYNAMIC_MINOR,
    name:       "idiom",
    fops:       &idiom_file_operations,
};

/*
 * Functions called at module load and unload time: only register and
 * unregister the USB callbacks and the misc entry point
 */
int init_module(void)
{
    int retval;

    retval = usb_register(&idiom_usb_driver);
    if (!retval) {
	retval = misc_register(&idiom_misc);
	if (retval) 
	    usb_deregister(&idiom_usb_driver);
    }
    return retval;
}

void cleanup_module(void)
{
    usb_deregister(&idiom_usb_driver);
    misc_deregister(&idiom_misc);
}


/*
 * Handler for data sent in by the device. The function is called by
 * the USB kernel subsystem whenever the device spits out new data
 */
static void idiom_irq(struct urb *urb)
{
    struct idiom_device *idiom = urb->context;
    signed char *data = idiom->data;
    struct input_dev *idev = &idiom->idev;

    if (urb->status != USB_ST_NOERROR) return;

    /* ignore data[0] which reports mouse buttons */
    idiom->x += data[1];
    idiom->y += data[2];
    printk(KERN_DEBUG "idiom irq, %5i %5i\n", idiom->x, idiom->y);

    /* push one key every 10 pixels */
    while (idiom->y < -10) {
	input_report_key(idev, KEY_UP, 1); /* keypress */
	input_report_key(idev, KEY_UP, 0); /* release */
	idiom->y += 10;
    }
    while (idiom->y > 10) {
	input_report_key(idev, KEY_DOWN, 1); /* keypress */
	input_report_key(idev, KEY_DOWN, 0); /* release */
	idiom->y -= 10;
    }
    while (idiom->x < -10) {
	input_report_key(idev, KEY_LEFT, 1); /* keypress */
	input_report_key(idev, KEY_LEFT, 0); /* release */
	idiom->x += 10;
    }
    while (idiom->x > 10) {
	input_report_key(idev, KEY_RIGHT, 1); /* keypress */
	input_report_key(idev, KEY_RIGHT, 0); /* release */
	idiom->x -= 10;
    }
}

/*
 * Finally, offer an entry point to write data using the misc device
 */


/* the open method does the same as idiom_probe does */
int idiom_open(struct inode *inode, struct file *filp)
{
    struct idiom_device *idiom;

    /* allocate and zero a new data structure for the new device */
    idiom = kmalloc(sizeof(struct idiom_device), GFP_KERNEL);
    if (!idiom) return -ENOMEM; /* failure */
    memset(idiom, 0, sizeof(*idiom));

    /* tell the features of this input device: fake only keys */
    idiom->idev.evbit[0] = BIT(EV_KEY);

    /* and tell which keys: only the arrows */
    set_bit(103, idiom->idev.keybit); /* Up    */
    set_bit(105, idiom->idev.keybit); /* Left  */
    set_bit(106, idiom->idev.keybit); /* Right */
    set_bit(108, idiom->idev.keybit); /* Down  */

    /* and register the input device itself */
    input_register_device(&idiom->idev);
    filp->private_data = idiom;

    /* announce yourself */
    printk(KERN_INFO "idiom: faking an USB mouse via the misc device\n");
    return 0; /* Ok */
}    

/* close releases the device, like idiom_disconnect */
int idiom_release(struct inode *inode, struct file *filp)
{
    struct idiom_device *idiom = filp->private_data;
    input_unregister_device(&idiom->idev);
    kfree(idiom);
    printk(KERN_INFO "idiom: closing misc device\n");
    return 0;
}

/* poll reports the device as writeable */
unsigned int idiom_poll(struct file *filp, struct poll_table_struct *table)
{
    return POLLWRNORM | POLLOUT;
}

/* write accepts data and converts it to mouse movement */
ssize_t idiom_write(struct file *filp, const char *buf, size_t count,
		    loff_t *offp)
{
    struct idiom_device *idiom = filp->private_data;
    static char localbuf[16];
    struct urb urb;
    int i;

    /* accept 16 bytes at a time, at most */
    if (count >16) count=16;
    copy_from_user(localbuf, buf, count);

    /* prepare the urb for idiom_irq() */
    urb.status = USB_ST_NOERROR;
    urb.context = idiom;

    /* scan written data */
    for (i=0; i<count; i++) {
	idiom->data[1] = idiom->data[2] = 0;
	switch (localbuf[i]) {
	    case 'u': case 'U': /* up */
		idiom->data[2] = -10;
		break;
	    case 'd': case 'D': /* down */
		idiom->data[2] = 10;
		break;
	    case 'l': case 'L': /* left */
		idiom->data[1] = -10;
		break;
	    case 'r': case 'R': /* right */
		idiom->data[1] = 10;
		break;
	    default:
		continue;
	}
	/* if we are here, a valid key is there, fix the urb */
	idiom_irq(&urb);
    }
    return count;
}


struct file_operations idiom_file_operations = {
	write:    idiom_write,
	poll:     idiom_poll,
	open:     idiom_open,
	release:  idiom_release,
};
