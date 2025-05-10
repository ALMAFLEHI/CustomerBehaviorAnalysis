// ================================
// CSVLoader.cpp
// ================================
#include "CSVLoader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include "Transaction.h"

using namespace std;

std::vector<Transaction> CSVLoader::loadTransactions(const std::string& filename) {
    vector<Transaction> transactions;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return transactions;
    }

    string line;
    getline(file, line); // Skip header

    int lineNumber = 1;
    while (getline(file, line)) {
        lineNumber++;
        stringstream ss(line);
        string customerID, product, category, priceStr, date, paymentMethod;

        if (!getline(ss, customerID, ',') ||
            !getline(ss, product, ',') ||
            !getline(ss, category, ',') ||
            !getline(ss, priceStr, ',') ||
            !getline(ss, date, ',') ||
            !getline(ss, paymentMethod)) { // No separator after last field
            cerr << "Warning: Skipped invalid transaction at line " << lineNumber << endl;
            continue;
        }

        try {
            double price = stod(priceStr);
            transactions.emplace_back(customerID, product, price, date, category, paymentMethod);
        }
        catch (...) {
            cerr << "Warning: Invalid price format at line " << lineNumber << endl;
        }
    }

    file.close();
    return transactions;
}

std::vector<std::string> CSVLoader::loadReviews(const std::string& filename) {
    vector<string> reviews;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return reviews;
    }

    string line;
    getline(file, line); // Skip header

    int lineNumber = 1;
    while (getline(file, line)) {
        lineNumber++;
        stringstream ss(line);
        string productID, customerID, ratingStr, reviewText;

        if (!getline(ss, productID, ',') ||
            !getline(ss, customerID, ',') ||
            !getline(ss, ratingStr, ',') ||
            !getline(ss, reviewText)) {
            cerr << "Warning: Skipped invalid review at line " << lineNumber << endl;
            continue;
        }

        if (ratingStr == "1") {
            reviews.push_back(reviewText);
        }
    }

    file.close();
    return reviews;
}
