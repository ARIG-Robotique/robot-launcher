#!/bin/bash

ACTION="init"
ROBOT_NAME=$(cat robot-name)

while [ "${ACTION}" != "exit" ] ; do
    cd
    ./robot-launcher

    ACTION=$(cat /tmp/robot-action)
    echo "Action : ${ACTION}"

    cd "${ROBOT_NAME}"
    if [ "${ACTION}" == "run" ] ; then
        ./run.sh
    elif [ "${ACTION}" == "monitoring" ] ; then
        ./monitoring.sh
    elif [ "${ACTION}" == "debug" ] ; then
        ./debug.sh
    fi
done
