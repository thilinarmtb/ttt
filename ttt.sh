#!/bin/bash

function print_help() {
  echo "Usage: $0 [options]"
  echo "Options:"
  echo "  -help Print this help message and exit."
  echo "  -cc <compiler> Set the compiler to use for the build."
  echo "  -build-type <Release|Debug> Build type."
  echo "  -build-dir <build directory> Build directory."
  echo "  -install-prefix <install prefix> Install prefix."
  echo "  -enable-docs Enable building documentation."
  echo "  -enable-asan Enable address sanitizer."
  echo "  -install Install the project."
  echo "  -docs Build documentation with Doxygen+Sphinx."
  echo "  -format Format the source code with clang-format."
  echo "  -format-check Check if source formatting is compliant with clang-format."
  echo "  -tidy Run clang-tidy."
}

# Set default values.
: ${TTT_CC:=cc}
: ${TTT_BUILD_TYPE:=Release}
: ${TTT_INSTALL_PREFIX:=`pwd`/install}
: ${TTT_BUILD_DIR:=`pwd`/build}
: ${TTT_ENABLE_DOCS:=OFF}
: ${TTT_ENABLE_ASAN:=OFF}
: ${TTT_INSTALL:=NO}
: ${TTT_DOCS:=NO}
: ${TTT_FORMAT:=NO}
: ${TTT_FORMAT_CHECK:=NO}
: ${TTT_TIDY:=NO}

# Handle command line arguments.
while [[ $# -gt 0 ]]; do
  case $1 in
    -help)
      print_help
      exit 0
      ;;
    -cc)
      TTT_CC="$2"
      shift
      shift
      ;;
    -build-type)
      TTT_BUILD_TYPE="$2"
      shift
      shift
      ;;
    -build-dir)
      TTT_BUILD_DIR="$2"
      shift
      shift
      ;;
    -install-prefix)
      TTT_INSTALL_PREFIX="$2"
      shift
      shift
      ;;
    -enable-docs)
      TTT_ENABLE_DOCS="ON"
      shift
      ;;
    -enable-asan)
      TTT_ENABLE_ASAN="ON"
      shift
      ;;
    -install)
      TTT_INSTALL="YES"
      shift
      ;;
    -docs)
      TTT_DOCS="YES"
      shift
      ;;
    -format)
      TTT_FORMAT="YES"
      shift
      ;;
    -format-check)
      TTT_FORMAT_CHECK="YES"
      shift
      ;;
    -tidy)
      TTT_TIDY="YES"
      shift
      ;;
    *)
      echo "Unknown option: $1"
      print_help
      exit 1
      ;;
  esac
done
  
mkdir -p ${TTT_BUILD_DIR} 2> /dev/null

cmake -DCMAKE_C_COMPILER=${TTT_CC} \
  -DCMAKE_BUILD_TYPE=${TTT_BUILD_TYPE} \
  -DCMAKE_INSTALL_PREFIX=${TTT_INSTALL_PREFIX} \
  -B ${TTT_BUILD_DIR} \
  -DENABLE_DOCS=${TTT_ENABLE_DOCS} \
  -DENABLE_ASAN=${TTT_ENABLE_ASAN} \
  -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
  -S .
  
if [[ "${TTT_FORMAT}" == "YES" ]]; then
  cmake --build ${TTT_BUILD_DIR} --target format -j4
fi

if [[ "${TTT_FORMAT_CHECK}" == "YES" ]]; then
  cmake --build ${TTT_BUILD_DIR} --target format-check -j4
  if [[ $? -ne 0 ]]; then
    echo "Error: clang-format check failed."
    exit 1
  fi
fi

if [[ "${TTT_TIDY}" == "YES" ]]; then
  cmake --build ${TTT_BUILD_DIR} --target tidy -j4
  if [[ $? -ne 0 ]]; then
    echo "Error: clang-tidy failed."
    exit 1
  fi
fi

if [[ ${TTT_DOCS} == "YES" ]]; then
  cmake --build ${TTT_BUILD_DIR} --target docs -j4
  if [[ $? -ne 0 ]]; then
    echo "Error: Building docs with Doxygen+Sphinx failed."
    exit 1
  fi
fi

if [[ "${TTT_INSTALL}" == "YES" ]]; then
  cmake --build ${TTT_BUILD_DIR} --target install -j4
  if [[ $? -ne 0 ]]; then
    echo "Error: Installing failed."
    exit 1
  fi
fi
