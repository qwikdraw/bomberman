#!/bin/sh

brew update && brew install pkg-config glm glfw cmake
mkdir -p lib
cd lib
git clone --depth 1 https://github.com/skypjack/entt.git
cd ..
