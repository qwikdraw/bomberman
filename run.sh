#!/bin/bash

export DYLD_LIBRARY_PATH=.:$DYLD_LIBRARY_PATH;
export DYLD_LIBRARY_PATH=./lib/irrlkang:$DYLD_LIBRARY_PATH;

./bomberman "$@"
