#!/bin/sh

brew update && brew install pkg-config glm glfw cmake
mkdir -p lib
cd lib
git clone https://github.com/alecthomas/entityx.git
cd entityx/entityx
cmake -DENTITYX_BUILD_SHARED=0 -DENTITYX_BUILD_TESTING=0 -DENTITYX_DT_TYPE=double ..
make
cd ../..
