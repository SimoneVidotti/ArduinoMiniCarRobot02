#!/bin/bash
echo "(i am using debian based...)"

read -p "[input](username)> " user
sudo usermod -a -G dialout $user

sudo chmod +x /dev/ttyACM0 && sudo chmod a+rw /dev/ttyACM0

echo "Done."