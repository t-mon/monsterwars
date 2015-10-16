#!/bin/bash
width=1200
height=200

ls *.svg | while read file
    do
        destFile=`echo $file | sed 's/\.svg/\.png/'`
        if [ $file == "pillow.svg" ]; then
             echo "------------------------------------------"
             inkscape -f $file -w 200 -h 200 -e $destFile
        else
             echo "------------------------------------------"
             inkscape -f $file -w $width -h $height -e $destFile
        fi
    done
exit 0
