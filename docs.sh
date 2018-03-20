#!/bin/sh
cd docs/m.css/doxygen
source ./venv/bin/activate
./dox2html5.py ../../Doxyfile-mcss
deactivate
