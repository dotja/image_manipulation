# Image Manipulation with C++

Manipulating images programatically. Convert a BGR image to gray scale.

**Ubuntu 20.04**

**Opencv 4.4.0**

### Installation
Check `install.opencv.sh` for installing opencv library.

### Compile and Run
```
g++ -o color_to_gray color_to_gray.cpp `pkg-config opencv4 --cflags --libs`
```

`./color_to_gray color.jpg gray.jpg`
