#! /bin/bash


sed -i '/GRUB_CMDLINE_LINUX=""/c\GRUB_CMDLINE_LINUX="net.ifnames=0 biosdevname=0"' /etc/default/grub
echo "Config file changed successfully. "

# Generate a new grub config file to save the changes.
sudo grub-mkconfig -o /boot/grub/grub.cfg

reboot