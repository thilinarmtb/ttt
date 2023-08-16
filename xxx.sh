#!/bin/bash

function print_help() {
  echo "Usage: $0 [options]"
  echo "Options:"
  echo "  -c|--cc <compiler> Set the compiler to use for the build."
  echo "  -t|--type <Release|Debug> Build type."
  echo "  -p|--prefix <install prefix> Install prefix."
  echo "  -b|--build-dir <build directory> Build directory."
  echo "  -d|--docs <yes|no> Enable or disable building documentation."
  echo "  -i|--install <yes|no> Install the project."
  echo "  -f|--format <yes|no> Format the source code with clang-format."
  echo "  -h|--help Print this help message and exit."
}

# Set default values.
: ${XXX_CC:=cc}
: ${XXX_BUILD_TYPE:=Release}
: ${XXX_INSTALL_PREFIX:=`pwd`/install}
: ${XXX_BUILD_DIR:=`pwd`/build}
: ${XXX_ENABLE_DOCS:=no}
: ${XXX_INSTALL:=yes}
: ${XXX_FORMAT:=no}
: ${XXX_FORMAT_CHECK:=no}
: ${XXX_TIDY:=no}

# Handle command line arguments.
while [[ $# -gt 0 ]]; do
  case $1 in
    -c|--cc)
      XXX_CC="$2"
      shift
      shift
      ;;
    -t|--type)
      XXX_BUILD_TYPE="$2"
      shift
      shift
      ;;
    -p|--prefix)
      XXX_INSTALL_PREFIX="$2"
      shift
      shift
      ;;
    -b|--build-dir)
      XXX_BUILD_DIR="$2"
      shift
      shift
      ;;
    -d|--docs)
      XXX_ENABLE_DOCS="$2"
      shift
      shift
      ;;
    --install)
      XXX_INSTALL="$2"
      shift
      shift
      ;;
    --format)
      XXX_FORMAT="$2"
      shift
      shift
      ;;
    --format-check)
      XXX_FORMAT_CHECK="$2"
      shift
      shift
      ;;
    --tidy)
      XXX_TIDY="$2"
      shift
      shift
      ;;
    -h|--help)
      print_help
      exit 0
      ;;
    *)
      echo "Unknown option: $1"
      print_help
      exit 1
      ;;
  esac
done
  
mkdir -p ${XXX_BUILD_DIR} 2> /dev/null

cmake -DCMAKE_C_COMPILER=${XXX_CC} \
  -DCMAKE_BUILD_TYPE=${XXX_BUILD_TYPE} \
  -DCMAKE_INSTALL_PREFIX=${XXX_INSTALL_PREFIX} \
  -B ${XXX_BUILD_DIR} \
  -DENABLE_DOCS=${XXX_ENABLE_DOCS} \
  -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
  -S . \
  
if [[ "${XXX_FORMAT}" == "yes" ]]; then
  cmake --build ${XXX_BUILD_DIR} --target format -j4
fi

if [[ "${XXX_FORMAT_CHECK}" == "yes" ]]; then
  cmake --build ${XXX_BUILD_DIR} --target format-check -j4
  if [[ $? -ne 0 ]]; then
    echo "Error: clang-format check failed."
    exit 1
  fi
fi

if [[ "${XXX_TIDY}" == "yes" ]]; then
  cmake --build ${XXX_BUILD_DIR} --target tidy -j4
  if [[ $? -ne 0 ]]; then
    echo "Error: clang-tidy failed."
    exit 1
  fi
fi

if [[ ${XXX_ENABLE_DOCS} == "yes" ]]; then
  cmake --build ${XXX_BUILD_DIR} --target Sphinx -j4
  if [[ $? -ne 0 ]]; then
    echo "Error: Building docs with Sphinx failed."
    exit 1
  fi
fi

if [[ "${XXX_INSTALL}" == "yes" ]]; then
  cmake --build ${XXX_BUILD_DIR} --target install -j4
  if [[ $? -ne 0 ]]; then
    echo "Error: Installing failed."
    exit 1
  fi
fi
