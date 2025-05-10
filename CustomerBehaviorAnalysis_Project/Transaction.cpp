#include "Transaction.h"

Transaction::Transaction() {
    customerID = "";
    product = "";
    price = 0.0;
    date = "";
    category = "";
    paymentMethod = "";
}

Transaction::Transaction(string customerID, string product, double price,
    string date, string category, string paymentMethod) {
    this->customerID = customerID;
    this->product = product;
    this->price = price;
    this->date = date;
    this->category = category;
    this->paymentMethod = paymentMethod;
}

string Transaction::getCustomerID() const {
    return customerID;
}

string Transaction::getProduct() const {
    return product;
}

double Transaction::getPrice() const {
    return price;
}

string Transaction::getDate() const {
    return date;
}

string Transaction::getCategory() const {
    return category;
}

string Transaction::getPaymentMethod() const {
    return paymentMethod;
}
