#include <cctype>
#include <iostream>
#include <memory>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>

class ExpressionTree {
  public:
    ExpressionTree(const std::string &expression) {
        root = buildTree(expression);
    }

    void printInFixOrder() const {
        printInFixOrder(root);
        std::cout << std::endl;
    }

    void printPreFixOrder() const {
        printPreFixOrder(root);
        std::cout << std::endl;
    }

    void printPostFixOrder() const {
        printPostFixOrder(root);
        std::cout << std::endl;
    }

    int eval() const {
        return evaluate(root);
    }

  private:
    struct Node {
        std::string value;
        std::shared_ptr<Node> left;
        std::shared_ptr<Node> right;

        Node(const std::string &val) : value(val), left(nullptr), right(nullptr) {}
    };

    std::shared_ptr<Node> root;

    bool isOperator(const std::string &op) const {
        return op == "+" || op == "-" || op == "*" || op == "/" || op == "%";
    }

    std::shared_ptr<Node> buildTree(const std::string &expression) {
        std::string postfix{infixToPostfix(expression)};

        std::stack<std::shared_ptr<Node>> st;
        std::istringstream iss(postfix);
        std::string token;

        while (iss >> token) {
            if (isOperator(token)) {
                std::shared_ptr<Node> right = st.top();
                st.pop();
                std::shared_ptr<Node> left = st.top();
                st.pop();

                std::shared_ptr<Node> node = std::make_shared<Node>(token);
                node->left = left;
                node->right = right;
                st.push(node);
            } else {
                st.push(std::make_shared<Node>(token));
            }
        }
        return st.top();
    }

    std::string infixToPostfix(const std::string &expression) const {
        std::ostringstream output;
        std::stack<std::string> operators;
        std::istringstream iss(expression);
        std::string token;

        while (iss >> token) {
            if (std::isdigit(token[0]) || (token[0] == '-' && token.size() > 1)) {
                output << token << ' ';
            } else if (token == "(") {
                operators.push(token);
            } else if (token == ")") {
                while (!operators.empty() && operators.top() != "(") {
                    output << operators.top() << ' ';
                    operators.pop();
                }
                operators.pop();
            } else if (isOperator(token)) {
                while (!operators.empty() && precedence(operators.top()) >= precedence(token)) {
                    output << operators.top() << ' ';
                    operators.pop();
                }
                operators.push(token);
            }
        }

        while (!operators.empty()) {
            output << operators.top() << ' ';
            operators.pop();
        }
        return output.str();
    }

    int precedence(const std::string &op) const {
        if (op == "+" || op == "-") return 1;
        if (op == "*" || op == "/" || op == "%") return 2;

        return 0;
    }

    void printInFixOrder(const std::shared_ptr<Node> &node) const {
        if (!node) return;

        if (isOperator(node->value)) std::cout << "(";

        printInFixOrder(node->left);
        std::cout << node->value << " ";
        printInFixOrder(node->right);

        if (isOperator(node->value)) std::cout << ")";
    }

    void printPreFixOrder(const std::shared_ptr<Node> &node) const {
        if (!node) return;

        std::cout << node->value << " ";
        printPreFixOrder(node->left);
        printPreFixOrder(node->right);
    }

    void printPostFixOrder(const std::shared_ptr<Node> &node) const {
        if (!node) return;

        printPostFixOrder(node->left);
        printPostFixOrder(node->right);
        std::cout << node->value << " ";
    }

    int evaluate(const std::shared_ptr<Node> &node) const {
        if (!node) return 0;

        if (!isOperator(node->value)) return std::stoi(node->value);

        int leftValue{evaluate(node->left)};
        int rightValue{evaluate(node->right)};

        if (node->value == "+") return leftValue + rightValue;
        if (node->value == "-") return leftValue - rightValue;
        if (node->value == "*") return leftValue * rightValue;
        if (node->value == "%") return leftValue % rightValue;
        if (node->value == "/") {
            if (rightValue == 0) throw std::runtime_error("Division by zero");
            return leftValue / rightValue;
        }

        throw std::runtime_error("Invalid operator");
    }
};

int main(void) {
    try {
        std::string infix{"( -12 + 3 ) * 4 % 5"};
        ExpressionTree exprTree(infix);

        std::cout << "Inorder: ";
        exprTree.printInFixOrder();

        std::cout << "Preorder: ";
        exprTree.printPreFixOrder();

        std::cout << "Postorder: ";
        exprTree.printPostFixOrder();

        std::cout << "Evaluated result: " << exprTree.eval() << std::endl;
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}
/*
        %
       / \
      *   5
     / \
    +   4
   / \
-12   3
*/
