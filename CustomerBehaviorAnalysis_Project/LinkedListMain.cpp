// ================================
// LinkedListMain.cpp (Final with Unified Performance Report)
// ================================

#include "C:\\Users\\devls\\source\\repos\\CustomerBehaviorAnalysis_Project\\CustomerBehaviorAnalysis_Project\\Transaction.h"
#include "C:\\Users\\devls\\source\\repos\\CustomerBehaviorAnalysis_Project\\CustomerBehaviorAnalysis_Project\\LinkedList.h"
#include "C:\\Users\\devls\\source\\repos\\CustomerBehaviorAnalysis_Project\\CustomerBehaviorAnalysis_Project\\CSVLoader.h"
#include "Timer.h"
#include <iostream>
#include <fstream>
#include "Utilities.h"
using namespace std;

int main() {
    vector<Transaction> transactions = CSVLoader::loadTransactions("C:/Users/devls/source/repos/CustomerBehaviorAnalysis_Project/CustomerBehaviorAnalysis_Project/x64/Debug/Dataset/transactions_cleaned.csv");
    LinkedList transactionList;
    for (const auto& t : transactions) {
        transactionList.insert(t);
    }

    int choice;
    do {
        cout << "\n=============== Transaction System (Linked List) ===============\n";
        cout << "1. Display All Transactions\n";
        cout << "2. Sort Transactions by Date\n";
        cout << "3. Search by Category + Payment Method\n";
        cout << "4. Time Sorting (Performance Test)\n";
        cout << "5. Insert Transaction at Index\n";
        cout << "6. Delete Transaction at Index\n";
        cout << "0. Exit\n";
        cout << "===============================================================\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            transactionList.displayAll();
            cout << "\n[✔] All transactions displayed.\n";
            break;

        case 2:
            transactionList.sortByDate();
            transactionList.displayAll();
            cout << "\n[✔] Transactions sorted and displayed.\n";
            break;

        case 3: {
            string cat, pay;
            cout << "Enter category (Books, Electronics, Toys, Automotive, Beauty, Sports, Fashion, Furniture, Home Appliances): ";
            getline(cin, cat);
            cout << "Enter payment method (Credit Card, Debit Card, PayPal, Bank Transfer, Cash on Delivery): ";
            getline(cin, pay);
            cout << "\nSearching transactions with Category: '" << cat << "' and Payment Method: '" << pay << "'...\n";
            transactionList.searchByCategoryAndPayment(cat, pay);
            cout << "\n[✔] Search completed and displayed.\n";

            char confirm;
            cout << "\nDo you want to see the percentage of '" << cat << "' purchases made using '" << pay << "'? (y/n): ";
            cin >> confirm;
            if (tolower(confirm) == 'y') {
                int total = 0, match = 0;
                for (const auto& t : transactions) {
                    if (Utilities::toLower(t.getCategory()) == Utilities::toLower(cat)) {
                        total++;
                        if (Utilities::toLower(t.getPaymentMethod()) == Utilities::toLower(pay)) {
                            match++;
                        }
                    }
                }
                if (total > 0) {
                    double percent = (match * 100.0) / total;
                    cout << "\n→ Total '" << cat << "' transactions: " << total << endl;
                    cout << "→ '" << pay << "' payments in '" << cat << "': " << match << endl;
                    cout << "→ Percentage: " << percent << "%\n";
                }
                else {
                    cout << "\n[!] No transactions found for category: " << cat << endl;
                }
            }
            cin.ignore();
            break;
        }

        case 4: {
            Timer timer;
            timer.start();
            transactionList.sortByDate();
            timer.stop();

            double timeTaken = timer.getDurationMilliseconds();
            int entries = transactions.size();

            cout << "\n[!] Linked List Sorting Time: " << timeTaken << " ms\n";
            cout << "[!] Sorting performance measured and recorded.\n";

            ofstream report("PerformanceReport.txt", ios::app);
            if (report.is_open()) {
                report << "\nStructure: LINKED LIST\n";
                report << "------------------------\n";
                report << "Sorting Algorithm   : Bubble Sort\n";
                report << "Time Taken (ms)     : " << timeTaken << "\n";
                report << "Time Complexity     : O(n²)\n";
                report << "Memory Usage        : Dynamically allocated nodes\n";
                report << "Number of Records   : " << entries << "\n";
                report << "Stability           : Stable sort\n";
                report << "Suitability         : Simple to implement, but slower due to pointer overhead\n\n";
                report.close();
            }
            else {
                cerr << "[!] Failed to append to PerformanceReport.txt\n";
            }
            break;
        }

        case 5: {
            int index;
            Transaction t;
            string input;
            double price;

            cout << "\nEnter index to insert at: ";
            cin >> index;
            cin.ignore();

            cout << "Customer ID: ";
            getline(cin, input);
            t.setCustomerID(input);

            cout << "Product: ";
            getline(cin, input);
            t.setProduct(input);

            cout << "Category: ";
            getline(cin, input);
            t.setCategory(input);

            cout << "Price: ";
            cin >> price;
            cin.ignore();
            t.setPrice(price);

            cout << "Date (DD/MM/YYYY): ";
            getline(cin, input);
            t.setDate(input);

            cout << "Payment Method: ";
            getline(cin, input);
            t.setPaymentMethod(input);

            if (transactionList.insertAtIndex(index, t))
                cout << "[✔] Inserted successfully.\n";
            else
                cout << "[!] Insert failed.\n";
            break;
        }

        case 6: {
            int index;
            cout << "Enter index to delete: ";
            cin >> index;
            if (transactionList.deleteAtIndex(index))
                cout << "[✔] Deleted successfully.\n";
            else
                cout << "[!] Delete failed.\n";
            break;
        }

        case 0:
            cout << "\nExiting program.\n";
            break;

        default:
            cout << "\nInvalid option. Try again.\n";
        }
    } while (choice != 0);

    return 0;
}
