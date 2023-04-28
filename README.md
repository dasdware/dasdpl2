# Dasd Programming Language (DPL)

This repository contains the source code for the `Dasd Programming Language`. This is work in progress. Use at your own risk.

## Bootstrapping and building

After checking out the repository and all it's submodules, you can bootstrap the build executable by executing (Windows only):

```
$ bootstrap.bat
```

The build process uses [nobuild](https://github.com/tsoding/nobuild), for more information, see there.

After the build executable `build.exe` has been created, you can use it to build the compiler itself.

## Running

After the compiler has been created, you can simply run it with the command `dplc.exe`. You can build and run the compiler at the same time using the command `build.exe run`.
