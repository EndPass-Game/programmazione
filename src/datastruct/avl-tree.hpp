#pragma once
#include <stddef.h>  // size_t

#include "datastruct/binary-tree.hpp"

namespace datastruct {
    template <class T>
    class AVLTree : public BinaryTree<T> {
      private:
        struct AVLNode : public BinaryTree<T>::Node {
            unsigned int height;

            AVLNode(T elem)
                : BinaryTree<T>::Node(elem),
                  height(0) {}
        };

        void _leftRotation(AVLNode *node) {
            if (node == nullptr or node->right == nullptr) return;
            AVLNode *right = (AVLNode *) node->right;
            if (right->left != nullptr) right->left->parent = node;

            if (node == this->head_)
                this->head_ = right;
            else
                BinaryTree<T>::_setParentNode(node, right);

            // sistema i pointer dei due nodi che ruotano
            right->parent = node->parent;
            node->right = right->left;
            right->left = node;
            node->parent = right;

            _updateHeight(node);
            _updateHeight(right);
        }

        void _rightRotation(AVLNode *node) {
            if (node == nullptr or node->left == nullptr) return;
            AVLNode *left = (AVLNode *) node->left;
            if (left->right != nullptr) left->right->parent = node;

            if (node == this->head_)
                this->head_ = left;
            else
                BinaryTree<T>::_setParentNode(node, left);

            // sistema i pointer dei due nodi che ruotano
            left->parent = node->parent;
            node->left = left->right;
            left->right = node;
            node->parent = left;

            _updateHeight(node);
            _updateHeight(left);
        }

        void _updateHeight(AVLNode *node) {
            unsigned int currHeight = 0;

            AVLNode *left = (AVLNode *) node->left;
            AVLNode *right = (AVLNode *) node->right;
            if (left != nullptr and left->height >= currHeight) {
                currHeight = left->height + 1;
            }
            if (right != nullptr and right->height >= currHeight) {
                currHeight = right->height + 1;
            }
            node->height = currHeight;
        }

        int _getBalanceFactor(const AVLNode *node) const {
            AVLNode *left = (AVLNode *) node->left;
            AVLNode *right = (AVLNode *) node->right;
            int leftHeight = left == nullptr ? 0 : (int) left->height + 1;
            int rightHeight = right == nullptr ? 0 : (int) right->height + 1;
            return leftHeight - rightHeight;
        }

        void _rebalanceNode(AVLNode *node) {
            int balanceFactor = _getBalanceFactor(node);
            if (balanceFactor >= -1 and balanceFactor <= 1)
                return;
            else if (balanceFactor == 2) {
                if (_getBalanceFactor((AVLNode *) node->left) >= 0) {
                    _rightRotation(node);
                } else {
                    _leftRotation(node);
                    _rightRotation((AVLNode *) node->parent);
                }
            } else if (balanceFactor == -2) {
                if (_getBalanceFactor((AVLNode *) node->right) <= 0) {
                    _leftRotation(node);
                } else {
                    _rightRotation(node);
                    _leftRotation((AVLNode *) node->parent);
                }
            }
        };

      public:
        // ******** FUNZIONI DEL PADRE ********
        // Queste funzioni sono presenti nella funzione della classe padre
        // e sono esattamente uguali a quelle,
        // ma che per chiarezza di interfaccia sono riportate anche qui
        T search(T data) {
            return BinaryTree<T>::search(data);
        }

        T max() {
            return BinaryTree<T>::max();
        }

        T min() {
            return BinaryTree<T>::min();
        }

        size_t getSize() {
            return BinaryTree<T>::getSize();
        }

        T *asArray() {
            return BinaryTree<T>::asArray();
        }
        // ***** FINE FUNZIONI DEL PADRE *****

        bool remove(T elem) {
            AVLNode *toDelete = (AVLNode *) BinaryTree<T>::_remove(elem);
            AVLNode *parent = nullptr;
            if (toDelete != nullptr) parent = (AVLNode *) toDelete->parent;
            while (parent != nullptr) {
                _updateHeight(parent);
                int balance = _getBalanceFactor(parent);
                if (balance < -1 or balance > 1) _rebalanceNode(parent);
                parent = (AVLNode *) parent->parent;
            }
            delete toDelete;

            if (toDelete == nullptr)
                return false;
            else
                return true;
        }

        void printBT(const std::string &prefix, const AVLNode *node, bool isLeft) {
            if (node != nullptr) {
                std::cout << prefix;

                std::cout << (isLeft ? "├──" : "└──");

                // print the value of the node
                std::cout << node->data << std::endl;

                // enter the next tree level - left and right branch
                printBT(prefix + (isLeft ? "│   " : "    "), (AVLNode *) node->left, true);
                printBT(prefix + (isLeft ? "│   " : "    "), (AVLNode *) node->right, false);
            }
        }

        void insert(T elem) {
            AVLNode *newNode = new AVLNode(elem);
            BinaryTree<T>::_insert(newNode);

            AVLNode *parent = (AVLNode *) newNode->parent;
            bool hasBalanced = false;
            while (!hasBalanced and parent != nullptr) {
                _updateHeight(parent);
                int balance = _getBalanceFactor(parent);
                if (balance < -1 or balance > 1) {
                    _rebalanceNode(parent);
                    hasBalanced = true;
                }
                parent = (AVLNode *) parent->parent;
            }
        }
    };
}  // namespace datastruct
