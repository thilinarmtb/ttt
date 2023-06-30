### XXX

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
