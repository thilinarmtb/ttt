#!/bin/bash

function print_help() {
  echo "Usage: $0 [options]"
  echo "Options:"
  echo "  -c|--cc <compiler> Set the compiler to use for the build."
  echo "  -t|--type <Release|Debug> Build type."
  echo "  -p|--prefix <install prefix> Install prefix."
  echo "  -b|--build-dir <build directory> Build directory."
  echo "  -d|--docs <yes|no> Enable or disable building documentation."
  echo "  --install <yes|no> Install the project."
  echo "  --format <yes|no> Format the source code with clang-format."
  echo "  --format-check <yes|no> Check if source formatting is compliant with clang-format."
  echo "  --tidy <yes|no> Run clang-tidy."
  echo "  -h|--help Print this help message and exit."
}

# Set default values.
: ${TTT_CC:=cc}
: ${TTT_BUILD_TYPE:=Release}
: ${TTT_INSTALL_PREFIX:=`pwd`/install}
: ${TTT_BUILD_DIR:=`pwd`/build}
: ${TTT_ENABLE_DOCS:=no}
: ${TTT_INSTALL:=yes}
: ${TTT_FORMAT:=no}
: ${TTT_FORMAT_CHECK:=no}
: ${TTT_TIDY:=no}

# Handle command line arguments.
while [[ $# -gt 0 ]]; do
  case $1 in
    -c|--cc)
      TTT_CC="$2"
      shift
      shift
      ;;
    -t|--type)
      TTT_BUILD_TYPE="$2"
      shift
      shift
      ;;
    -p|--prefix)
      TTT_INSTALL_PREFIX="$2"
      shift
      shift
      ;;
    -b|--build-dir)
      TTT_BUILD_DIR="$2"
      shift
      shift
      ;;
    -d|--docs)
      TTT_ENABLE_DOCS="$2"
      shift
      shift
      ;;
    --install)
      TTT_INSTALL="$2"
      shift
      shift
      ;;
    --format)
      TTT_FORMAT="$2"
      shift
      shift
      ;;
    --format-check)
      TTT_FORMAT_CHECK="$2"
      shift
      shift
      ;;
    --tidy)
      TTT_TIDY="$2"
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
  
mkdir -p ${TTT_BUILD_DIR} 2> /dev/null

cmake -DCMAKE_C_COMPILER=${TTT_CC} \
  -DCMAKE_BUILD_TYPE=${TTT_BUILD_TYPE} \
  -DCMAKE_INSTALL_PREFIX=${TTT_INSTALL_PREFIX} \
  -B ${TTT_BUILD_DIR} \
  -DENABLE_DOCS=${TTT_ENABLE_DOCS} \
  -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
  -S .
  
if [[ "${TTT_FORMAT}" == "yes" ]]; then
  cmake --build ${TTT_BUILD_DIR} --target format -j4
fi

if [[ "${TTT_FORMAT_CHECK}" == "yes" ]]; then
  cmake --build ${TTT_BUILD_DIR} --target format-check -j4
  if [[ $? -ne 0 ]]; then
    echo "Error: clang-format check failed."
    exit 1
  fi
fi

if [[ "${TTT_TIDY}" == "yes" ]]; then
  cmake --build ${TTT_BUILD_DIR} --target tidy -j4
  if [[ $? -ne 0 ]]; then
    echo "Error: clang-tidy failed."
    exit 1
  fi
fi

if [[ ${TTT_ENABLE_DOCS} == "yes" ]]; then
  cmake --build ${TTT_BUILD_DIR} --target Sphinx -j4
  if [[ $? -ne 0 ]]; then
    echo "Error: Building docs with Sphinx failed."
    exit 1
  fi
fi

if [[ "${TTT_INSTALL}" == "yes" ]]; then
  cmake --build ${TTT_BUILD_DIR} --target install -j4
  if [[ $? -ne 0 ]]; then
    echo "Error: Installing failed."
    exit 1
  fi
fi
