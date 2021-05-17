#!/bin/bash
if [[ `hostname` == "login"* ]]; then
    echo "ERROR: you are on a login node - use make on a 'submit' target to run on the right type of node"
    exit 1
fi
exit 0

