# Sonix
A fully functional audiobook player, focusing on increasing playback speed smoothly

# About
There are several subprojects within this repo.


# Installation
To build, first install nlohmann/json to your system. Go to https://github.com/nlohmann/json, and follow it's installation instructions.
Then cd into one of the project directories, make a build directory, run cmake, build with the makefile, and run the binary labeled "sap".
Linux example:

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

    # To build ffmpeg from source (which you *shouldn't* have to do)
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
