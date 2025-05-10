#include "Utilities.h"
#include "Array.h"
#include <iostream>
using namespace std;

Array::Array() : size(0), capacity(10) {
    transactions = new Transaction[capacity];
}

Array::~Array() {
    delete[] transactions;
}

int Array::getSize() const {
    return size;
}

void Array::insert(const Transaction& transaction) {
    if (size >= capacity) {
        resize();
    }
    transactions[size++] = transaction;
}

void Array::resize() {
    int newCapacity = capacity * 2;
    Transaction* newTransactions = new Transaction[newCapacity];

    for (int i = 0; i < size; ++i) {
        newTransactions[i] = transactions[i];
    }

    delete[] transactions;
    transactions = newTransactions;
    capacity = newCapacity;
}

void Array::displayAll() const {
    cout << "Total transactions loaded: " << size << endl;
    for (int i = 0; i < size; ++i) {
        cout << "Index: " << i << endl;
        cout << "Customer ID: " << transactions[i].getCustomerID() << endl;
        cout << "Product: " << transactions[i].getProduct() << endl;
        cout << "Price: " << transactions[i].getPrice() << endl;
        cout << "Date: " << transactions[i].getDate() << endl;
        cout << "Category: " << transactions[i].getCategory() << endl;
        cout << "Payment Method: " << transactions[i].getPaymentMethod() << endl;
        cout << "----------------------------------------" << endl;
    }
}

void Array::searchByCategoryAndPayment(const string& category, const string& paymentMethod) {
    cout << "Searching transactions with Category: '" << category
        << "' and Payment Method: '" << paymentMethod << "'..." << endl;

    string targetCategory = Utilities::toLower(category);
    string targetPayment = Utilities::toLower(paymentMethod);

    bool found = false;

    for (int i = 0; i < size; ++i) {
        if (Utilities::toLower(transactions[i].getCategory()) == targetCategory &&
            Utilities::toLower(transactions[i].getPaymentMethod()) == targetPayment) {
            cout << "Index: " << i << endl;
            cout << "Customer ID: " << transactions[i].getCustomerID() << endl;
            cout << "Product: " << transactions[i].getProduct() << endl;
            cout << "Price: " << transactions[i].getPrice() << endl;
            cout << "Date: " << transactions[i].getDate() << endl;
            cout << "Category: " << transactions[i].getCategory() << endl;
            cout << "Payment Method: " << transactions[i].getPaymentMethod() << endl;
            cout << "----------------------------------------" << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "No matching transactions found." << endl;
    }
}

void Array::sortByDate() {
    cout << "Sorting transactions by Date..." << endl;

    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (!Utilities::compareDates(transactions[j].getDate(), transactions[j + 1].getDate())) {
                Transaction temp = transactions[j];
                transactions[j] = transactions[j + 1];
                transactions[j + 1] = temp;
            }
        }
    }

    cout << "Sorting complete." << endl;
}

void Array::clear() {
    size = 0;
}

bool Array::deleteAtIndex(int index) {
    if (index < 0 || index >= size) return false;
    for (int i = index; i < size - 1; ++i) {
        transactions[i] = transactions[i + 1];
    }
    size--;
    return true;
}

bool Array::insertAtIndex(int index, const Transaction& transaction) {
    if (index < 0 || index > size) return false;
    if (size >= capacity) resize();

    for (int i = size; i > index; --i) {
        transactions[i] = transactions[i - 1];
    }
    transactions[index] = transaction;
    size++;
    return true;
}
