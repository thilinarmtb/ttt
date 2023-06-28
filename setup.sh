#!/bin/bash

if [ $# -lt 1 ]; then
  echo "$0 <libname>"
  exit 1
fi

name=$1
NAME=$(echo "$1" | tr '[:lower:]' '[:upper:]')

git grep -l 'xxx' | grep -v setup.sh | xargs sed -i.bak "s/xxx/${name}/g"
git grep -l 'XXX' | grep -v setup.sh | xargs sed -i.bak "s/XXX/${NAME}/g"
git mv xxx.sh ${name}.sh
git mv src/xxx.c src/${name}.c
git mv src/xxx.h src/${name}.h
git mv src/xxx-impl.h src/${name}-impl.h
git clean -dfx
