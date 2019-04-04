#!/bin/bash

# linux check
if [ ! "$OSTYPE" == "linux-gnu" ]; then
    read -p "boostrap only works on linux. Press any key to exit..." -n1
    exit 1
fi

# y/n prompt
confirmation() {
    read -p "(y/n): " bool
    if [ "$bool" = "y" -o "$bool" = "Y" ]; then
        return 1
    elif [ "$bool" = "n" -o "$bool" = "N" ]; then
        return 0
    else
        echo "bootstrap: $bool is invalid. Exiting..."
        exit 1
    fi
}

# if python 3 is not installed
if [ ! -x "$(command -v python3)" ]; then

    # if NOT in non-prompt mode
    if [[ ! "$@" =~ "-y" ]]; then
        echo "python3 is not installed. Would you like to install?"
        confirmation; shouldInstall=$?

        if [ "$shouldInstall" = 0 ]; then
            echo "Cannot continue without installing. Exiting..."
            exit 1
        fi
    fi

    # docker does not recognize sudo, omitting if already root
    if [ $EUID -ne 0 ]; then
        usr = sudo
    fi

    # install python 3
    $usr apt-get install -y python3
fi

# run python bootstrap script
exec python3 bootstrap.py $@
