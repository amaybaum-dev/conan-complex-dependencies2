#!/bin/bash

set -e

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Configuration
BUILD_TYPE="Release"
BUILD_DIR="build"
INSTALL_DIR="install"
JOBS=$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)

# Function to print colored output
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

# Function to check if command exists
command_exists() {
    command -v "$1" >/dev/null 2>&1
}

# Function to check dependencies
check_dependencies() {
    print_status "Checking build dependencies..."
    
    local missing_deps=()
    
    if ! command_exists conan; then
        missing_deps+=("conan")
    fi
    
    if ! command_exists cmake; then
        missing_deps+=("cmake")
    fi
    
    if ! command_exists make; then
        missing_deps+=("make")
    fi
    
    if [ ${#missing_deps[@]} -ne 0 ]; then
        print_error "Missing dependencies: ${missing_deps[*]}"
        print_error "Please install the missing dependencies and try again."
        exit 1
    fi
    
    print_success "All build dependencies are available"
}

# Function to clean build directory
clean_build() {
    if [ "$1" = "--clean" ]; then
        print_status "Cleaning build directory..."
        rm -rf "$BUILD_DIR"
        rm -rf "$INSTALL_DIR"
        print_success "Build directory cleaned"
    fi
}

# Function to install dependencies
install_dependencies() {
    print_status "Installing dependencies with Conan..."
    print_status "This may take 15-20 minutes on first build..."
    print_status "Dependency graph: 25+ libraries, 5+ levels deep"
    
    # Create build directory
    mkdir -p "$BUILD_DIR"
    
    # Install dependencies
    conan install . --output-folder="$BUILD_DIR" --build=missing --profile=default
    
    print_success "Dependencies installed successfully"
}

# Function to configure CMake
configure_cmake() {
    print_status "Configuring CMake..."
    
    cd "$BUILD_DIR"
    
    # Configure with CMake
    cmake .. \
        -DCMAKE_BUILD_TYPE="$BUILD_TYPE" \
        -DCMAKE_INSTALL_PREFIX="../$INSTALL_DIR" \
        -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
    
    cd ..
    
    print_success "CMake configuration completed"
}

# Function to build project
build_project() {
    print_status "Building project..."
    print_status "Build type: $BUILD_TYPE"
    print_status "Jobs: $JOBS"
    print_status "This may take 5-10 minutes..."
    
    cd "$BUILD_DIR"
    
    # Build with multiple jobs
    cmake --build . --config "$BUILD_TYPE" --parallel "$JOBS"
    
    cd ..
    
    print_success "Build completed successfully"
}

# Function to install project
install_project() {
    print_status "Installing project..."
    
    cd "$BUILD_DIR"
    
    cmake --install . --config "$BUILD_TYPE"
    
    cd ..
    
    print_success "Project installed to $INSTALL_DIR"
}

# Function to run tests
run_tests() {
    if [ "$1" = "--test" ]; then
        print_status "Running tests..."
        
        if [ -f "$BUILD_DIR/bin/test_runner" ]; then
            cd "$BUILD_DIR/bin"
            ./test_runner
            cd ../..
            print_success "Tests completed"
        else
            print_warning "Test executable not found, skipping tests"
        fi
    fi
}

# Function to run benchmarks
run_benchmarks() {
    if [ "$1" = "--benchmark" ]; then
        print_status "Running benchmarks..."
        
        if [ -f "$BUILD_DIR/bin/benchmark_runner" ]; then
            cd "$BUILD_DIR/bin"
            ./benchmark_runner
            cd ../..
            print_success "Benchmarks completed"
        else
            print_warning "Benchmark executable not found, skipping benchmarks"
        fi
    fi
}

# Function to run the application
run_application() {
    if [ "$1" = "--run" ]; then
        print_status "Running application..."
        
        if [ -f "$BUILD_DIR/bin/complex_app" ]; then
            cd "$BUILD_DIR/bin"
            ./complex_app
            cd ../..
            print_success "Application completed"
        else
            print_error "Application executable not found"
            exit 1
        fi
    fi
}

# Function to analyze dependencies
analyze_dependencies() {
    if [ "$1" = "--analyze" ]; then
        print_status "Analyzing dependency graph..."
        
        # Generate dependency graph
        conan graph info . --format=html > "$BUILD_DIR/dependency_graph.html"
        
        # List all packages
        conan list "*" --format=table > "$BUILD_DIR/package_list.txt"
        
        print_success "Dependency analysis completed"
        print_status "Dependency graph: $BUILD_DIR/dependency_graph.html"
        print_status "Package list: $BUILD_DIR/package_list.txt"
    fi
}

# Function to show help
show_help() {
    echo "Complex Conan Dependencies Build Script"
    echo ""
    echo "Usage: $0 [OPTIONS]"
    echo ""
    echo "Options:"
    echo "  --clean       Clean build directory before building"
    echo "  --test        Run tests after building"
    echo "  --benchmark   Run benchmarks after building"
    echo "  --run         Run the application after building"
    echo "  --analyze     Analyze dependencies"
    echo "  --help        Show this help message"
    echo ""
    echo "Examples:"
    echo "  $0                    # Build project"
    echo "  $0 --clean            # Clean build and rebuild"
    echo "  $0 --test --run       # Build, test, and run"
    echo "  $0 --analyze          # Analyze dependencies"
}

# Main function
main() {
    print_status "=== Complex Conan Dependencies Build Script ==="
    print_status "Project: Complex Dependencies with Deep Transitive Dependencies"
    print_status "Dependencies: 25+ libraries"
    print_status "Dependency Graph Depth: 5+ levels"
    print_status "================================================"
    
    # Parse arguments
    CLEAN_BUILD=false
    RUN_TESTS=false
    RUN_BENCHMARKS=false
    RUN_APP=false
    ANALYZE_DEPS=false
    
    while [[ $# -gt 0 ]]; do
        case $1 in
            --clean)
                CLEAN_BUILD=true
                shift
                ;;
            --test)
                RUN_TESTS=true
                shift
                ;;
            --benchmark)
                RUN_BENCHMARKS=true
                shift
                ;;
            --run)
                RUN_APP=true
                shift
                ;;
            --analyze)
                ANALYZE_DEPS=true
                shift
                ;;
            --help)
                show_help
                exit 0
                ;;
            *)
                print_error "Unknown option: $1"
                show_help
                exit 1
                ;;
        esac
    done
    
    # Check dependencies
    check_dependencies
    
    # Clean build if requested
    if [ "$CLEAN_BUILD" = true ]; then
        clean_build --clean
    fi
    
    # Install dependencies
    install_dependencies
    
    # Configure CMake
    configure_cmake
    
    # Build project
    build_project
    
    # Install project
    install_project
    
    # Run tests if requested
    if [ "$RUN_TESTS" = true ]; then
        run_tests --test
    fi
    
    # Run benchmarks if requested
    if [ "$RUN_BENCHMARKS" = true ]; then
        run_benchmarks --benchmark
    fi
    
    # Run application if requested
    if [ "$RUN_APP" = true ]; then
        run_application --run
    fi
    
    # Analyze dependencies if requested
    if [ "$ANALYZE_DEPS" = true ]; then
        analyze_dependencies --analyze
    fi
    
    print_success "=== Build Process Completed Successfully ==="
    print_status "Build directory: $BUILD_DIR"
    print_status "Install directory: $INSTALL_DIR"
    print_status "Executables:"
    print_status "  - Main app: $BUILD_DIR/bin/complex_app"
    print_status "  - Tests: $BUILD_DIR/bin/test_runner"
    print_status "  - Benchmarks: $BUILD_DIR/bin/benchmark_runner"
    print_status "  - gRPC example: $BUILD_DIR/bin/grpc_example"
    print_status "============================================="
}

# Run main function with all arguments
main "$@" 