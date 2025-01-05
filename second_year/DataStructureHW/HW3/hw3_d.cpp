#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <queue>
#include <vector>

template <class T>
class LinkedBinaryTree {
  public:
    class Node {
      public:
        T data;
        std::shared_ptr<Node> left, right;
        Node(T d) : data(d), left(nullptr), right(nullptr) {}
    };

    LinkedBinaryTree() : root(nullptr) {}

    void insert(const T &value) {
        std::shared_ptr<Node> newNode{std::make_shared<Node>(value)};

        if (!root) {
            root = newNode;
        } else {
            std::shared_ptr<Node> current{incompleteNodes.front()};

            if (!current->left) {
                current->left = newNode;
            } else if (!current->right) {
                current->right = newNode;
                incompleteNodes.pop();
            }
        }

        incompleteNodes.push(newNode);
        headerList[value].push_back(newNode);
    }

    void printTree() {
        if (!root) {
            std::cout << "Tree is empty." << std::endl;
            return;
        }

        std::function<void(std::shared_ptr<Node>, const std::string &, bool)> printTree = [&](std::shared_ptr<Node> node, const std::string &prefix, bool isLeft) {
            if (node) {
                std::cout << prefix;
                std::cout << (isLeft ? "├── " : "└── ");
                std::cout << node->data << std::endl;

                printTree(node->left, prefix + (isLeft ? "│   " : "    "), true);
                printTree(node->right, prefix + (isLeft ? "│   " : "    "), false);
            }
        };

        printTree(root, "", true);
    }

    void printHeaderList() {
        for (const auto &pair : headerList) {
            std::cout << pair.first << ": ";
            const std::vector<std::shared_ptr<Node>> &nodes{pair.second};
            for (const auto &node : nodes) {
                std::cout << node->data << " ";
            }
            std::cout << std::endl;
        }
    }

  private:
    std::shared_ptr<Node> root;
    std::queue<std::shared_ptr<Node>> incompleteNodes;
    std::map<T, std::vector<std::shared_ptr<Node>>> headerList;
};

int main(void) {
    LinkedBinaryTree<char> tree;
    std::string input;

    std::cout << "Enter a string to construct the binary tree: ";
    std::getline(std::cin, input);

    for (const char &c : input) {
        tree.insert(c);
    }

    std::cout << "Tree structure:" << std::endl;
    tree.printTree();
    std::cout << std::endl;

    std::cout << "Unordered map of vectors for all letters:" << std::endl;
    tree.printHeaderList();
}

/*
----------------- 1. Database Indexing
In a database, a tree-like structure can be used for indexing rows or records based on a particular field (e.g., a unique key or identifier).
The headerList can map a field value to all rows that share that value.
This could be used in database systems like SQL or NoSQL for fast lookups:

Example:
Key: The value of a field (e.g., CustomerID in a customer database).
Value: A list of nodes, each representing a record associated with that CustomerID.
This approach helps in retrieving all rows matching a specific key quickly.

2. Autocompletion in Text Editors
In an autocomplete feature of a text editor, words or phrases can be stored in a tree-like structure.
The headerList could map each character or word prefix to all the words that share that prefix, allowing for fast lookup and suggestions based on partial input.

Example:
Key: A prefix of a word ("aut", "hel", etc.).
Value: A list of nodes where each node contains a word that starts with that prefix.
This can be used to quickly provide a list of suggested words while typing.

----------------- 3. File System Traversal (Directory Indexing)
In a file system, a tree-like structure can be used to represent directories and files.
The headerList can store a list of all files or directories with a certain name (in case of duplicates or similar names).
For instance, files with the same name but different file extensions can be grouped together in a map.

Example:
Key: The name of a file or directory.
Value: A list of nodes representing different files or directories with that name.
This can be helpful for organizing or searching directories with multiple files of similar names.

----------------- 4. Text Pattern Matching
In text analysis or pattern matching, you could use a tree-like structure to represent a document where each node corresponds to a substring.
The headerList could map substrings (e.g., patterns or phrases) to all occurrences within the document.
This could be useful in applications like search engines or plagiarism detection.

Example:
Key: A pattern or phrase (e.g., "lorem", "ipsum").
Value: A list of nodes where each node corresponds to an occurrence of the pattern or phrase in the document.
This allows quick retrieval of all occurrences of a particular substring.

----------------- 5. Decision Trees for Machine Learning
In machine learning, decision trees are often used for classification tasks.
The headerList could store intermediate nodes at each level of the decision tree, which maps a feature (key) to a list of decision nodes at that feature level.
This structure allows for efficient classification of data by following the decision path.

Example:
Key: The feature used for a decision (e.g., "age", "income").
Value: A list of nodes that correspond to different decision outcomes based on the value of that feature.
This structure allows for efficient decision-making as the tree is traversed.
 */
