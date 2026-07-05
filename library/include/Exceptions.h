//
// Created by jopala on 6.06.2026.
//

#ifndef PROGRAM_EXCEPTIONS_H
#define PROGRAM_EXCEPTIONS_H
#include <string>

/**
 * @namespace Exceptions
 * @brief Contains custom exception classes used throughout the application.
 *
 * This namespace isolates custom error handling logic, ensuring that
 * domain-specific exceptions do not clash with standard library names or
 * other libraries.
 */
namespace Exceptions {
    /**
     * @class FileWriteErrorException
     * @brief Exception thrown when a file write operation fails.
     *
     * This custom exception inherits from `std::runtime_error`. It is specifically
     * designed to be thrown during file I/O operations (such as saving repository
     * data to a JSON file) when the target file cannot be created, opened, or written to.
     */
    class FileWriteErrorException : public std::runtime_error {
    public:
        /**
         * @brief Constructs a new File Write Error Exception.
         * * @param msg A descriptive error message detailing what caused the failure
         * (e.g., the exact file path that was inaccessible). This message can be
         * retrieved later using the standard `.what()` method.
         */
        explicit FileWriteErrorException(const std::string& msg)
            : runtime_error(msg) {}
    };

}

#endif //PROGRAM_EXCEPTIONS_H
