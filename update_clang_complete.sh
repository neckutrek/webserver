#!/bin/bash
rm -rf build/
mkdir build
cd build
CXX="$HOME/.vim/bin/cc_args.py g++" cmake ..
make
cp ./src/.clang_complete ../.clang_complete
cd ..
rm -rf build/
cmake -B build
