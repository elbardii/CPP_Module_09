#include "BitcoinExchange.hpp"
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cctype>

BitcoinExchange::BitcoinExchange() {
    // Try opening data.csv in current directory, or in ex00/
    std::ifstream file("data.csv");
    if (file.is_open()) {
        file.close();
        loadDatabase("data.csv");
    } else {
        loadDatabase("ex00/data.csv");
    }
}

BitcoinExchange::BitcoinExchange(const std::string& dbPath) {
    loadDatabase(dbPath);
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) : _database(other._database) {
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other) {
    if (this != &other) {
        this->_database = other._database;
    }
    return *this;
}

BitcoinExchange::~BitcoinExchange() {
}

std::string BitcoinExchange::trim(const std::string& str) const {
    size_t first = str.find_first_not_of(" \t\r\n");
    if (first == std::string::npos)
        return "";
    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, last - first + 1);
}

bool BitcoinExchange::isValidDate(const std::string& date) const {
    if (date.length() != 10)
        return false;
    if (date[4] != '-' || date[7] != '-')
        return false;
    for (size_t i = 0; i < 10; ++i) {
        if (i == 4 || i == 7)
            continue;
        if (!std::isdigit(date[i]))
            return false;
    }

    int year = std::atoi(date.substr(0, 4).c_str());
    int month = std::atoi(date.substr(5, 2).c_str());
    int day = std::atoi(date.substr(8, 2).c_str());

    if (year < 0 || month < 1 || month > 12 || day < 1)
        return false;

    int daysInMonth[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    bool isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    if (month == 2 && isLeap)
        daysInMonth[2] = 29;

    if (day > daysInMonth[month])
        return false;

    return true;
}

void BitcoinExchange::loadDatabase(const std::string& dbPath) {
    std::ifstream file(dbPath.c_str());
    if (!file.is_open()) {
        std::cerr << "Error: could not open database file." << std::endl;
        return;
    }

    std::string line;
    // Read header line (date,exchange_rate)
    if (std::getline(file, line)) {
        // If first line is not header, we process it
        if (line.find("date") == std::string::npos) {
            size_t comma = line.find(',');
            if (comma != std::string::npos) {
                std::string date = trim(line.substr(0, comma));
                double rate = std::strtod(trim(line.substr(comma + 1)).c_str(), NULL);
                _database[date] = rate;
            }
        }
    }

    while (std::getline(file, line)) {
        if (line.empty())
            continue;
        size_t comma = line.find(',');
        if (comma == std::string::npos)
            continue;
        std::string date = trim(line.substr(0, comma));
        double rate = std::strtod(trim(line.substr(comma + 1)).c_str(), NULL);
        _database[date] = rate;
    }
    file.close();
}

void BitcoinExchange::processInput(const std::string& inputPath) const {
    std::ifstream file(inputPath.c_str());
    if (!file.is_open()) {
        std::cout << "Error: could not open file." << std::endl;
        return;
    }

    if (_database.empty()) {
        std::cout << "Error: database is empty." << std::endl;
        return;
    }

    std::string line;
    // Check first line for header
    if (std::getline(file, line)) {
        std::string trimmedLine = trim(line);
        if (trimmedLine != "date | value") {
            // Process the first line if it's not the header
            file.seekg(0, std::ios::beg);
        }
    }

    while (std::getline(file, line)) {
        std::string trimmedLine = trim(line);
        if (trimmedLine.empty())
            continue;

        size_t pipePos = trimmedLine.find('|');
        if (pipePos == std::string::npos) {
            std::cout << "Error: bad input => " << trimmedLine << std::endl;
            continue;
        }

        std::string dateStr = trim(trimmedLine.substr(0, pipePos));
        std::string valStr = trim(trimmedLine.substr(pipePos + 1));

        if (!isValidDate(dateStr)) {
            std::cout << "Error: bad input => " << dateStr << std::endl;
            continue;
        }

        if (valStr.empty()) {
            std::cout << "Error: bad input => " << trimmedLine << std::endl;
            continue;
        }

        char* endPtr = NULL;
        double val = std::strtod(valStr.c_str(), &endPtr);
        if (endPtr == valStr.c_str() || *endPtr != '\0') {
            std::cout << "Error: bad input => " << trimmedLine << std::endl;
            continue;
        }

        if (val < 0) {
            std::cout << "Error: not a positive number." << std::endl;
            continue;
        }

        if (val > 1000) {
            std::cout << "Error: too large a number." << std::endl;
            continue;
        }

        // Find date in database: exact or closest lower date
        std::map<std::string, double>::const_iterator it = _database.upper_bound(dateStr);
        if (it == _database.begin()) {
            std::cout << "Error: bad input => " << dateStr << std::endl;
            continue;
        }

        --it;
        double rate = it->second;
        std::cout << dateStr << " => " << valStr << " = " << (val * rate) << std::endl;
    }
    file.close();
}
