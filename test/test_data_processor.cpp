#include "data_processor.h"
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include <gtest/gtest.h>
#include <spdlog/spdlog.h>
#include <fmt/format.h>
#include <iostream>
#include <fstream>
#include <sstream>

// Catch2 Tests
TEST_CASE("DataProcessor JSON Processing", "[json]") {
    DataProcessor processor;
    
    SECTION("Valid JSON processing") {
        std::string validJson = R"({"name": "test", "value": 42})";
        REQUIRE(processor.processJsonData(validJson) == true);
    }
    
    SECTION("Invalid JSON processing") {
        std::string invalidJson = R"({"name": "test", "value": 42)"; // Missing closing brace
        REQUIRE(processor.processJsonData(invalidJson) == false);
    }
    
    SECTION("JSON report generation") {
        std::string report = processor.generateJsonReport();
        REQUIRE(!report.empty());
        REQUIRE(report.find("timestamp") != std::string::npos);
        REQUIRE(report.find("status") != std::string::npos);
    }
}

TEST_CASE("DataProcessor File Operations", "[filesystem]") {
    DataProcessor processor;
    
    SECTION("Directory processing") {
        REQUIRE(processor.processFilesInDirectory(".") == true);
    }
    
    SECTION("Compression") {
        // Create test file
        std::ofstream testFile("test_compress.txt");
        testFile << "Test data for compression";
        testFile.close();
        
        REQUIRE(processor.compressFile("test_compress.txt", "test_compressed.gz") == true);
        
        // Cleanup
        std::remove("test_compress.txt");
        std::remove("test_compressed.gz");
    }
}

TEST_CASE("DataProcessor Database Operations", "[database]") {
    DataProcessor processor;
    
    SECTION("Database initialization") {
        REQUIRE(processor.initializeDatabase("test_db.db") == true);
        
        SECTION("Data storage") {
            REQUIRE(processor.storeData("data_processor_logs", "Test data") == true);
        }
        
        // Cleanup
        std::remove("test_db.db");
    }
}

TEST_CASE("DataProcessor Text Processing", "[text]") {
    DataProcessor processor;
    
    SECTION("Regex processing") {
        std::string text = "Hello world! Contact: test@example.com";
        std::string emailPattern = R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})";
        
        REQUIRE(processor.processTextWithRegex(text, emailPattern) == true);
    }
    
    SECTION("Invalid regex pattern") {
        std::string text = "Hello world!";
        std::string invalidPattern = R"([invalid)"; // Unclosed bracket
        
        REQUIRE(processor.processTextWithRegex(text, invalidPattern) == false);
    }
}

TEST_CASE("DataProcessor Cryptography", "[crypto]") {
    DataProcessor processor;
    
    SECTION("Data encryption") {
        std::string plaintext = "Secret message";
        std::string key = "mysecretkey1234567890123456789012"; // 32 bytes
        
        std::string encrypted = processor.encryptData(plaintext, key);
        REQUIRE(!encrypted.empty());
        REQUIRE(encrypted != plaintext);
    }
    
    SECTION("Hash generation") {
        std::string data = "Test data for hashing";
        std::string hash = processor.generateHash(data);
        
        REQUIRE(!hash.empty());
        REQUIRE(hash.length() == 64); // SHA-256 hash length
    }
    
    SECTION("Hash consistency") {
        std::string data = "Consistent hash test";
        std::string hash1 = processor.generateHash(data);
        std::string hash2 = processor.generateHash(data);
        
        REQUIRE(hash1 == hash2);
    }
}

TEST_CASE("DataProcessor Async Operations", "[async]") {
    DataProcessor processor;
    
    SECTION("Async processing") {
        bool callbackCalled = false;
        std::string result;
        
        processor.processDataAsync("Async test data", [&callbackCalled, &result](const std::string& asyncResult) {
            callbackCalled = true;
            result = asyncResult;
        });
        
        processor.waitForCompletion();
        
        REQUIRE(callbackCalled == true);
        REQUIRE(!result.empty());
    }
}

TEST_CASE("DataProcessor Error Handling", "[errors]") {
    DataProcessor processor;
    
    SECTION("Error state") {
        REQUIRE(processor.hasErrors() == false);
        REQUIRE(processor.getLastError().empty());
    }
    
    SECTION("Error clearing") {
        processor.clearErrors();
        REQUIRE(processor.hasErrors() == false);
    }
}

TEST_CASE("DataProcessor Logging", "[logging]") {
    DataProcessor processor;
    
    SECTION("Log level setting") {
        processor.setLogLevel(0); // Trace level
        REQUIRE_NOTHROW(processor.logOperation("TEST", "Log test"));
    }
    
    SECTION("Operation logging") {
        REQUIRE_NOTHROW(processor.logOperation("TEST_OP", "Test operation details"));
    }
}

// Google Test Tests
class DataProcessorTest : public ::testing::Test {
protected:
    void SetUp() override {
        processor_ = std::make_unique<DataProcessor>();
    }
    
    void TearDown() override {
        processor_.reset();
    }
    
    std::unique_ptr<DataProcessor> processor_;
};

TEST_F(DataProcessorTest, JsonProcessingWorks) {
    std::string validJson = R"({"test": "data", "number": 123})";
    EXPECT_TRUE(processor_->processJsonData(validJson));
}

TEST_F(DataProcessorTest, JsonProcessingFailsWithInvalidJson) {
    std::string invalidJson = R"({"test": "data", "number": 123)"; // Missing closing brace
    EXPECT_FALSE(processor_->processJsonData(invalidJson));
}

TEST_F(DataProcessorTest, JsonReportGeneration) {
    std::string report = processor_->generateJsonReport();
    EXPECT_FALSE(report.empty());
    EXPECT_NE(report.find("timestamp"), std::string::npos);
    EXPECT_NE(report.find("status"), std::string::npos);
}

