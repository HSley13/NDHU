#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <string>

class TrieNode {
  public:
    std::map<char, std::shared_ptr<TrieNode>> children;
    bool is_end_of_word{false};
};

class Trie {
  public:
    Trie() : root(std::make_shared<TrieNode>()) {}

    void insert(const std::string &value) {
        std::shared_ptr<TrieNode> current{root};
        for (const char &ch : value) {
            if (current->children.find(ch) == current->children.end()) {
                current->children[ch] = std::make_shared<TrieNode>();
            }
            current = current->children[ch];
        }
        current->is_end_of_word = true;
    }

    bool search(const std::string &key) {
        std::shared_ptr<TrieNode> current{root};
        for (const char &ch : key) {
            if (current->children.find(ch) == current->children.end()) {
                return false;
            }
            current = current->children[ch];
        }
        return current->is_end_of_word;
    }

    void preorder() {
        std::function<void(const std::shared_ptr<TrieNode> &node, const std::shared_ptr<TrieNode> &parent, int level)> preorderHelper = [&](const std::shared_ptr<TrieNode> &node, const std::shared_ptr<TrieNode> &parent, int level) {
            if (!node) {
                return;
            }

            if (parent && (parent->children.size() > 1 || parent->is_end_of_word)) {
                for (int i{0}; i < level; i++) {
                    std::cout << " ";
                }
            }

            if (node == root) {
                std::cout << "[]" << std::endl;
            } else {
                auto it{std::find_if(parent->children.begin(), parent->children.end(), [&](const std::pair<char, std::shared_ptr<TrieNode>> &child) { return child.second == node; })};
                if (it != parent->children.end()) {
                    std::cout << it->first;
                }
            }

            if (node->children.size() > 1 || node->is_end_of_word) {
                std::cout << std::endl;
            }

            for (const std::pair<char, std::shared_ptr<TrieNode>> &pair : node->children) {
                preorderHelper(pair.second, node, level + 2);
            }
        };

        preorderHelper(root, nullptr, 0);
    }

  private:
    std::shared_ptr<TrieNode> root;
};

int main(void) {
    Trie trie;
    std::string command, key, value;

    while (true) {
        std::cin >> command;
        if (command == "insert") {
            std::cin >> value;
            trie.insert(value);
        } else if (command == "search") {
            std::cin >> key;
            if (trie.search(key)) {
                std::cout << "exist" << std::endl;
            } else {
                std::cout << "not exist" << std::endl;
            }
        } else if (command == "print") {
            trie.preorder();
        } else if (command == "exit") {
            break;
        }
    }
}
