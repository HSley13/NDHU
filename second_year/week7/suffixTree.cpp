#include <cstddef>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

class SuffixTreeNode {
  public:
    std::unordered_map<char, std::shared_ptr<SuffixTreeNode>> children;
    std::vector<int> suffix_indices;

    void insertSuffix(const std::string &text, std::size_t index) {
        SuffixTreeNode *current{this};
        for (std::size_t i{index}; i < text.size(); i++) {
            char ch{text[i]};
            if (current->children.find(ch) == current->children.end()) {
                current->children[ch] = std::make_shared<SuffixTreeNode>();
            }
            current = current->children.at(ch).get();
            current->suffix_indices.push_back(index);
        }
    }
};

class SuffixTree {
  public:
    SuffixTree(const std::string &text) : text(text), root(std::make_shared<SuffixTreeNode>()) {
        for (std::size_t i{0}; i < text.size(); i++) {
            root->insertSuffix(text, i);
        }
    }

    std::pair<bool, int> existAndCount(const std::string &substring) const {
        std::shared_ptr<const SuffixTreeNode> current{root};
        for (const char &ch : substring) {
            if (current->children.find(ch) == current->children.end()) {
                return {false, 0};
            }
            current = current->children.at(ch);
        }
        return {true, current->suffix_indices.size()};
    }

  private:
    std::shared_ptr<SuffixTreeNode> root;
    std::string text;
};

int main(void) {
    std::string text{""};
    std::cout << "Enter text (empty line to end):" << std::endl;
    while (true) {
        std::string line;
        getline(std::cin, line);
        if (line.empty()) {
            break;
        }
        text += line;
    }

    SuffixTree tree(text);

    std::string query;
    std::cout << "Enter queries (empty line to end):" << std::endl;
    while (true) {
        getline(std::cin, query);
        if (query.empty()) {
            break;
        }

        std::pair<bool, int> result = tree.existAndCount(query);

        std::cout << "Existence of '" << query << "': " << (result.first ? "Yes" : "No") << std::endl;
        std::cout << "Count of '" << query << "': " << result.second << std::endl;
    }
}
