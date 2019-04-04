
https://www.privateinternetaccess.com/helpdesk/kb/articles/how-can-i-uninstall-reinstall-your-application-on-linux

rm -rf ~/.config/PrivateInternetAccess
This next command removes the start or application menu icon (useful if you're just uninstalling the PIA app and not reinstalling it):

rm ~/.local/share/applications/pia_manager.desktop
After that you will then need to remove the following :



sudo rm -rf /opt/pia

 rm -rf ~/.pia_manager
