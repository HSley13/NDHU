#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

class TextProcessor {
  public:
    TextProcessor(const std::string &inputFileName, const std::string &histFileName, const std::string &freqFileName) {
        inputFile.open(inputFileName);
        if (!inputFile) {
            throw std::runtime_error("Error opening input file!");
        }

        wordCountFile.open(histFileName);
        charCountFile.open(freqFileName);
        if (!wordCountFile || !charCountFile) {
            throw std::runtime_error("Error opening output files!");
        }

        processFile();
    }

  private:
    std::ifstream inputFile;
    std::ofstream wordCountFile;
    std::ofstream charCountFile;

    std::map<std::string, int> wordCountMap;
    std::map<char, int> charCountMap;

    void processFile() {
        std::string line;
        while (std::getline(inputFile, line)) {
            line = processString(line);
            processWords(line);
        }
        writeWordCounts();
        writeCharCounts();
    }

    std::string processString(std::string &str) {
        str.erase(std::remove_if(str.begin(), str.end(), [](unsigned char c) {
                      return !std::isalpha(c) && !std::isspace(c);
                  }),
                  str.end());

        std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c) {
            return std::tolower(c);
        });
        return str;
    }

    void processWords(const std::string &line) {
        std::istringstream stream{line};
        std::string word;
        while (stream >> word) {
            wordCountMap[word]++;
            for (const char &ch : word) {
                charCountMap[ch]++;
            }
        }
    }

    void writeWordCounts() {
        for (const std::pair<std::string, int> &word : wordCountMap) {
            wordCountFile << word.first << "\t" << std::string(word.second, '*') << word.second << "\n";
        }
    }

    void writeCharCounts() {
        std::vector<std::pair<char, int>> charVector(charCountMap.begin(), charCountMap.end());
        std::sort(charVector.begin(), charVector.end(), [](const std::pair<char, int> &a, const std::pair<char, int> &b) {
            return a.second < b.second;
        });

        for (const std::pair<char, int> &charPair : charVector) {
            charCountFile << charPair.first << "\t" << charPair.second << "\n";
        }
    }
};

int main(void) {
    try {
        std::string inputFileName, histFileName, freqFileName;
        std::cin >> inputFileName >> histFileName >> freqFileName;

        TextProcessor processor(inputFileName, histFileName, freqFileName);
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}
