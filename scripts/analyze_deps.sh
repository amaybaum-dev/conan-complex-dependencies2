#!/bin/bash

set -e

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

print_status() {
    echo -e "${BLUE}[INFO]${NC} $1"
}

print_success() {
    echo -e "${GREEN}[SUCCESS]${NC} $1"
}

print_warning() {
    echo -e "${YELLOW}[WARNING]${NC} $1"
}

print_error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

print_status "=== Complex Dependencies Analysis ==="
print_status "Analyzing dependency graph with 25+ libraries..."

# Create analysis directory
mkdir -p analysis

# Generate dependency graph
print_status "Generating dependency graph..."
conan graph info . --format=html > analysis/dependency_graph.html
print_success "Dependency graph saved to: analysis/dependency_graph.html"

# List all packages
print_status "Listing all packages..."
conan list "*" --format=table > analysis/package_list.txt
print_success "Package list saved to: analysis/package_list.txt"

# Generate detailed package information
print_status "Generating detailed package information..."
conan list "*" --format=json > analysis/package_details.json
print_success "Package details saved to: analysis/package_details.json"

# Count dependencies
print_status "Counting dependencies..."
TOTAL_PACKAGES=$(conan list "*" --format=table | wc -l)
DIRECT_PACKAGES=$(grep -c "\[requires\]" conanfile.txt || echo "0")
TRANSITIVE_PACKAGES=$((TOTAL_PACKAGES - DIRECT_PACKAGES))

print_status "Dependency Statistics:"
print_status "  Total packages: $TOTAL_PACKAGES"
print_status "  Direct dependencies: $DIRECT_PACKAGES"
print_status "  Transitive dependencies: $TRANSITIVE_PACKAGES"

# Generate dependency tree
print_status "Generating dependency tree..."
conan graph info . --format=text > analysis/dependency_tree.txt
print_success "Dependency tree saved to: analysis/dependency_tree.txt"

# Analyze build requirements
print_status "Analyzing build requirements..."
conan graph info . --format=text | grep -A 20 "Build requirements" > analysis/build_requirements.txt
print_success "Build requirements saved to: analysis/build_requirements.txt"

# Generate summary report
print_status "Generating summary report..."
cat > analysis/summary_report.txt << EOF
Complex Conan Dependencies Analysis Report
=========================================

Generated: $(date)
Project: Complex Dependencies with Deep Transitive Dependencies

Dependency Statistics:
- Total packages: $TOTAL_PACKAGES
- Direct dependencies: $DIRECT_PACKAGES
- Transitive dependencies: $TRANSITIVE_PACKAGES
- Dependency graph depth: 5+ levels

Key Libraries:
- fmt: Formatting library (used by spdlog, nlohmann_json)
- spdlog: Logging library (depends on fmt)
- nlohmann_json: JSON library (depends on fmt)
- boost: Boost libraries (multiple components)
- openssl: Cryptography library
- zlib: Compression library
- bzip2: Compression library
- libiconv: Character encoding
- catch2: Testing framework
- gtest: Google Test framework
- benchmark: Google Benchmark
- protobuf: Protocol Buffers
- grpc: gRPC framework
- abseil: Abseil C++ library
- re2: Regular expression library
- libcurl: HTTP client library
- sqlite3: Database library
- libpng: PNG image library
- libjpeg-turbo: JPEG image library
- freetype: Font rendering library
- harfbuzz: Text shaping library

Transitive Dependencies:
- fmt → used by spdlog, nlohmann_json, benchmark
- zlib → used by boost, openssl, protobuf
- bzip2 → used by boost
- libiconv → used by boost, openssl
- abseil → used by grpc, re2
- protobuf → used by grpc

Files Generated:
- dependency_graph.html: Interactive dependency graph
- package_list.txt: List of all packages
- package_details.json: Detailed package information
- dependency_tree.txt: Dependency tree structure
- build_requirements.txt: Build-time requirements

EOF

print_success "Summary report saved to: analysis/summary_report.txt"

# Display summary
print_status "=== Analysis Summary ==="
print_status "Files generated in 'analysis/' directory:"
ls -la analysis/
print_status ""
print_status "To view the dependency graph, open: analysis/dependency_graph.html"
print_status "To view the summary report: cat analysis/summary_report.txt"
print_status "========================="

print_success "Dependency analysis completed successfully!" 