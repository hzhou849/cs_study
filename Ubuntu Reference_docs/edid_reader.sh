#!/bin/bash
#this script allows you to readback monitor data based on EDID
# to get the manufacturer and model number.

will require a HEX->ASCII string decoder to get the rest of the information
xrandr --verbose | awk '
/[:.]/ && hex {
    sub(/.*000000fc00/, "", hex)
    hex = substr(hex, 0, 26) "0a"
    sub(/0a.*/, "0a", hex)
    print hex
    hex=""
}
hex {
    gsub(/[ \t]+/, "")
    hex = hex $0
}
/EDID.*:/ {
    hex=" "
}' | xxd -r -p