  1 #!/bin/bash
  2 
  3 # DHCP IP assignment test script - modified to test connection for: 
  4 # 1)NRT connection
  5 # 2)RT device1, dev2 and dev2-Ethercat connection
  6 
  7 
  8 counter=0
  9 sraCounter=0
 10 
 11 ipLogNrt=$(ping -c 3 169.254.31.10 | grep 'Destination')
 12 
 13 if [[ -z "$ipLogNrt" ]]; then
 14    echo -e "169.254.31.10 ->NRT Connection test passed...\n"
 15 else
 16    echo -e "NRT Connection test failed...\n"
 17 fi
 18 
 19 
 20 for num in {10..20}
 21 do
 22     ipLog=$(ping -c 3 169.254.30.$num | grep 'Destination')
 23     if [[ -z "$ipLog" ]]; then
 24         if [[ $num -eq "10" ]]; then
 25             # echo "${ipLog} - device found"
 26             echo -e "169.254.30.${num} ->CART Control Board DHCP IP address is assigned correctly\n"
 27             ((counter++))
 28         elif [[ $num -eq "11" ]]; then #secondary CART Board IP (ignore)
 29             ((counter++))
 30         elif [[ $num -ge "12" ]]; then
 31             ((sraCounter++))
 32             echo -e "169.254.30.${num} ->SRA$sraCounter DHCP IP address is assigned correctly\n"
 33             ((counter++))
 34             if (( $sraCounter == 2)); then
 35                 break
 36             fi
 37         fi
 38     fi
 39 done
 40 
 41 if (( $counter >= 4 )); then
 42     echo -e "\nDHCP IP assignment test passed...\n"
 43 elif (( $counter == 1 )) | (( $counter == 2 )); then
 44     echo -e "\n Not all devices found DHCP IP assignment test failed..."
 45 else
 46     echo -e "\n\n\ DHCP IP assignment test failed...\n"
 47    # echo $counter
 48 fi
