//
// Created by mathis on 01/08/2020.
//
#pragma once
#include <API.hpp>
#include <fstream>
#include <iostream>
#include <string>

namespace daft::core::utils {
class ENGINE_API Logger {
   public:
    class Log : public std::ostream {
       public:
        explicit Log(std::string filepath) : std::ostream(), m_filepath{std::move(filepath)} {}

        template <typename T>
        Log& operator<<(T value) {
            std::ofstream logFile;
            try {
                logFile.open(m_filepath, std::ios_base::app);
                logFile << value;
                logFile.close();
            } catch (std::ifstream::failure& f) {
                std::cerr << "Failed to open file : " << m_filepath << std::endl;
            }
            std::cout << value;
            return *this;
        }

       private:
        std::string m_filepath;
    };

    static Log& debug();

    static Log& info();

    static Log& warn();

    static Log& trace();

    static Log& error();

   private:
    static Log m_log;
};
}  // namespace daft::core::utils