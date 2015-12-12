#!/usr/bin/env bash

PACKAGES="sdl2 sfml-all"
LIBS=`pkg-config --libs ${PACKAGES}`
CFLAGS=`pkg-config --cflags ${PACKAGES}`

mkdir -p Debug
g++ -std=c++11 -g ${CFLAGS}   src/*.cpp ${LIBS} -o Debug/shaderbasis
