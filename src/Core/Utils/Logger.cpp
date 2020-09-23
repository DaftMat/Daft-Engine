//
// Created by mathis on 01/08/2020.
//
#include "Logger.hpp"

#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>

namespace daft::core {

void Logger::debug(std::stringstream ss) {
#if defined(DEBUG) || defined(TRACE)
    createLogEntry("debug", std::move(ss).str());
#endif
}

void Logger::info(std::stringstream ss) {
#if defined(DEBUG) || defined(TRACE)
    createLogEntry("info ", std::move(ss).str());
#endif
}

void Logger::warn(std::stringstream ss) {
#if defined(DEBUG) || defined(TRACE)
    createLogEntry("warn ", std::move(ss).str());
#endif
}

void Logger::trace(std::stringstream ss) {
#if defined(TRACE)
    createLogEntry("trace", std::move(ss).str());
#endif
}

void Logger::error(std::stringstream ss) { createLogEntry("error", std::move(ss).str()); }

void Logger::createLogEntry(std::string type, std::string msg) {
    /// create entry
    std::string time = getTimeStr();
    std::string movedType = std::move(type);
    std::string movedMsg = std::move(msg);
    std::string logEntry = "+ " + time + " >> " + movedType + " -- " + movedMsg + "\n";

    /// send it to stdout as well as in the logging file
    std::cout << logEntry;
    std::ofstream logFile;
    try {
        logFile.open("logs/logs.txt", std::ios_base::app);
        logFile << logEntry;
        logFile.close();
    } catch (std::ifstream::failure& f) {
        std::cerr << "Failed to open file : logs/logs.txt" << std::endl;
    }
}

std::string Logger::getTimeStr() {
    time_t rawtime;
    struct tm* timeinfo;
    char buffer[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer, sizeof(buffer), "[%d/%m/%Y-%H:%M:%S]", timeinfo);
    return std::string(buffer);
}

}  // namespace daft::core