#ifndef CSVLOADER_H
#define CSVLOADER_H

#include <vector>
#include <string>
#include "Transaction.h"

/**
 * @brief Class for loading transaction and review data from CSV files.
 */
class CSVLoader {
public:
    /**
     * @brief Load transactions from a CSV file.
     * @param filename Name of the CSV file to load.
     * @return Vector of Transaction objects.
     */
    static std::vector<Transaction> loadTransactions(const std::string& filename);

    /**
     * @brief Load review texts from a CSV file.
     * @param filename Name of the CSV file to load.
     * @return Vector of review strings.
     */
    static std::vector<std::string> loadReviews(const std::string& filename);
};

#endif // CSVLOADER_H
