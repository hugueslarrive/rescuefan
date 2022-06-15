#! /bin/bash

stty -F /dev/ttyS3 115200 raw -echo
powershell.exe set-executionpolicy -executionpolicy unrestricted

while :
do
    TEMP=`powershell.exe -File gettemp.ps1 | sed -e 's/\r//'`
    echo $TEMP
    if [ $TEMP -lt 40 ]; then
        echo "speed_down" | tee /dev/ttyS3
    fi
    if [ $TEMP -gt 40 ]; then
        echo "speed_up" | tee /dev/ttyS3
    fi
    sleep 1
done
