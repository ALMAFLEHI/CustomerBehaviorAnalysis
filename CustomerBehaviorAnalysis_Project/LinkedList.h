// ================================
// LinkedList.h (Updated with getSize)
// ================================
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Transaction.h"

/**
 * @brief Singly linked list structure for storing transactions.
 */
class LinkedList {
private:
    struct Node {
        Transaction data;
        Node* next;
    };

    Node* head;
    Node* tail;
    int listSize;  // Replaces size variable name to avoid ambiguity

public:
    LinkedList();
    ~LinkedList();

    void insert(const Transaction& transaction);
    bool insertAtIndex(int index, const Transaction& transaction);
    bool deleteAtIndex(int index);

    void displayAll() const;
    void searchByCategoryAndPayment(const std::string& category, const std::string& paymentMethod);
    void sortByDate();
    void clear();

    int getSize() const { return listSize; }  // Public accessor for performance reporting
};

#endif // LINKEDLIST_H
