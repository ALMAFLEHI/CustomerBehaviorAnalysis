// ================================
// Utilities.h
// ================================
#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>

/**
 * @brief Utility functions for string processing and date handling.
 */
class Utilities {
public:
    static std::string toLower(const std::string& str);
    static std::string trim(const std::string& str);
    static bool compareDates(const std::string& date1, const std::string& date2);
};

#endif // UTILITIES_H
