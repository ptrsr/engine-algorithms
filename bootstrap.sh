#!/bin/bash

# parameter fetching function
# https://stackoverflow.com/questions/16654607/using-getopts-inside-a-bash-function
process() {
    error() {
        echo -e "Exiting..."
        exit 1
    }

    while getopts "dtrn" opt; do
        case "$opt" in
            d ) d=true ;;
            t ) t=true ;;
            r ) r=true ;;
            n ) n=true ;;
            [?] ) error "$opt";; # Print helpFunction in case parameter is non-existent
        esac
    done


    if [ -x "$(command -v git)" ]; then
        echo 'Error: git is not installed.' >&2
        exit 1
    fi
}

# if commands were given directly from the shell, execute
if [ $# -ne 0 ]; then
    process $@
    exit 0
fi

echo -e "Created by Ruud Peters (ruud_peters96@hotmail.com)"

echo -e "
INFO
Setup project for engine algorithms course."

echo -e "
COMMANDS
-d      - run in docker
-t      - run tests (after building)
-r      - release mode (debug default)
-n      - non interactive (will install all
        neccessary software for boostrapping)"

echo -e "
Press enter immediately to exit.
Add commands and press enter to run setup.
Running this script with commands from the shell is also possible.
"

read -p "Command(s): `echo $'\n> '`" input

# if no commands were given, exit
if [ -z "$input" ]; then
    exit 0
fi

process "$input"


#echo "$parameterA"

#read -p "Press any key to continue..."
