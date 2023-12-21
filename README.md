# Sonix
A fully functional audiobook player, focusing on increasing playback speed smoothly

## About
I've noticed that there aren't any good open source (or closed source!) audiobook players out there that play regular audiofiles, and none that go over 2x speed without sounding like crap. (The one exception I was able to find is BookPlayer, which is fantastic: https://github.com/TortugaPower/BookPlayer. Sadly, however, it is on iOS only)

Sonix is meant to fill that void. It also does something else, however. It also lets you listen to audiobooks faster than 3.5x speed without just playing the audio faster. Nothing I have ever found can do that, and I want to listen to books faster than that.

Eventually, I want it to be able to play audible .aax files directly, provided you have the authcode bound to your account. Nothing else I've found does that either! This is completely legal, provided they're your audiobooks you've paid for.

## Installation
There are several subprojects within this repo. I could split them up into seperate repos in an organization, but simply putting them in seperate folders works fine for me.

To build, first install nlohmann/json to your system. Go to https://github.com/nlohmann/json, and follow it's installation instructions.
Then cd into one of the project directories, make a build directory, run cmake, build with the makefile, and run the binary labeled "sap". (The project used to be called "SuperSonic Audiobook Player", and I never got around to renaming everything)

For Linux:
```bash
# Make and install nlohmann/json
git clone https://github.com/nlohmann/json
cd json
mkdir build
cd build
cmake ..
make -j$(nproc)
sudo make install

# Install dependancies
sudo dnf install ffmpeg-devel ffmpeg-libs

# To build ffmpeg from source (which you *shouldn't* have to do, but I had to do this at one point, so I kept track of all the packages I had to use)
sudo dnf install ocl-icd-devel SDL2*-devel libcdio-paranoia-devel libcdio cdparanoia libcdio-devel cdparanoia-devel jack-audio-connection-kit-devel jack-mixer mpg123-plugins-jack qjackctl libgcrypt-devel opencv-devel opencc-devel opencl-utils-devel openal-soft-devel zvbi-devel zimg-devel xvidcore-devel x265-devel x264-devel libvpx-devel vo-amrwbenc-devel vid.stab-devel libv4l-devel libva-v4l2-request qv4l2 v4l2ucp baresip-v4l2 libtheora-devel libssh-devel soxr-devel libsmbclient-devel librsvg2-devel rav1e-devel rav1e-devel libopenmpt-devel openjpeg* opencore-amr-devel libmysofa libmysofa-devel libmodplug libmodplug-devel lensfun lensfun-devel gsm-devel glslang glslang-devel libdav1d-devel libdav1d dav1d libbluray libbluray-devel libass libass-devel lilv lilv-devel libaom libaom-devel aom ladspa-devel lmms-devel frei0r-devel srt-devel srt-libs libwebp-devel vapoursynth-devel vapoursynth-libs

# Now build the Qml version
git clone https://github.com/smartycope/Sonix.git
cd Qml
mkdir build
cd build
cmake ..
make -j$(nproc)
cd ..
./sap
```

Note that currently only the minimalist version works. And only on Linux, I'm pretty sure. You may be able to build it for Windows, if you build from source, and write a new build for it. 

The other versions are a work in progress, and the app has essentially been abandoned, for now. I'm very bad at mobile frontend development, I *really* don't want to rewrite everything in Java, and when I was actively working on this project, Qt didn't have great Android export support (at least, not that I could ever figure out). It may be better now, I haven't checked.
