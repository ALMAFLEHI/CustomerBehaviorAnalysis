// ================================
// ReviewAnalyzer.cpp
// ================================
#include "ReviewAnalyzer.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <iomanip>
using namespace std;

ReviewAnalyzer::ReviewAnalyzer() {
    loadStopwords();
}

void ReviewAnalyzer::loadStopwords() {
    stopwords = { "the", "and", "is", "in", "on", "with", "a", "an", "it", "of", "to" };
}

string ReviewAnalyzer::cleanWord(const string& word) const {
    string cleaned;
    for (char c : word) {
        if (isalnum(c)) cleaned += tolower(c);
    }
    return cleaned;
}

void ReviewAnalyzer::loadReviews(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Cannot open review file " << filename << endl;
        return;
    }

    string line;
    getline(file, line); // Skip header
    while (getline(file, line)) {
        stringstream ss(line);
        string productID, customerID, ratingStr, reviewText;

        getline(ss, productID, ',');
        getline(ss, customerID, ',');
        getline(ss, ratingStr, ',');
        getline(ss, reviewText);

        if (productID.empty() || customerID.empty() || ratingStr.empty() || reviewText.empty())
            continue;

        int rating = stoi(ratingStr);
        allReviews[rating].push_back(reviewText);
    }

    file.close();
}

void ReviewAnalyzer::analyzeTopWords(int rating, int topN) {
    wordFrequency.clear();
    totalWordsCounted = 0;

    if (allReviews.find(rating) == allReviews.end()) {
        cout << "[!] No reviews found with rating: " << rating << endl;
        return;
    }

    for (const string& review : allReviews[rating]) {
        stringstream words(review);
        string word;
        while (words >> word) {
            word = cleanWord(word);
            if (word.empty() || stopwords.count(word)) continue;
            wordFrequency[word]++;
            totalWordsCounted++;
        }
    }

    vector<pair<string, int>> sortedWords(wordFrequency.begin(), wordFrequency.end());
    sort(sortedWords.begin(), sortedWords.end(), [](auto& a, auto& b) {
        return a.second > b.second;
        });

    cout << "\nTop " << topN << " Frequent Words in " << rating << "-Star Reviews:\n";
    cout << "================================================\n";
    for (int i = 0; i < min(topN, (int)sortedWords.size()); ++i) {
        cout << setw(15) << left << sortedWords[i].first << " : " << sortedWords[i].second << endl;
    }
}

void ReviewAnalyzer::exportTopWordsToFile(const string& filename, int rating, int topN) const {
    ofstream out(filename);
    if (!out.is_open()) {
        cerr << "Error: Unable to open " << filename << " for writing.\n";
        return;
    }

    vector<pair<string, int>> sorted(wordFrequency.begin(), wordFrequency.end());
    sort(sorted.begin(), sorted.end(), [](auto& a, auto& b) {
        return a.second > b.second;
        });

    if ((int)sorted.size() > topN) {
        sorted.resize(topN);
    }

    out << "Review Frequency Report\n";
    out << "=======================\n";
    out << "Top " << topN << " Words in " << rating << "-Star Reviews:\n\n";

    for (const auto& pair : sorted) {
        out << setw(15) << left << pair.first << " : " << pair.second << "\t"
            << string(pair.second, '*') << "\n";
    }

    out << "\nTotal Words Counted: " << totalWordsCounted << "\n";
    out.close();
    cout << "[!] Report saved to " << filename << endl;
}
