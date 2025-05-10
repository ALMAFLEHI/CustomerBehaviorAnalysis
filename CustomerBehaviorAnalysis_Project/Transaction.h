#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
using namespace std;

class Transaction {
private:
    string customerID;
    string product;
    double price;
    string date;
    string category;
    string paymentMethod;

public:
    Transaction();
    Transaction(string customerID, string product, double price,
        string date, string category, string paymentMethod);

    string getCustomerID() const;
    string getProduct() const;
    double getPrice() const;
    string getDate() const;
    string getCategory() const;
    string getPaymentMethod() const;



    void setCustomerID(const std::string& id) { customerID = id; }
    void setProduct(const std::string& p) { product = p; }
    void setPrice(double pr) { price = pr; }
    void setDate(const std::string& d) { date = d; }
    void setCategory(const std::string& c) { category = c; }
    void setPaymentMethod(const std::string& pm) { paymentMethod = pm; }
};





#endif // TRANSACTION_H
