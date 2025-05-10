#include "Utilities.h"
#include <algorithm>
#include <cctype>
#include <sstream>

std::string Utilities::toLower(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(),
        [](unsigned char c) { return std::tolower(c); });
    return result;
}

std::string Utilities::trim(const std::string& str) {
    size_t first = str.find_first_not_of(' ');
    if (first == std::string::npos)
        return "";

    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

bool Utilities::compareDates(const std::string& date1, const std::string& date2) {
    auto convertToInt = [](const std::string& date) -> int {
        if (date.length() != 10 || date[2] != '/' || date[5] != '/') {
            // Invalid format, return large number to push invalid dates last
            return 99999999;
        }
        try {
            int day = stoi(date.substr(0, 2));
            int month = stoi(date.substr(3, 2));
            int year = stoi(date.substr(6, 4));
            return year * 10000 + month * 100 + day; // YYYYMMDD
        }
        catch (...) {
            return 99999999; // On parsing error, push to the end
        }
        };

    return convertToInt(date1) < convertToInt(date2);
}
