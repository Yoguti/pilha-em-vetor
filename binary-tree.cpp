#include <vector>

namespace structures {

template<typename T>
class BinaryTree {
private:
    struct Node {
        T data;
        Node* left;
        Node* right;
        
        Node(const T& d) : data(d), left(nullptr), right(nullptr) {}
    };
    
    Node* root;
    std::size_t size_;

    void destroy(Node* node) {
        if (node != nullptr) {
            destroy(node->left);
            destroy(node->right);
            delete node;
        }
    }

    void pre_order_traverse(Node* node, std::vector<T>& v) const {
        if (node != nullptr) {
            v.push_back(node->data);
            pre_order_traverse(node->left, v);
            pre_order_traverse(node->right, v);
        }
    }

    void in_order_traverse(Node* node, std::vector<T>& v) const {
        if (node != nullptr) {
            in_order_traverse(node->left, v);
            v.push_back(node->data);
            in_order_traverse(node->right, v);
        }
    }

    void post_order_traverse(Node* node, std::vector<T>& v) const {
        if (node != nullptr) {
            post_order_traverse(node->left, v);
            post_order_traverse(node->right, v);
            v.push_back(node->data);
        }
    }

    Node* remove_node(Node* node, const T& data) {
        if (node == nullptr) {
            return nullptr;
        }
        
        if (data < node->data) {
            node->left = remove_node(node->left, data);
        } else if (data > node->data) {
            node->right = remove_node(node->right, data);
        } else {
            // Node to delete found
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                size_--;
                return nullptr;
            } else if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                size_--;
                return temp;
            } else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                size_--;
                return temp;
            } else {
                // Node has two children
                Node* successor = node->right;
                while (successor->left != nullptr) {
                    successor = successor->left;
                }
                node->data = successor->data;
                node->right = remove_node(node->right, successor->data);
            }
        }
        return node;
    }

public:
    BinaryTree() : root(nullptr), size_(0) {}
    
    ~BinaryTree() {
        destroy(root);
    }

    void insert(const T& data) {
        if (root == nullptr) {
            root = new Node(data);
            size_++;
            return;
        }

        Node* current = root;
        while (true) {
            if (data <= current->data) {
                if (current->left == nullptr) {
                    current->left = new Node(data);
                    size_++;
                    break;
                }
                current = current->left;
            } else {
                if (current->right == nullptr) {
                    current->right = new Node(data);
                    size_++;
                    break;
                }
                current = current->right;
            }
        }
    }

    void remove(const T& data) {
        root = remove_node(root, data);
    }

    bool contains(const T& data) const {
        Node* current = root;
        while (current != nullptr) {
            if (data == current->data) {
                return true;
            }
            current = (data < current->data) ? current->left : current->right;
        }
        return false;
    }

    bool empty() const {
        return size_ == 0;
    }

    std::size_t size() const {
        return size_;
    }

    std::vector<T> pre_order() const {
        std::vector<T> result;
        pre_order_traverse(root, result);
        return result;
    }

    std::vector<T> in_order() const {
        std::vector<T> result;
        in_order_traverse(root, result);
        return result;
    }

    std::vector<T> post_order() const {
        std::vector<T> result;
        post_order_traverse(root, result);
        return result;
    }
};

}  // namespace structures
