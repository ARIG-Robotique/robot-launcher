#!/bin/bash

ACTION="init"
ROBOT_NAME=$(cat robot-name)

while [ "${ACTION}" != "exit" ] ; do
    cd
    ./robot-launcher
    cd ${ROBOT_NAME}

    ACTION=$(cat /tmp/robot-action)
    echo "Action : ${ACTION}"

    cd "${ROBOT_NAME}"
    if [ "${ACTION}" == "run" ] ; then
        ./run.sh
    elif [ "${ACTION}" == "monitoring" ] ; then
        ./monitoring.sh
    elif [ "${ACTION}" == "debug" ] ; then
        ./debug.sh
    elif [ "${ACTION}" == "reboot" ] ; then
        sudo reboot
    elif [ "${ACTION}" == "poweroff" ] ; then
        sudo poweroff
    fi
done
