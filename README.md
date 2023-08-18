### XXX

## Setup a new project

Simply use `setup.sh` to replace instances of `xxx` and `XXX` with your
project specific names and/or prefixes. This script also renames the files.
```sh
./setup.sh --rename mylib
```

Then `mylib.sh` (Initially `xxx.sh` before calling setup), can be used to
build and install the library `mylib.so` and the executable `mylib-driver`.

If the option `-n` or `--nuke` is also passed to the script, `setup.sh`
self-deletes itself, deletes git history and this `README.md` as well.
```sh
./setup.sh --rename mylib --nuke
```

Use `-h` or `--help` to print the full help message.
```sh
./setup.sh --help
```

## Build this project

This project uses conda to manage dependencies (CMake, clang-format, clang-tidy
and other dependencies for documentation). Dependencies can be installed by
executing following commands after installing [conda](https://docs.conda.io/en/latest/miniconda.html).
```sh
conda env create -f environment-dev.yml
conda activate mylib-dev
```

You can format the source code with `clang-format` (`.c` and `.h` files are
likely to be messy after renaming from `xxx` to `mylib`) using the option
`--format yes`.
```
./mylib.sh --format yes
```

Then you can initialize git, add the files and do the initial commit for the
new project.
```sh
git init
git add .
git commit
```

Then simply run `mylib.sh` script to build and install the library.
```sh
./mylib.sh --docs yes --install yes
```

Use `-h` or `--help` to see all the options supported by `mylib.sh` script.
```
./mylib.sh --help
```
