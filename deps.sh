#!/bin/sh

brew install pkg-config glm glfw wget
mkdir -p lib
cd lib
git clone --depth 1 https://github.com/skypjack/entt.git
mkdir -p lodepng
cd lodepng
wget https://raw.githubusercontent.com/lvandeve/lodepng/master/lodepng.cpp
wget https://raw.githubusercontent.com/lvandeve/lodepng/master/lodepng.h
cd ..
git clone --depth 1 https://github.com/logankaser/irrklang.git
cd ..
rm -rf assets
git clone --depth 1 https://github.com/logankaser/bomberman-assets.git assets