TEST_F(DataProcessorTest, FileSystemOperations) {
    EXPECT_TRUE(processor_->processFilesInDirectory("."));
}

TEST_F(DataProcessorTest, CompressionWorks) {
    // Create test file
    std::ofstream testFile("gtest_compress.txt");
    testFile << "Test data for compression in GTest";
    testFile.close();
    
    EXPECT_TRUE(processor_->compressFile("gtest_compress.txt", "gtest_compressed.gz"));
    
    // Cleanup
    std::remove("gtest_compress.txt");
    std::remove("gtest_compressed.gz");
}

TEST_F(DataProcessorTest, DatabaseOperations) {
    EXPECT_TRUE(processor_->initializeDatabase("gtest_db.db"));
    EXPECT_TRUE(processor_->storeData("data_processor_logs", "GTest data"));
    
    // Cleanup
    std::remove("gtest_db.db");
}

TEST_F(DataProcessorTest, RegexProcessing) {
    std::string text = "Hello world! Email: test@example.com";
    std::string emailPattern = R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})";
    
    EXPECT_TRUE(processor_->processTextWithRegex(text, emailPattern));
}

TEST_F(DataProcessorTest, InvalidRegexPattern) {
    std::string text = "Hello world!";
    std::string invalidPattern = R"([invalid)"; // Unclosed bracket
    
    EXPECT_FALSE(processor_->processTextWithRegex(text, invalidPattern));
}

TEST_F(DataProcessorTest, EncryptionWorks) {
    std::string plaintext = "Secret message for GTest";
    std::string key = "mysecretkey1234567890123456789012"; // 32 bytes
    
    std::string encrypted = processor_->encryptData(plaintext, key);
    EXPECT_FALSE(encrypted.empty());
    EXPECT_NE(encrypted, plaintext);
}

TEST_F(DataProcessorTest, HashGeneration) {
    std::string data = "Test data for hashing in GTest";
    std::string hash = processor_->generateHash(data);
    
    EXPECT_FALSE(hash.empty());
    EXPECT_EQ(hash.length(), 64); // SHA-256 hash length
}

TEST_F(DataProcessorTest, HashConsistency) {
    std::string data = "Consistent hash test for GTest";
    std::string hash1 = processor_->generateHash(data);
    std::string hash2 = processor_->generateHash(data);
    
    EXPECT_EQ(hash1, hash2);
}

TEST_F(DataProcessorTest, AsyncProcessing) {
    bool callbackCalled = false;
    std::string result;
    
    processor_->processDataAsync("Async test data for GTest", 
                                [&callbackCalled, &result](const std::string& asyncResult) {
        callbackCalled = true;
        result = asyncResult;
    });
    
    processor_->waitForCompletion();
    
    EXPECT_TRUE(callbackCalled);
    EXPECT_FALSE(result.empty());
}

TEST_F(DataProcessorTest, ErrorHandling) {
    EXPECT_FALSE(processor_->hasErrors());
    EXPECT_TRUE(processor_->getLastError().empty());
    
    processor_->clearErrors();
    EXPECT_FALSE(processor_->hasErrors());
}

TEST_F(DataProcessorTest, LoggingOperations) {
    EXPECT_NO_THROW(processor_->setLogLevel(0));
    EXPECT_NO_THROW(processor_->logOperation("GTEST", "GTest operation"));
}

// Performance tests
TEST_F(DataProcessorTest, PerformanceJsonProcessing) {
    const int iterations = 100;
    auto start = std::chrono::high_resolution_clock::now();
    
    for (int i = 0; i < iterations; ++i) {
        std::string json = fmt::format(R"({{"iteration": {}, "data": "test_data_{}"}})", i, i);
        processor_->processJsonData(json);
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    EXPECT_LT(duration.count(), 1000); // Should complete in less than 1 second
}

TEST_F(DataProcessorTest, PerformanceHashGeneration) {
    const int iterations = 100;
    auto start = std::chrono::high_resolution_clock::now();
    
    for (int i = 0; i < iterations; ++i) {
        std::string data = "Test data for hashing " + std::to_string(i);
        processor_->generateHash(data);
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    EXPECT_LT(duration.count(), 1000); // Should complete in less than 1 second
}

// Integration tests
TEST_F(DataProcessorTest, IntegrationTest) {
    // Test multiple operations together
    std::string jsonData = R"({"name": "integration_test", "value": 42})";
    EXPECT_TRUE(processor_->processJsonData(jsonData));
    
    std::string hash = processor_->generateHash(jsonData);
    EXPECT_FALSE(hash.empty());
    
    EXPECT_TRUE(processor_->processTextWithRegex(jsonData, R"("name":\s*"[^"]*")"));
    
    std::string report = processor_->generateJsonReport();
    EXPECT_FALSE(report.empty());
}

int main(int argc, char** argv) {
    // Initialize spdlog for tests
    auto logger = spdlog::stdout_color_mt("test_runner");
    logger->set_level(spdlog::level::info);
    
    logger->info("=== Running Complex Dependencies Tests ===");
    logger->info("Testing 25+ library dependencies");
    logger->info("Using Catch2 and Google Test frameworks");
    logger->info("==========================================");
    
    // Run Catch2 tests
    int catchResult = Catch::Session().run(argc, argv);
    
    // Run Google Test tests
    ::testing::InitGoogleTest(&argc, argv);
    int gtestResult = RUN_ALL_TESTS();
    
    logger->info("=== Test Results ===");
    logger->info("Catch2 tests completed");
    logger->info("Google Test tests completed");
    logger->info("====================");
    
    // Return combined result
    return (catchResult == 0 && gtestResult == 0) ? 0 : 1;
} 