#-----------------------------------------------------------
#---- system packages

sudo apt install build-essential
sudo apt install cmake
sudo apt install pkg-config
sudo apt install libgtk-3-dev
sudo apt install libavcodec-dev
sudo apt install libavformat-dev
sudo apt install libswscale-dev
sudo apt install libv4l-dev
sudo apt install libxvidcore-dev
sudo apt install libx264-dev
sudo apt install libjpeg-dev
sudo apt install libpng-dev
sudo apt install libtiff-dev
sudo apt install gfortran
sudo apt install openexr
sudo apt install libatlas-base-dev
sudo apt install python3-dev
sudo apt install python3-numpy
sudo apt install libtbb2
sudo apt install libtbb-dev
sudo apt install libdc1394-22-dev
sudo apt install libopenexr-dev
sudo apt install libgstreamer-plugins-base1.0-dev
sudo apt install libgstreamer1.0-dev

#-----------------------------------------------------------
#---- clone the latest opencv source code

mkdir ~/my_opencv && cd ~/my_opencv
git clone https://github.com/opencv/opencv.git
git clone https://github.com/opencv/opencv_contrib.git


#-----------------------------------------------------------
#---- build and make

cd ~/opencv
mkdir -p build && cd build

cmake .. -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local -D OPENCV_GENERATE_PKGCONFIG=ON -D OPENCV_EXTRA_MODULES_PATH=~/my_opencv/opencv_contrib/modules

## specify the number of processors you want to use
make -j$(nproc)

sudo make install

#-----------------------------------------------------------
#---- check the versions you've installed

pkg-config --modversion opencv4
python3 -c "import cv2; print(cv2.__version__)"


#-----------------------------------------------------------
#---- notes:

# the <include> files should be in /usr/local/include/opencv2
# cp them there if necessary


#-----------------------------------------------------------
#---- extras for running opencv in C++:

sudo apt install libopencv-dev
sudo apt install apt-file
sudo apt-file update
sudo apt list --upgradable

ls /usr/local/lib/pkgconfig/
## it will output: opencv4

apt-file search opencv4.pc
## it will output: /usr/lib/x86_64-linux-gnu/pkgconfig/opencv4.pc
export PKG_CONFIG_PATH=/usr/lib/x86_64-linux-gnu/pkgconfig/opencv4.pc

#-----------------------------------------------------------
#---- compiling the C++ code:

g++ -o script script.cpp `pkg-config opencv4 --cflags --libs`



