#!/bin/bash

# colors
Color_Off='\e[0m'       # Text Reset
Green='\e[0;32m'        # Green

prepare() {
    echo -e "${Green}Process $1${Color_Off}"
    cd $1
    if [ -f preview-snapshot.png ]; then
        echo "crop 48 px from top"
        convert -crop +0+48 preview-snapshot.png preview.png
        rm -v preview-snapshot.png
    else
        echo "noting to do"
    fi
    cd ..
}


# Check each level directory and call prepare
echo -e "${Green}Create previews:${Color_Off}"
for D in *; do
    if [ -d "${D}" ]; then
        prepare ${D}
    fi
done
echo -e "${Green}Done.${Color_Off}"

