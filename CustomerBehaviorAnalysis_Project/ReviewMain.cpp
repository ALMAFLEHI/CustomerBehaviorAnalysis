// ================================
// ReviewMain.cpp
// ================================
#include "ReviewAnalyzer.h"
#include <iostream>
#include <string>
using namespace std;

/**
 * @brief Menu-driven UI to analyze review frequency by rating.
 */
int main() {
    ReviewAnalyzer analyzer;
    analyzer.loadReviews("C:/Users/devls/source/repos/CustomerBehaviorAnalysis_Project/CustomerBehaviorAnalysis_Project/x64/Debug/Dataset/reviews_cleaned.csv");

    int choice;
    do {
        cout << "\n============= Review Analysis Menu =============\n";
        cout << "1. Display & Export Top Frequent Words by Star Rating\n";
        cout << "0. Exit\n";
        cout << "===============================================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            int rating, topN;
            cout << "Enter star rating (1 to 5): ";
            cin >> rating;
            if (rating < 1 || rating > 5) {
                cout << "[!] Invalid rating. Try again.\n";
                break;
            }

            cout << "Enter number of top frequent words to display: ";
            cin >> topN;

            analyzer.analyzeTopWords(rating, topN);
            analyzer.exportTopWordsToFile("ReviewFrequencyReport.txt", rating, topN);
            cout << "\n[!] Analysis & export complete.\n";
            break;
        }

        case 0:
            cout << "Exiting review analysis...\n";
            break;

        default:
            cout << "[!] Invalid choice. Try again.\n";
        }

    } while (choice != 0);

    return 0;
}
