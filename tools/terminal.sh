#!/bin/bash

if [ "$(which mate-terminal)" != "" ]
then
    nohup mate-terminal -e "sudo $1"
    echo "sudo $1"
else
    echo "Unable to find terminal"
fi
