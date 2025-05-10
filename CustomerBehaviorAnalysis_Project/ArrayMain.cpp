#include "C:\\Users\\devls\\source\\repos\\CustomerBehaviorAnalysis_Project\\CustomerBehaviorAnalysis_Project\\Transaction.h"
#include "C:\\Users\\devls\\source\\repos\\CustomerBehaviorAnalysis_Project\\CustomerBehaviorAnalysis_Project\\Array.h"
#include "C:\\Users\\devls\\source\\repos\\CustomerBehaviorAnalysis_Project\\CustomerBehaviorAnalysis_Project\\CSVLoader.h"
#include "Timer.h"
#include <iostream>
#include <fstream>
#include "Utilities.h"
using namespace std;

/**
 * @brief Main function with menu-driven UI for Array-based transaction system.
 */
int main() {
    vector<Transaction> transactions = CSVLoader::loadTransactions("C:/Users/devls/source/repos/CustomerBehaviorAnalysis_Project/CustomerBehaviorAnalysis_Project/x64/Debug/Dataset/transactions_cleaned.csv");
    Array transactionArray;
    for (const auto& t : transactions) {
        transactionArray.insert(t);
    }

    int choice;
    do {
        cout << "\n================ Transaction System (Array) ================\n";
        cout << "1. Display All Transactions\n";
        cout << "2. Sort Transactions by Date\n";
        cout << "3. Search by Category + Payment Method\n";
        cout << "4. Time Sorting (Performance Test)\n";
        cout << "5. Insert Transaction at Index\n";
        cout << "6. Delete Transaction at Index\n";
        cout << "0. Exit\n";
        cout << "===========================================================\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            transactionArray.displayAll();
            cout << "\n[!] All transactions displayed.\n";
            break;
        case 2:
            transactionArray.sortByDate();
            transactionArray.displayAll();
            cout << "\n[!] Transactions sorted and displayed.\n";
            break;
        case 3: {
            string cat, pay;
            cout << "Enter category (Books, Electronics, Toys, Automotive, Beauty, Sports, Fashion, Furniture, Home Appliances): ";
            getline(cin, cat);
            cout << "Enter payment method (Credit Card, Debit Card, PayPal, Bank Transfer, Cash on Delivery): ";
            getline(cin, pay);
            cout << "\nSearching transactions with Category: '" << cat << "' and Payment Method: '" << pay << "'...\n";
            transactionArray.searchByCategoryAndPayment(cat, pay);
            cout << "\n[!] Search completed and displayed.\n";

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
            transactionArray.sortByDate();
            timer.stop();

            double timeTaken = timer.getDurationMilliseconds();
            int count = transactionArray.getSize();

            cout << "\n[!] Array Sorting Time: " << timeTaken << " ms\n";
            cout << "[!] Sorting performance measured and recorded.\n";

            ofstream report("PerformanceReport.txt");
            if (report.is_open()) {
                report << "Performance Comparison Report\n";
                report << "===============================\n";
                report << "Structure: ARRAY\n";
                report << "------------------\n";
                report << "Sorting Algorithm   : Bubble Sort\n";
                report << "Time Taken (ms)     : " << timeTaken << "\n";
                report << "Time Complexity     : O(n²)\n";
                report << "Memory Usage        : Contiguous block (array of objects)\n";
                report << "Number of Records   : " << count << "\n";
                report << "Stability           : Stable sort\n";
                report << "Suitability         : Fast for small datasets, slow for large ones.\n";
                report.close();
            }
            else {
                cerr << "[!] Failed to write to PerformanceReport.txt\n";
            }
            break;
        }
        case 5: {
            int index;
            Transaction t;
            cout << "Enter index to insert at: ";
            cin >> index;
            cin.ignore();

            string cid, product, date, category, payment;
            double price;
            cout << "Customer ID: "; getline(cin, cid);
            cout << "Product: "; getline(cin, product);
            cout << "Price: "; cin >> price; cin.ignore();
            cout << "Date (DD/MM/YYYY): "; getline(cin, date);
            cout << "Category: "; getline(cin, category);
            cout << "Payment Method: "; getline(cin, payment);

            t = Transaction(cid, product, price, date, category, payment);
            if (transactionArray.insertAtIndex(index, t)) {
                cout << "[+] Inserted successfully at index " << index << endl;
            }
            else {
                cout << "[!] Failed to insert at that index." << endl;
            }
            break;
        }
        case 6: {
            int index;
            cout << "Enter index to delete: ";
            cin >> index;
            if (transactionArray.deleteAtIndex(index)) {
                cout << "[!] Transaction at index " << index << " deleted.\n";
            }
            else {
                cout << "[!] Invalid index.\n";
            }
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
