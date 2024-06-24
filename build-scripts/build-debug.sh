#! /bin/bash

# This script generates build files with debug, so a debugger may be used

echo "Creating build directory..."
mkdir -p ../build                 # Create build folder

echo "Moving to build directory..."
cd ../build                       # Go to build folder

echo "Generating build files..."
cmake -DCMAKE_BUILD_TYPE=Debug .. # Generate build files

