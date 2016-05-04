#!/bin/bash
DYLD_FORCE_FLAT_NAMESPACE=1 DYLD_INSERT_LIBRARIES=libreplacer.dylib LD_PRELOAD=libreplacer.so ./test $1
