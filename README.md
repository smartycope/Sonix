# SuperSonic-Audiobook-Player
A fully functional audiobook player, focusing on increasing playback speed smoothly

# About
There are several subprojects within this repo.


# Installation
To build, first install nlohmann/json to your system. Go to https://github.com/nlohmann/json, and follow it's installation instructions.
Then cd into one of the project directories, make a build directory, run cmake, build with the makefile, and run the binary labeled "sap".
Linux example:

#Make and install nlohmann/json
git clone https://github.com/nlohmann/json \n
cd json
mkdir build
cd build
cmake ..
make -j$(nproc)
sudo make install

#Now build the desktop version
git clone https://github.com/smartycope/SuperSonic-Audiobook-Player.git
cd Desktop
mkdir build
cd build
cmake ..
make -j$(nproc)
cd ..
./sap
