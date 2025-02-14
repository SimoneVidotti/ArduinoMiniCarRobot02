#!/bin/bash
echo "(i am using arch-linux os...)"

read -p "[input](username)> " user
sudo usermod -a -G uucp $user

sudo chmod +x /dev/ttyACM0 && sudo chmod a+rw /dev/ttyACM0

echo "Done."
