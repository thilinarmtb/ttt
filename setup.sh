#!/bin/bash

function print_help() {
  echo "$0 [-r|--rename] <name> [-h|--help] [-n|--nuke]"
  echo ""
  echo "  -h|--help    Print this help message and exit (optional)"
  echo "  -r|--rename  Rename the project to <name> (required)."
  echo "  -n|--nuke    Remove this script, .git directory and README.md (optional)."
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
    -h|--help)
      print_help
      exit 0
      ;;
    -r|--rename)
      shift
      if [[ $# -eq 0 ]]; then
        echo "Missing argument for option: -r|--rename."
        exit 1
      fi
      name="$1"
      rename=1
      shift
      ;;
    -n|--nuke)
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

  git grep -l 'xxx' | grep -v setup.sh | xargs sed -i.bak "s/xxx/${name}/g"
  git grep -l 'XXX' | grep -v setup.sh | xargs sed -i.bak "s/XXX/${NAME}/g"
  git mv xxx.sh ${name}.sh
  git mv src/xxx-impl.c src/${name}-impl.c
  git mv src/xxx.c src/${name}.c
  git mv include/xxx.h include/${name}.h
  git mv include/xxx-impl.h include/${name}-impl.h
  git mv bin/xxx-driver.c bin/${name}-driver.c
  git clean -dfx
fi

# Remove this script, .git directory and README.md.
if [[ $nuke -eq 1 ]]; then
  rm -rf -- README.md "$0" .git
fi
