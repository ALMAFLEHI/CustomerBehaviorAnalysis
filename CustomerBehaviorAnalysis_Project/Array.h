#ifndef ARRAY_H
#define ARRAY_H

#include "Transaction.h"
#include <string>

/**
 * @brief Array-based container for storing and managing transactions.
 */
class Array {
private:
    Transaction* transactions;
    int size;
    int capacity;
    void resize();  // Used to double array size when needed

public:
    Array();
    ~Array();

    void insert(const Transaction& transaction);
    bool insertAtIndex(int index, const Transaction& transaction);
    bool deleteAtIndex(int index);
    void displayAll() const;
    void searchByCategoryAndPayment(const std::string& category, const std::string& paymentMethod);
    void sortByDate();
    void clear();

    int getSize() const;  // ✅ Only declared once in public
};

#endif // ARRAY_H
