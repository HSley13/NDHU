#include <algorithm>
#include <cmath>
#include <float.h>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#define MAX_ENTRIES 16

struct BoundingBox {
    double minX, minY;
    double maxX, maxY;
};

struct DataItem {
    double latitude, longitude;
    std::string name;
};

struct SearchResult {
    DataItem item;
    double distance;
};

struct RTreeNode {
    bool isLeaf;
    int count;
    BoundingBox mbr;
    std::vector<std::shared_ptr<RTreeNode>> children;
    std::vector<DataItem> data;
};

class RTree {
  public:
    RTree() {
        root = createNode(true);
    }

    void insert(const DataItem &item) {
        std::shared_ptr<RTreeNode> node{root};
        // while (!node->isLeaf) {
        //     double minEnlargement{DBL_MAX};
        //     std::shared_ptr<RTreeNode> bestChild;
        //     for (const std::shared_ptr<RTreeNode> &child : node->children) {
        //         double enlargement{calculateMBRDistance(child->mbr, item.latitude, item.longitude)};
        //         if (enlargement < minEnlargement) {
        //             minEnlargement = enlargement;
        //             bestChild = child;
        //         }
        //     }
        //     node = bestChild;
        // }

        node->data.push_back(item);
        node->count++;
        if (node->count > MAX_ENTRIES) {
            std::cerr << "Node overflow! Splitting not yet implemented.\n";
        }
        updateMBR(node);
    }

    std::vector<SearchResult> search(double latitude, double longitude, int n) {
        std::vector<SearchResult> results;
        recursiveSearch(root, latitude, longitude, results);

        std::sort(results.begin(), results.end(), [](const SearchResult &a, const SearchResult &b) { return a.distance < b.distance; });

        if (results.size() > n) {
            results.resize(n);
        }

        return results;
    }

    void print() {
        printTree(root, 0);
    }

  private:
    std::shared_ptr<RTreeNode> root;

    BoundingBox calculateMBR(const BoundingBox &a, const BoundingBox &b) {
        BoundingBox mbr;
        mbr.minX = std::min(a.minX, b.minX);
        mbr.minY = std::min(a.minY, b.minY);
        mbr.maxX = std::max(a.maxX, b.maxX);
        mbr.maxY = std::max(a.maxY, b.maxY);
        return mbr;
    }

    double calculateDistance(double lat1, double lon1, double lat2, double lon2) {
        return std::sqrt(std::pow(lat2 - lat1, 2) + std::pow(lon2 - lon1, 2));
    }

    double calculateMBRDistance(const BoundingBox &mbr, double latitude, double longitude) {
        double dx{std::max({0.0, mbr.minX - longitude, longitude - mbr.maxX})};
        double dy{std::max({0.0, mbr.minY - latitude, latitude - mbr.maxY})};
        return std::sqrt(dx * dx + dy * dy);
    }

    void updateMBR(std::shared_ptr<RTreeNode> &node) {
        if (node->isLeaf) {
            for (int i{0}; i < node->count; i++) {
                const DataItem &item{node->data[i]};
                if (i == 0) {
                    node->mbr = {item.longitude, item.latitude, item.longitude, item.latitude};
                } else {
                    node->mbr.minX = std::min(node->mbr.minX, item.longitude);
                    node->mbr.minY = std::min(node->mbr.minY, item.latitude);
                    node->mbr.maxX = std::max(node->mbr.maxX, item.longitude);
                    node->mbr.maxY = std::max(node->mbr.maxY, item.latitude);
                }
            }
        }
        // else {
        //         for (int i{0}; i < node->count; i++) {
        //             const BoundingBox &childMBR{node->children[i]->mbr};
        //             if (i == 0) {
        //                 node->mbr = childMBR;
        //             } else {
        //                 node->mbr = calculateMBR(node->mbr, childMBR);
        //             }
        //         }
        //     }
    }

    std::shared_ptr<RTreeNode> createNode(bool isLeafOrNot) {
        std::shared_ptr<RTreeNode> node{std::make_shared<RTreeNode>()};
        node->isLeaf = isLeafOrNot;
        node->count = 0;
        return node;
    }

    void recursiveSearch(const std::shared_ptr<RTreeNode> &node, double latitude, double longitude, std::vector<SearchResult> &results) {
        if (node->isLeaf) {
            for (const DataItem &item : node->data) {
                double d{calculateDistance(latitude, longitude, item.latitude, item.longitude)};
                results.push_back({item, d});
            }
        }
        // else {
        //         for (const std::shared_ptr<RTreeNode> &child : node->children) {
        //             double d{calculateMBRDistance(child->mbr, latitude, longitude)};
        //             if(d >= 0.0){
        //             recursiveSearch(child, latitude, longitude, results);
        //             }
        //         }
        //     }
    }

    void printTree(const std::shared_ptr<RTreeNode> &node, int depth) {
        for (int i{0}; i < depth; i++)
            std::cout << "  ";
        std::cout << "Node (count=" << node->count << ", isLeaf=" << node->isLeaf << "):" << std::endl;

        for (int i{0}; i < node->count; i++) {
            if (node->isLeaf) {
                for (int j{0}; j < depth + 1; j++)
                    std::cout << "  ";
                std::cout << "Data: " << node->data[i].name << " (" << node->data[i].latitude << ", " << node->data[i].longitude << ")" << std::endl;
            } else {
                printTree(node->children[i], depth + 1);
            }
        }
    }
};

int main(void) {
    RTree tree;

    DataItem item;
    double latitude, longitude;
    std::vector<SearchResult> results;

    std::string command;

    while (true) {
        std::cin >> command;

        if (!command.compare("insert")) {
            std::cin >> item.latitude >> item.longitude >> item.name;
            tree.insert(item);
        } else if (!command.compare("print")) {
            tree.print();
        } else if (!command.compare("exit")) {
            break;
        } else if (!command.compare("search")) {
            std::cin >> latitude >> longitude;
            results = tree.search(latitude, longitude, 2);
            for (const SearchResult &result : results) {
                std::cout << result.item.name << " (" << result.item.latitude << ", " << result.item.longitude << ") - Distance: " << result.distance << std::endl;
            }
        } else {
            std::cout << "Unknown command." << std::endl;
        }
    }
}
