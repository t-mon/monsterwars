#!/bin/bash

# colors
Color_Off='\e[0m'       # Text Reset
Green='\e[0;32m'        # Green

prepare() {
    echo -e "${Green}Process $1${Color_Off}"
    cd $1
    if [ -f preview.png ]; then
        #echo "Resize preview image to with 300"
        cp -v preview-original.png preview.png
        convert preview.png -resize 300 preview.png
        #convert -crop +0+48 preview-snapshot.png preview.png
        #rm -v preview-snapshot.png
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

