#!/bin/bash
DYLD_INSERT_LIBRARIES=libreplacer.dylib LD_PRELOAD=libreplacer.so ./test $1
