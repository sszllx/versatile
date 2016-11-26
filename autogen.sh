#!/bin/sh

qmake -qt CONFIG+=debug QMAKE_CXXFLAGS="-Wall -Werror"

make -j8
