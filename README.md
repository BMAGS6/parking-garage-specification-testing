# Specification Testing in C

[![C23](https://img.shields.io/badge/C-23-00599C?style=flat-square&logo=c&logoColor=white)](https://www.open-std.org/jtc1/sc22/wg14/)
[![cmocka](https://img.shields.io/badge/testing-cmocka-2E7D32?style=flat-square)](https://cmocka.org/)
[![CMake](https://img.shields.io/badge/build-CMake-064F8C?style=flat-square&logo=cmake&logoColor=white)](https://cmake.org/)
[![Doxygen](https://img.shields.io/badge/documentation-Doxygen-2C4AA8?style=flat-square)](https://www.doxygen.nl/)
[![License: zlib](https://img.shields.io/badge/license-zlib-blue?style=flat-square)](LICENSE)

Brandon Magoni -- CSIS3106: Software Verification, Validation, Testing and Security

October, 2026

This lesson derives twelve tests from a parking-charge specification and 
automates them with cmocka. The accompanying PowerPoint contains the lesson and 
full narration notes.

## Specification

The public function is `int parking_charge_cents(int minutes)`.

| Requirement              | Behavior                                                |
| ------------------------ | ------------------------------------------------------- |
| Accepted input           | Whole minutes, 0 through 1440 inclusive                 |
| Invalid input            | Return -1 when minutes is negative or greater than 1440 |
| Zero minutes             | Return 0                                                |
| First started hour       | 1 through 60 minutes costs 500 cents                    |
| Additional started hours | Add 200 cents per additional started hour               |
| Maximum stay             | 1440 minutes, costing 5100 cents; no daily cap          |

All charges use integer cents.

## Files

- `include/parking.h`: public interface and contract.
- `src/parking.c`: correct implementation.
- `tests/test_parking.c`: twelve named cmocka tests and the test runner.
- `demo/parking_buggy.c`: deliberate exact-hour boundary defect.
- `CMakeLists.txt`: C23 build and CTest registration.
- `NARRATION.md`: a copy of the PowerPoint speaker notes.
- `RECORDING_GUIDE.md`: commands and recording sequence.
- `results/`: actual verbose CTest output from both versions, captured on Linux. 
Paths and timings will differ on your computer.

## Build and test

Use the MSYS2 **UCRT64** terminal when on Windows. GCC, cmocka, CMake, and Ninja
must be installed and on PATH. 
Run commands from the folder containing `CMakeLists.txt`, not its parent folder.


```bash
cmake -S . -B build -G Ninja -DDEMO_BUG=OFF
cmake --build build
ctest --test-dir build --verbose
```

Expected: twelve cmocka cases pass, and CTest reports 1/1 executables passed. 
`--verbose` shows cmocka output even when the executable succeeds. 
`--output-on-failure` alone suppresses the detailed output on a passing run.

## Deliberate failure and correction

```bash
cmake -S . -B build -DDEMO_BUG=ON
cmake --build build
ctest --test-dir build --verbose
```

Expected: nine cases pass and three fail at 60, 120, and 1440 minutes. CTest 
returns nonzero; this is the intended demonstration. The compiler should still 
succeed. `DEMO_BUG=ON` selects `demo/parking_buggy.c` instead of 
`src/parking.c`. It does not change the tests or mark the failure as an expected
CTest pass.

Restore the correct version:

```bash
cmake -S . -B build -DDEMO_BUG=OFF
cmake --build build
ctest --test-dir build --verbose
```

Expected: twelve cases pass again. The correction is `(minutes - 1) / 60` in place of `minutes / 60`.

For a literal edit during the recording, enable `DEMO_BUG`, run the failure, 
change the faulty line in `demo/parking_buggy.c` to `(minutes - 1) / 60`, save, 
rebuild, and rerun. Explain that this edits the demonstration copy. Switching 
the option OFF restores the untouched production source.

## Troubleshooting

If CMake cannot find cmocka, confirm that you opened UCRT64 and are using the 
UCRT64 GCC and cmocka installation. To specify a nonstandard installation, 
configure with `-DCMAKE_PREFIX_PATH=/path/to/prefix` or explicitly set 
`CMOCKA_INCLUDE_DIR` and `CMOCKA_LIBRARY`. The project does not download dependencies.

If an old `build` folder uses a different generator or compiler, use a fresh 
directory such as `build-lesson` in all three commands. Do not reuse build 
folders from another project. Keep the UCRT64 terminal open when running tests 
so the cmocka DLL is on PATH. These instructions use Ninja, a 
single-configuration generator.

## Verification

The supplied project was built and run with GCC 13.3.0, CMake 4.4.4, 
Ninja 1.13.2, and cmocka 1.1.8 on Linux. The actual logs show twelve passes for 
the corrected version and the three intended boundary failures for the buggy version.

## References

- ISTQB. *Certified Tester Foundation Level Syllabus*, v4.0.1, sections 4.1, 4.2.1, 4.2.2. https://istqb.org/wp-content/uploads/2024/11/ISTQB_CTFL_Syllabus_v4.0.1.pdf
- cmocka, *Running Tests*. https://api.cmocka.org/group__cmocka__exec.html
- cmocka, *Assert Macros*. https://api.cmocka.org/group__cmocka__asserts.html
- CMake, *ctest manual*. https://cmake.org/cmake/help/latest/manual/ctest.1.html
