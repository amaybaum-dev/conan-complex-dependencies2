#pragma once

#include <string>
#include <vector>
#include <memory>
#include <functional>

// Forward declarations to avoid including all headers
namespace spdlog {
    class logger;
}

namespace nlohmann {
    class json;
}

namespace boost {
    namespace filesystem {
        class path;
    }
    namespace system {
        class error_code;
    }
}

namespace re2 {
    class RE2;
}

namespace sqlite3 {
    struct sqlite3;
}

namespace curl {
    struct CURL;
}

namespace png {
    struct png_struct_def;
    struct png_info_def;
}

namespace jpeg {
    struct jpeg_compress_struct;
    struct jpeg_decompress_struct;
}

namespace ft {
    struct FT_LibraryRec_;
    struct FT_FaceRec_;
}

namespace hb {
    struct hb_font_t;
    struct hb_buffer_t;
}

namespace OpenSSL {
    struct SSL_CTX;
    struct SSL;
    struct EVP_CIPHER_CTX;
}

/**
 * @brief Complex data processor that demonstrates deep transitive dependencies
 * 
 * This class uses multiple libraries with complex dependency relationships:
 * - fmt -> spdlog -> logging
 * - nlohmann_json -> JSON processing
 * - boost -> filesystem, system, thread operations
 * - openssl -> cryptography
 * - zlib/bzip2 -> compression
 * - re2 -> regular expressions
 * - sqlite3 -> database operations
 * - curl -> HTTP operations
 * - libpng/libjpeg-turbo -> image processing
 * - freetype/harfbuzz -> font rendering
 */
class DataProcessor {
public:
    DataProcessor();
    ~DataProcessor();

    // JSON Processing
    bool processJsonData(const std::string& jsonData);
    std::string generateJsonReport() const;
    
    // File System Operations
    bool processFilesInDirectory(const std::string& directoryPath);
    bool compressFile(const std::string& inputPath, const std::string& outputPath);
    bool decompressFile(const std::string& inputPath, const std::string& outputPath);
    
    // Database Operations
    bool initializeDatabase(const std::string& dbPath);
    bool storeData(const std::string& table, const std::string& data);
    std::vector<std::string> queryData(const std::string& query);
    
    // Network Operations
    bool downloadFile(const std::string& url, const std::string& localPath);
    std::string makeHttpRequest(const std::string& url);
    
    // Image Processing
    bool processImage(const std::string& imagePath);
    bool convertImageFormat(const std::string& inputPath, const std::string& outputPath);
    
    // Text Processing
    bool processTextWithRegex(const std::string& text, const std::string& pattern);
    std::vector<std::string> extractMatches(const std::string& text, const std::string& pattern);
    
    // Font Rendering
    bool renderText(const std::string& text, const std::string& fontPath, const std::string& outputPath);
    bool processTextLayout(const std::string& text, const std::string& fontPath);
    
    // Cryptography
    std::string encryptData(const std::string& data, const std::string& key);
    std::string decryptData(const std::string& encryptedData, const std::string& key);
    std::string generateHash(const std::string& data);
    
    // Threading and Async Operations
    void processDataAsync(const std::string& data, std::function<void(const std::string&)> callback);
    void waitForCompletion();
    
    // Logging and Monitoring
    void setLogLevel(int level);
    void logOperation(const std::string& operation, const std::string& details);
    
    // Error Handling
    std::string getLastError() const;
    bool hasErrors() const;
    void clearErrors();

private:
    // PIMPL idiom to hide implementation details
    class Impl;
    std::unique_ptr<Impl> pImpl;
    
    // Private helper methods
    bool validateInput(const std::string& input);
    void logError(const std::string& error);
    bool initializeComponents();
    void cleanupComponents();
}; 