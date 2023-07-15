### XXX

## Setup a new project

Simply use `setup.sh` to replace instances of `xxx` and `XXX` with your
project specific names and/or prefixes. This script also renames the files.
```sh
./setup.sh --rename mylib
```

Then `mylib.sh` (Originally, `xxx.sh` before calling setup), can be used to
build and install the library `mylib.so` and the executable `mylib_driver`.

If the option `-n` or `--nuke` is also passed to the script, `setup.sh`
self-deletes itself and deletes git history and this `README.md` as well.
```sh
./setup.sh --rename mylib --nuke
```

Pass `-h` or `--help` to print the full help message.
```sh
./setup.sh --help
```

## Build this project

This project uses conda to manage dependencies (CMake, clang-format, and other
dependencies for documentation). Dependencies can be installed by executing the
following commands after installing [conda](https://docs.conda.io/en/latest/miniconda.html).
```sh
conda env create -f environment-dev.yml
conda activate xxx-dev
```
