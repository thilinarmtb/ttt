#!/bin/bash

function print_help() {
  echo "$0 [-r|-rename] <name> [-h|-help] [-n|-nuke]"
  echo ""
  echo "  -h|-help    Print this help message and exit (optional)"
  echo "  -r|-rename  Rename the project to <name> (required)."
  echo "  -n|-nuke    Remove this script, .git directory and README.md (optional)."
}

if [[ $# -eq 0 ]]; then
  print_help
  exit 0
fi

rename=0
name=""
nuke=0
while [[ $# -gt 0 ]]; do
  case "$1" in
    -h|-help)
      print_help
      exit 0
      ;;
    -r|-rename)
      shift
      if [[ $# -eq 0 ]]; then
        echo "Missing argument for option: -r|-rename."
        exit 1
      fi
      name="$1"
      rename=1
      shift
      ;;
    -n|-nuke)
      nuke=1
      shift
      ;;
    *)
      echo "Unknown option: $1"
      exit 1
      ;;
  esac
done

if [[ $rename -eq 1 ]]; then
  NAME=$(echo "${name}" | tr '[:lower:]' '[:upper:]')
  name=$(echo "${name}" | tr '[:upper:]' '[:lower:]')

  git grep -l 'ttt' | grep -v setup.sh | xargs sed -i.bak "s/ttt/${name}/g"
  git grep -l 'TTT' | grep -v setup.sh | xargs sed -i.bak "s/TTT/${NAME}/g"

  len=${#name}
  printf -v underline -- "=%.0s" $(seq $len)
  sed -i.bak "2s/.*/$underline/g" docs/index.rst

  git mv ttt ${name}
  git mv tttcfg ${name}cfg
  git mv src/ttt_impl.c src/${name}_impl.c
  git mv src/ttt.c src/${name}.c
  git mv include/ttt.h include/${name}.h
  git mv include/ttt_impl.h include/${name}_impl.h
  git mv include/ttt_defs.h include/${name}_defs.h
  git mv tests/ttt_test.h tests/${name}_test.h
  git clean -dfx
fi

# Remove this script, .git directory and README.md.
if [[ $nuke -eq 1 ]]; then
  rm -rf -- README.md "$0" .git
fi
