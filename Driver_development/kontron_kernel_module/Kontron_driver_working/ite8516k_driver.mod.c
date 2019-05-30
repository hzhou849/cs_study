#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x3d6976bf, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0x96ea4642, __VMLINUX_SYMBOL_STR(param_ops_bool) },
	{ 0x397bdd46, __VMLINUX_SYMBOL_STR(param_array_ops) },
	{ 0x884381c2, __VMLINUX_SYMBOL_STR(platform_device_unregister) },
	{ 0xe02b9e90, __VMLINUX_SYMBOL_STR(platform_driver_unregister) },
	{ 0xaea976a8, __VMLINUX_SYMBOL_STR(acpi_check_resource_conflict) },
	{ 0x6a08c31c, __VMLINUX_SYMBOL_STR(__platform_driver_register) },
	{ 0xad17fa37, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0x54c8d525, __VMLINUX_SYMBOL_STR(i2c_add_adapter) },
	{ 0xc856f132, __VMLINUX_SYMBOL_STR(watchdog_register_device) },
	{ 0xe2fad8ff, __VMLINUX_SYMBOL_STR(hwmon_device_register) },
	{ 0x86bc3f15, __VMLINUX_SYMBOL_STR(sysfs_create_file_ns) },
	{ 0xd160a17c, __VMLINUX_SYMBOL_STR(sysfs_create_group) },
	{ 0x86849bf9, __VMLINUX_SYMBOL_STR(gpiochip_add) },
	{ 0x1fedf0f4, __VMLINUX_SYMBOL_STR(__request_region) },
	{ 0xaeec159a, __VMLINUX_SYMBOL_STR(platform_device_register_full) },
	{ 0x7c61340c, __VMLINUX_SYMBOL_STR(__release_region) },
	{ 0xff7559e4, __VMLINUX_SYMBOL_STR(ioport_resource) },
	{ 0xa3f6274a, __VMLINUX_SYMBOL_STR(platform_get_resource) },
	{ 0xb64e9b91, __VMLINUX_SYMBOL_STR(sysfs_remove_group) },
	{ 0xddfd51dc, __VMLINUX_SYMBOL_STR(sysfs_remove_file_ns) },
	{ 0x4ff1e5b3, __VMLINUX_SYMBOL_STR(hwmon_device_unregister) },
	{ 0xb63f50c8, __VMLINUX_SYMBOL_STR(watchdog_unregister_device) },
	{ 0xc81d643a, __VMLINUX_SYMBOL_STR(i2c_del_adapter) },
	{ 0x30085292, __VMLINUX_SYMBOL_STR(__dynamic_dev_dbg) },
	{ 0xb7681e7c, __VMLINUX_SYMBOL_STR(dev_warn) },
	{ 0xdb7305a1, __VMLINUX_SYMBOL_STR(__stack_chk_fail) },
	{ 0x3c80c06c, __VMLINUX_SYMBOL_STR(kstrtoull) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0x44b1d426, __VMLINUX_SYMBOL_STR(__dynamic_pr_debug) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x6bf1c17f, __VMLINUX_SYMBOL_STR(pv_lock_ops) },
	{ 0xeae3dfd6, __VMLINUX_SYMBOL_STR(__const_udelay) },
	{ 0xe259ae9e, __VMLINUX_SYMBOL_STR(_raw_spin_lock) },
	{ 0xbdfb6dbb, __VMLINUX_SYMBOL_STR(__fentry__) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

MODULE_ALIAS("platform:ite8516k");

MODULE_INFO(srcversion, "1957C84D80FEEF40D5F3B85");
