#! /bin/bash

stty -F /dev/ttyS3 115200 raw -echo
powershell.exe set-executionpolicy -executionpolicy unrestricted

while :
do
    TEMP=`powershell.exe -File gettemp.ps1 | sed -e 's/\r//'`
    echo $TEMP
    if [ $TEMP -lt 40 ]; then
        echo "fan 10" | tee /dev/ttyS3
    fi
    if [ $TEMP -gt 45 ]; then
        echo "fan 100" | tee /dev/ttyS3
    fi
    sleep 10
done
