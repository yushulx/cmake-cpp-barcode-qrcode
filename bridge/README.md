## How to Build the Shared Library on Windows

```bash
mkdir build
cd build
cmake -DCMAKE_GENERATOR_PLATFORM=x64 ..
cmake --build . --config release
```