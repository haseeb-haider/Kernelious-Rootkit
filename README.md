# Kernelious Rootkit

A DKOM rootkit that targets Windows x64 systems. The driver hooks and modifies critical kernel structures to hide processes, files, and other resources.

## Warning

- This code is Windows kernel driver code and is intended for research or educational purposes only.
- Do not run this driver on production systems.
- Building and testing requires a Windows development environment and the Windows Driver Kit (WDK).

## Repository Notes

- The project includes a Linux-only compatibility shim at `src/KmRootkit/win_compat.h`.
- That shim is only for local syntax validation and does not make the driver functional on Linux.
- The solution and project include `x64` and `ARM64` configurations, but the repo does not contain prebuilt driver binaries.
- The actual build must be done on Windows with the appropriate kernel headers.

## Build Instructions

1. Open `src/KmRootkit.sln` in Visual Studio on a Windows machine.
2. Select the `x64` platform.
3. Build the solution in `Debug` or `Release` mode.
4. If you receive `C1083`, install the Windows Driver Kit (WDK) and reopen the solution.

## WDK Check and Build Scripts

- `check-wdk.ps1` verifies MSBuild and WDK headers.
- `build-driver.ps1` runs the WDK check and then builds `src/KmRootkit.sln`.
- Example on Windows PowerShell:

  ```powershell
  .\check-wdk.ps1
  .\build-driver.ps1 -Configuration Release -Platform x64
  ```

## GitHub Actions

- The repository includes a Windows build workflow at `.github/workflows/build-windows.yml`.
- It checks for MSBuild and WDK headers, then attempts to build the solution and verify the `.sys` output.

## Local Validation

- On Linux, you can still run a syntax-only check for source files using the compatibility header.
- Example:

  ```bash
  cd src/KmRootkit
  gcc -std=c11 -fsyntax-only -I. *.c
  ```

- The driver is not intended to compile or run on Linux.
