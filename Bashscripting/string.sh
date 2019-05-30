#compare wildcard search substring
# if [[ "$firmware_ver" == *"$check_ver"* ]]; then

#remove match substring up to x characters
mac_address 01:23:45:67
mac_address=${mac_address#*3}
will print starting at the 4th character


#print at a a start/stop position of string (substring)
example:
 cuts from position start 2nd character stop at 10th character

command:
	awk '{print substr(<string in>, <start>, <stop>)}'
$0 - is the string passed in
echo "9a: adfadfaf" | grep 9a: | awk '{print substr($0, 2, 10)}'





