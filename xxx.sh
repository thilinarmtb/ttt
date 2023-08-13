#!/bin/bash

: ${XXX_CC:=cc}
: ${XXX_ENABLE_DOCS:=OFF}
: ${XXX_BUILD_TYPE:=Debug}
: ${XXX_INSTALL_PREFIX:=`pwd`/install}

### Don't touch anything that follows this line. ###
XXX_CURRENT_DIR=`pwd`
XXX_BUILD_DIR=${XXX_CURRENT_DIR}/build

mkdir -p ${XXX_BUILD_DIR} 2> /dev/null

cmake -DCMAKE_C_COMPILER=${XXX_CC} \
  -DCMAKE_INSTALL_PREFIX=${XXX_INSTALL_PREFIX} \
  -DCMAKE_BUILD_TYPE=${XXX_BUILD_TYPE} \
  -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
  -DENABLE_DOCS=${XXX_ENABLE_DOCS} \
  -B ${XXX_BUILD_DIR} -S ${XXX_CURRENT_DIR}
  
cmake --build ${XXX_BUILD_DIR} --target install -j4
