// ================================
// LinkedList.cpp (Fixed sortByDate)
// ================================
#include "LinkedList.h"
#include "Utilities.h"
#include <iostream>
using namespace std;

LinkedList::LinkedList() : head(nullptr), tail(nullptr), listSize(0) {}

LinkedList::~LinkedList() {
    clear();
}

void LinkedList::insert(const Transaction& transaction) {
    Node* newNode = new Node{ transaction, nullptr };
    if (!head) {
        head = tail = newNode;
    }
    else {
        tail->next = newNode;
        tail = newNode;
    }
    ++listSize;
}

void LinkedList::displayAll() const {
    Node* current = head;
    int index = 0;
    while (current) {
        cout << "Index: " << index++ << endl;
        cout << "Customer ID: " << current->data.getCustomerID() << endl;
        cout << "Product: " << current->data.getProduct() << endl;
        cout << "Price: " << current->data.getPrice() << endl;
        cout << "Date: " << current->data.getDate() << endl;
        cout << "Category: " << current->data.getCategory() << endl;
        cout << "Payment Method: " << current->data.getPaymentMethod() << endl;
        cout << "----------------------------------------" << endl;
        current = current->next;
    }
}

void LinkedList::searchByCategoryAndPayment(const string& category, const string& paymentMethod) {
    string catLower = Utilities::toLower(category);
    string payLower = Utilities::toLower(paymentMethod);
    Node* current = head;
    int index = 0;
    bool found = false;

    while (current) {
        if (Utilities::toLower(current->data.getCategory()) == catLower &&
            Utilities::toLower(current->data.getPaymentMethod()) == payLower) {
            cout << "Index: " << index << endl;
            cout << "Customer ID: " << current->data.getCustomerID() << endl;
            cout << "Product: " << current->data.getProduct() << endl;
            cout << "Price: " << current->data.getPrice() << endl;
            cout << "Date: " << current->data.getDate() << endl;
            cout << "Category: " << current->data.getCategory() << endl;
            cout << "Payment Method: " << current->data.getPaymentMethod() << endl;
            cout << "----------------------------------------" << endl;
            found = true;
        }
        current = current->next;
        ++index;
    }
    if (!found) cout << "No matching transactions found." << endl;
}

//
void LinkedList::sortByDate() {
    cout << "Sorting transactions by Date..." << endl;
    if (!head || !head->next) return;
    for (int i = 0; i < listSize - 1; ++i) {
        Node* current = head;
        while (current && current->next) {
            if (!Utilities::compareDates(current->data.getDate(), current->next->data.getDate())) {
                swap(current->data, current->next->data);
            }
            current = current->next;
        }
    }
    cout << "Sorting complete." << endl;
}

void LinkedList::clear() {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
    listSize = 0;
}

bool LinkedList::insertAtIndex(int index, const Transaction& transaction) {
    if (index < 0 || index > listSize) return false;

    Node* newNode = new Node{ transaction, nullptr };
    if (index == 0) {
        newNode->next = head;
        head = newNode;
        if (!tail) tail = newNode;
    }
    else {
        Node* current = head;
        for (int i = 0; i < index - 1; ++i)
            current = current->next;
        newNode->next = current->next;
        current->next = newNode;
        if (!newNode->next) tail = newNode;
    }
    ++listSize;
    return true;
}

bool LinkedList::deleteAtIndex(int index) {
    if (index < 0 || index >= listSize || !head) return false;

    Node* toDelete = nullptr;
    if (index == 0) {
        toDelete = head;
        head = head->next;
        if (!head) tail = nullptr;
    }
    else {
        Node* current = head;
        for (int i = 0; i < index - 1; ++i)
            current = current->next;
        toDelete = current->next;
        current->next = current->next->next;
        if (!current->next) tail = current;
    }
    delete toDelete;
    --listSize;
    return true;
}
