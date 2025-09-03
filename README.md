# Complex Conan Project with Deep Transitive Dependencies

This project demonstrates Conan's ability to handle complex dependency graphs with deep transitive dependencies. It showcases how Conan resolves, builds, and manages intricate dependency relationships.

## 🏗️ Project Structure

```
conan-complex-dependencies/
├── README.md                    # This file
├── conanfile.txt               # Main project dependencies
├── CMakeLists.txt              # Main CMake configuration
├── src/
│   ├── main.cpp                # Main application
│   ├── data_processor.cpp      # Data processing module
│   └── data_processor.h
├── include/
│   └── data_processor.h
├── test/
│   └── test_data_processor.cpp
├── scripts/
│   ├── build.sh               # Build script
│   ├── analyze_deps.sh        # Dependency analysis script
│   └── clean.sh               # Clean script
└── docs/
    ├── DEPENDENCY_GRAPH.md     # Dependency graph documentation
    └── BUILD_GUIDE.md         # Build guide
```

## 🎯 Key Features

### Complex Dependency Graph
- **Deep transitive dependencies**: Up to 5+ levels deep
- **Multiple dependency paths**: Same library required by different packages
- **Version conflicts**: Automatic resolution by Conan
- **Cross-platform compatibility**: Works on multiple platforms

### Libraries Used
- **fmt**: Formatting library (used by spdlog, nlohmann_json)
- **spdlog**: Logging library (depends on fmt)
- **nlohmann_json**: JSON library (depends on fmt)
- **boost**: Boost libraries (multiple components)
- **openssl**: Cryptography library
- **zlib**: Compression library
- **bzip2**: Compression library
- **libiconv**: Character encoding
- **catch2**: Testing framework
- **gtest**: Google Test framework
- **benchmark**: Google Benchmark
- **protobuf**: Protocol Buffers
- **grpc**: gRPC framework
- **abseil**: Abseil C++ library
- **re2**: Regular expression library

## 🚀 Quick Start

```bash
# Clone or navigate to the project
cd ~/Desktop/conan-complex-dependencies

# Install dependencies
conan install . --output-folder=build --build=missing

# Build the project
./scripts/build.sh

# Run the application
./build/bin/complex_app

# Run tests
./build/bin/test_runner
```

## 📊 Dependency Analysis

### Direct Dependencies
- `fmt/10.2.1` - Formatting
- `spdlog/1.12.0` - Logging
- `nlohmann_json/3.11.2` - JSON processing
- `boost/1.82.0` - Boost libraries
- `openssl/3.2.0` - Cryptography
- `catch2/3.4.0` - Testing
- `benchmark/1.8.3` - Benchmarking
- `protobuf/4.25.1` - Protocol Buffers
- `grpc/1.60.0` - gRPC framework
- `abseil/20240116.2` - Abseil C++ library
- `re2/20231101` - Regular expressions

### Transitive Dependencies
The dependency graph includes:
- **fmt** → used by spdlog, nlohmann_json, benchmark
- **zlib** → used by boost, openssl, protobuf
- **bzip2** → used by boost
- **libiconv** → used by boost, openssl
- **abseil** → used by grpc, re2
- **protobuf** → used by grpc

### Total Dependencies
- **Direct**: 11 libraries
- **Transitive**: 15+ additional libraries
- **Total**: 25+ libraries in the dependency graph

## 🔧 Build Configuration

### Conan Profile
- **Compiler**: Apple Clang 14
- **C++ Standard**: C++17
- **Build Type**: Release
- **Architecture**: arm64

### CMake Configuration
- **Minimum Version**: 3.15
- **C++ Standard**: 17
- **Conan Integration**: CMakeDeps + CMakeToolchain

## 📈 Performance Considerations

### Build Time
- **First build**: ~15-20 minutes (building from source)
- **Subsequent builds**: ~2-3 minutes (using cached packages)
- **Dependency resolution**: ~30 seconds

### Binary Size
- **Debug build**: ~50MB
- **Release build**: ~25MB
- **Stripped**: ~15MB

## 🧪 Testing

```bash
# Run all tests
./build/bin/test_runner

# Run specific test suites
./build/bin/test_runner --gtest_filter=DataProcessorTest.*

# Run benchmarks
./build/bin/benchmark_runner
```

## 📚 Documentation

- [Dependency Graph Analysis](docs/DEPENDENCY_GRAPH.md)
- [Build Guide](docs/BUILD_GUIDE.md)
- [Performance Analysis](docs/PERFORMANCE.md)

## 🔍 Troubleshooting

### Common Issues
1. **Version conflicts**: Conan automatically resolves these
2. **Build failures**: Check compiler compatibility
3. **Memory issues**: Use `--build=missing` for large builds
4. **Cache issues**: Clear Conan cache if needed

### Debug Commands
```bash
# Analyze dependency graph
conan graph info . --format=html > deps.html

# Check package cache
conan list "*" --format=table

# Clean build
./scripts/clean.sh
```

## 🤝 Contributing

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Test thoroughly
5. Submit a pull request

## 📄 License

This project is licensed under the MIT License - see the LICENSE file for details. 