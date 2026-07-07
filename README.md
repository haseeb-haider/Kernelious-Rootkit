# Kernelious Rootkit

A DKOM rootkit that targets Windows x64 systems. The driver hooks and modifies critical kernel structures to hide processes, files, and other resources.

## Warning

- This code is Windows kernel driver code and is intended for research or educational purposes only.
- Do not run this driver on production systems.
- Building and testing requires a Windows development environment and the Windows Driver Kit (WDK).

## Repository Notes

- The project includes a Linux-only compatibility shim at `src/KmRootkit/win_compat.h`.
- That shim is only for local syntax validation and does not make the driver functional on Linux.
- The actual build must be done on Windows with the appropriate kernel headers.

## Build Instructions

1. Open `src/KmRootkit/KmRootkit.sln` in Visual Studio on a Windows machine.
2. Select the `x64` platform.
3. Build the solution in `Debug` or `Release` mode.

## Local Validation

- On Linux, you can run a syntax-only check for source files using the compatibility header.
- Example:

  ```bash
  cd src/KmRootkit
  gcc -std=c11 -fsyntax-only -I. *.c
  ```

- The driver is not intended to compile or run on Linux.
