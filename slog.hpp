#pragma once

#include <iostream>
#include <mutex>
#include <string>

#define RESET   "\033[0m"
#define GRAY    "\033[90m"
#define BLUE    "\033[34m"
#define RED     "\033[31m"
#define YELLOW  "\033[33m"
#define GREEN   "\033[32m"

namespace slog {

    enum class Level {
        TRACE,
        DEBUG,
        INFO,
        WARNING,
        ERROR
    };

    inline auto logLevel = Level::DEBUG;

    class Logger {

    public:
        template<typename... Args>
        static void trace(const std::string& message, const char* file, const int line, Args... args) {
            log(message, Level::TRACE, file, line, GRAY, "TRACE", args...);
        }

        template<typename... Args>
        static void debug(const std::string& message, const char* file, const int line, Args... args) {
            log(message, Level::DEBUG, file, line, BLUE, "DEBUG", args...);
        }

        template<typename... Args>
        static void info(const std::string& message, const char* file, const int line, Args... args) {
            log(message, Level::INFO, file, line, GREEN, "INFO", args...);
        }

        template<typename... Args>
        static void warning(const std::string& message, const char* file, const int line, Args... args) {
            log(message, Level::WARNING, file, line, YELLOW, "WARNING", args...);
        }

        template<typename... Args>
        static void error(const std::string& message, const char* file, const int line, Args... args) {
            log(message, Level::ERROR, file, line, RED, "ERROR", args...);
        }

        static void setLevel(const Level newLevel) {
            logLevel = newLevel;
        }

    private:
        template<typename... Args>
        static void log(const std::string& message, const Level level, const char* file, const int line, const char* color, const char* levelStr, Args... args) {
            if (logLevel > level) return;
            std::lock_guard<std::mutex> lock(mutex_);
            std::cout << color << "[" << levelStr << "] "
                      << file << ":" << line << " - " << message << RESET;

            ((std::cout << " " << args), ...);

            std::cout << std::endl;
        }

        inline static std::mutex mutex_;
    };

} // namespace slog

// Simplified macros
#define trc(message, ...) slog::Logger::trace(message, __FILE__, __LINE__, __VA_ARGS__)
#define dbg(message, ...) slog::Logger::debug(message, __FILE__, __LINE__, __VA_ARGS__)
#define nfo(message, ...) slog::Logger::info(message, __FILE__, __LINE__, __VA_ARGS__)
#define wrn(message, ...) slog::Logger::warning(message, __FILE__, __LINE__, __VA_ARGS__)
#define err(message, ...) slog::Logger::error(message, __FILE__, __LINE__, __VA_ARGS__)
