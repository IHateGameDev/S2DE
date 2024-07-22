#!/bin/bash

SCRIPT_DIR=$(dirname "$(readlink -f "$0")")

if [ ! -d "$SCRIPT_DIR/S2DEL/libs/" ]; then
  echo "Directory $SCRIPT_DIR/S2DEL/libs/ does not exist!"
  exit 1
fi

echo "$SCRIPT_DIR/S2DEL/libs/" | sudo tee /etc/ld.so.conf.d/s2de.conf
sudo ldconfig