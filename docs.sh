#!/bin/sh
brew install python
pip -q install virtualenv
cd docs/m.css/doxygen
virtualenv .build
source ./.build/bin/activate
pip install -r requirements.txt
./dox2html5.py ../../Doxyfile-mcss
deactivate
rm -rf .build
