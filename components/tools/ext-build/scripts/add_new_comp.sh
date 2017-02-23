#!/bin/bash

ROOTDIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
THIS_SCRIPT=$(basename "$0")
TMPL_DIR=$ROOTDIR/template_comp

function usage {
    echo -e "Usage: $THIS_SCRIPT <new component location>"
    exit 1
}

if [ $# -ne 1 ]; then 
    usage
fi

NEW_LOCATION=$1

function getValidation {
    echo -e "Confirm new component copy to ${NEW_LOCATION}"
    echo -e "[y/N]:"
    read var1
}

while true; do
    getValidation

    if [[ $var1 =~ ^[Yy]{1}[Ee]{0,1}[Ss]{0,1}$ ]]; then
        mkdir -p $NEW_LOCATION
        cp -av $TMPL_DIR/* $NEW_LOCATION/
        echo -e "Copy is made, enjoy with new component scheme."
        echo -e "Customize now your component."
        break
    fi
done
