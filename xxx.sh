#!/bin/bash

: ${XXX_INSTALL_DIR:=`pwd`/install}
: ${XXX_CC:=cc}
: ${XXX_ENABLE_DOCS:=ON}

### Don't touch anything that follows this line. ###
XXX_CURRENT_DIR=`pwd`
XXX_BUILD_DIR=${XXX_CURRENT_DIR}/build

mkdir -p ${XXX_BUILD_DIR} 2> /dev/null

cmake -DCMAKE_C_COMPILER=${XXX_CC} \
  -DCMAKE_INSTALL_PREFIX=${XXX_INSTALL_DIR} \
  -DENABLE_DOCS=${XXX_ENABLE_DOCS} \
  -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
  -B ${XXX_BUILD_DIR} -S ${XXX_CURRENT_DIR}
  
cmake --build ${XXX_BUILD_DIR} --target install -j4
