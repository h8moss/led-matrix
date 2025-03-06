#! /bin/bash

# This script generates the build files with the following:
# - Debug, so a debugger may be used
# - DEVLAPTOP, which means it won't use the led matrix and instead will output to the command line for debugging
# - COMPILE_COMMANDS, so clangd may be used to debug the project

echo "Creating build directory..."
mkdir -p ../build                 # Create build folder

echo "Moving to build directory..."
cd ../build                       # Go to build folder

echo "Generating build files..."
cmake -DCMAKE_BUILD_TYPE=Debug -DDEVLAPTOP=1 -DCMAKE_EXPORT_COMPILE_COMMANDS=1 .. # Generate build files

