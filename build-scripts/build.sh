#! /bin/bash

# This script generates the build files for release

echo "Creating build directory..."
mkdir -p ../build                 # Create build folder

echo "Moving to build directory..."
cd ../build                       # Go to build folder

echo "Generating build files..."
cmake -DCMAKE_BUILD_TYPE=Release .. # Generate build files

