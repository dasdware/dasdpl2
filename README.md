# Dasd Programming Language (DPL)

This repository contains the source code for the `Dasd Programming Language`. This is work in progress. Use at your own risk.

## Bootstrapping and building

After checking out the repository and all its submodules, you can bootstrap the build executable by executing (to date, tested under Windows only):

```
$ gcc -o nobuild.exe nobuild.c
```

The build process uses [nobuild](https://github.com/tsoding/nobuild), for more information, see there.

After the build executable `nobuild.exe` has been created, you can use it to build the compiler itself. It supports the following subcommands:

```
$ nobuild.exe compile ; Creates dplc
$ nobuild.exe run     ; Creates dplc and runs it directly
$ nobuild.exe test    ; Creates the tests executable and  runs it
```

## Running

After the compiler has been created, you can simply run it with the command `dplc.exe`. You can build and run the compiler at the same time using the command `nobuild.exe run`.
