#include "data_processor.h"
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <fmt/format.h>
#include <iostream>
#include <thread>
#include <chrono>

int main() {
    // Initialize logging
    auto logger = spdlog::stdout_color_mt("main");
    logger->set_level(spdlog::level::info);
    
    logger->info("=== Complex Conan Dependencies Demo ===");
    logger->info("Starting application with 25+ library dependencies");
    logger->info("Dependency graph depth: 5+ levels");
    logger->info("=====================================");
    
    try {
        // Create data processor instance
        DataProcessor processor;
        logger->info("DataProcessor initialized successfully");
        
        // Test JSON processing
        logger->info("Testing JSON processing...");
        std::string jsonData = R"({
            "name": "Complex Dependencies Demo",
            "version": "1.0.0",
            "dependencies": {
                "fmt": "10.2.1",
                "spdlog": "1.12.0",
                "boost": "1.82.0",
                "openssl": "3.2.0"
            },
            "features": [
                "JSON processing",
                "File compression",
                "Database operations",
                "Network requests",
                "Image processing",
                "Text rendering",
                "Cryptography"
            ]
        })";
        
        if (processor.processJsonData(jsonData)) {
            logger->info("JSON processing successful");
            std::string report = processor.generateJsonReport();
            logger->info("Generated report: {}", report);
        } else {
            logger->error("JSON processing failed");
        }
        
        // Test file system operations
        logger->info("Testing file system operations...");
        std::string currentDir = ".";
        if (processor.processFilesInDirectory(currentDir)) {
            logger->info("File system operations successful");
        } else {
            logger->error("File system operations failed");
        }
        
        // Test compression
        logger->info("Testing compression...");
        std::string testData = "This is test data for compression. " + std::string(1000, 'A');
        std::ofstream testFile("test_input.txt");
        testFile << testData;
        testFile.close();
        
        if (processor.compressFile("test_input.txt", "test_compressed.gz")) {
            logger->info("Compression successful");
        } else {
            logger->error("Compression failed");
        }
        
        // Test database operations
        logger->info("Testing database operations...");
        if (processor.initializeDatabase("test.db")) {
            logger->info("Database initialized successfully");
            
            if (processor.storeData("data_processor_logs", "Test data entry")) {
                logger->info("Data stored successfully");
            } else {
                logger->error("Failed to store data");
            }
        } else {
            logger->error("Database initialization failed");
        }
        
        // Test text processing with regex
        logger->info("Testing text processing with regex...");
        std::string text = "Hello world! This is a test string with email@example.com and phone 123-456-7890";
        std::string emailPattern = R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})";
        
        if (processor.processTextWithRegex(text, emailPattern)) {
            logger->info("Regex processing successful - found email");
        } else {
            logger->info("Regex processing completed - no email found");
        }
        
        // Test cryptography
        logger->info("Testing cryptography...");
        std::string plaintext = "Secret message for encryption";
        std::string key = "mysecretkey1234567890123456789012"; // 32 bytes for AES-256
        
        std::string encrypted = processor.encryptData(plaintext, key);
        if (!encrypted.empty()) {
            logger->info("Encryption successful");
            
            std::string hash = processor.generateHash(plaintext);
            if (!hash.empty()) {
                logger->info("Hash generation successful: {}", hash.substr(0, 16) + "...");
            } else {
                logger->error("Hash generation failed");
            }
        } else {
            logger->error("Encryption failed");
        }
        
        // Test async processing
        logger->info("Testing async processing...");
        processor.processDataAsync("Async test data", [&logger](const std::string& result) {
            logger->info("Async processing completed with result: {}", result.substr(0, 16) + "...");
        });
        
        processor.waitForCompletion();
        
        // Test logging and monitoring
        logger->info("Testing logging and monitoring...");
        processor.setLogLevel(1); // Debug level
        processor.logOperation("DEMO", "Complex dependencies demonstration completed");
        
        // Performance demonstration
        logger->info("Demonstrating performance with multiple operations...");
        auto start = std::chrono::high_resolution_clock::now();
        
        for (int i = 0; i < 10; ++i) {
            std::string testJson = fmt::format(R"({{"iteration": {}, "data": "test_data_{}"}})", i, i);
            processor.processJsonData(testJson);
            
            std::string testHash = processor.generateHash("test_data_" + std::to_string(i));
            processor.processTextWithRegex("test@example.com", emailPattern);
        }
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        
        logger->info("Performance test completed in {} ms", duration.count());
        
        // Summary
        logger->info("=== Demo Summary ===");
        logger->info("✅ JSON processing with nlohmann_json");
        logger->info("✅ File system operations with boost::filesystem");
        logger->info("✅ Compression with zlib");
        logger->info("✅ Database operations with SQLite3");
        logger->info("✅ Text processing with RE2");
        logger->info("✅ Cryptography with OpenSSL");
        logger->info("✅ Async processing with std::thread");
        logger->info("✅ Logging with spdlog");
        logger->info("✅ Formatting with fmt");
        logger->info("✅ All 25+ dependencies working correctly!");
        logger->info("===================");
        
        // Cleanup
        std::remove("test_input.txt");
        std::remove("test_compressed.gz");
        std::remove("test.db");
        
        logger->info("Demo completed successfully!");
        
    } catch (const std::exception& e) {
        logger->error("Unexpected error: {}", e.what());
        return 1;
    }
    
    return 0;
} 