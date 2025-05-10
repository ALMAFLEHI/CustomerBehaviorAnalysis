// ================================
// ReviewAnalyzer.h
// ================================
#ifndef REVIEW_ANALYZER_H
#define REVIEW_ANALYZER_H

#include <string>
#include <map>
#include <set>
#include <vector>

/**
 * @brief Class for analyzing customer review data by star rating.
 */
class ReviewAnalyzer {
private:
    std::map<int, std::vector<std::string>> allReviews;      // reviews grouped by star rating
    std::map<std::string, int> wordFrequency;                // word count
    std::set<std::string> stopwords;                         // basic stopwords
    int totalWordsCounted = 0;

    std::string cleanWord(const std::string& word) const;
    void loadStopwords();

public:
    ReviewAnalyzer();

    void loadReviews(const std::string& filename);
    void analyzeTopWords(int rating, int topN = 10);
    void exportTopWordsToFile(const std::string& filename, int rating, int topN = 10) const;
};

#endif // REVIEW_ANALYZER_H
