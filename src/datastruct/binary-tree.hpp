#pragma once

#include <stddef.h>  // size_t

namespace datastruct {
    template <class T>
    class BinaryTree {
      protected:
        // Struttura interna per tenere il nodo di un albero
        struct Node {
            Node *left;
            Node *right;
            Node *parent;
            T data;
            Node(T data)
                : left(nullptr),
                  right(nullptr),
                  parent(nullptr),
                  data(data) {}
        };
        Node *head_;
        size_t size_;
        size_t counter_;  // variabile globale usata SOLO per asArray();

        void _setParentNode(Node *curr, Node *ptr) {
            if (curr == nullptr or curr->parent == nullptr) return;
            if (curr == curr->parent->left) {
                curr->parent->left = ptr;
            } else if (curr == curr->parent->right) {
                curr->parent->right = ptr;
            }
        }

        Node *_max(Node *node) {
            if (node == nullptr) return nullptr;
            Node *curr = node;
            while (curr->right != nullptr) {
                curr = curr->right;
            }
            return curr;
        }

        Node *_min(Node *node) {
            if (node == nullptr) return nullptr;
            Node *curr = node;
            while (curr->left != nullptr) {
                curr = curr->left;
            }
            return curr;
        }

        // ritorna la foglia su cui si può inserire il valore target
        // come figlio
        Node *_searchParent(T target) {
            if (head_ == nullptr) return nullptr;
            Node *curr = head_;
            Node *parent = nullptr;
            while (curr != nullptr) {
                parent = curr;
                if (target <= curr->data)
                    curr = curr->left;
                else
                    curr = curr->right;
            }
            return parent;
        }

        // ritorna prima istanza che fa match con target
        Node *_search(T target) {
            if (head_ == nullptr) return nullptr;
            Node *curr = head_;
            while (curr != nullptr) {
                if (curr->data == target) break;
                if (target > curr->data)
                    curr = curr->right;
                else
                    curr = curr->left;
            }
            return curr;
        }

        Node *_predecessor(Node *node) {
            if (node == nullptr) return nullptr;
            // caso 1: ha figlio sinistro
            Node *curr = node;
            if (curr->right != nullptr) return _max(curr->left);

            // caso 2: non ha figlio sinistro
            Node *parent = curr->parent;
            while (parent != nullptr and curr == parent->left) {
                curr = parent;
                parent = parent->parent;
            }
            return parent;
        }

        void _recDelete(Node *node) {
            if (node == nullptr) return;
            _recDelete(node->left);
            _recDelete(node->right);
            delete node;
        }

        void _debugPrint(Node *node) {
            if (node == nullptr) return;
            _debugPrint(node->left);
            std::cout << node->data;
            _debugPrint(node->right);
        }

        void _buildArray(T *array, Node *node) {
            if (node == nullptr) return;
            _buildArray(array, node->left);
            array[counter_] = node->data;
            counter_ += 1;
            _buildArray(array, node->right);
        }

        void _insert(Node *toInsert) {
            Node *parent = nullptr;
            if (head_ == nullptr) {
                head_ = toInsert;
            } else {
                parent = this->_searchParent(toInsert->data);
                if (toInsert->data <= parent->data) {
                    parent->left = toInsert;
                } else {
                    parent->right = toInsert;
                }
            }
            toInsert->parent = parent;
            size_ += 1;
        }

        Node *_remove(T elem) {
            Node *toDelete = this->_search(elem);
            if (toDelete == nullptr) {
                return nullptr;
            }
            Node *substitute = nullptr;
            // il nodo da rimuovere ha al massimo un figlio
            if (toDelete->left == nullptr or toDelete->right == nullptr) {
                if (toDelete->left != nullptr)
                    substitute = toDelete->left;
                else if (toDelete->right != nullptr)
                    substitute = toDelete->right;

                // sistema il pointer del nodo da sostituire
                // nota: non vengono settati left e right per evitare pointer a sé stessi
                if (substitute != nullptr) {
                    substitute->parent = toDelete->parent;
                }
            } else {  // ha entrambi i figli (predecessore esiste sempre)
                substitute = this->_predecessor(toDelete);
                // ************* NON CAMBIARE L'ORDINE CON ALTRE ISTRUZIONI IN QUESTO SCOPE
                // c'è il rischio di avere un node->left o right che punta a sé stesso,
                // causando ciclo infinito in altre funzioni
                _setParentNode(substitute, nullptr);
                // *************

                // sistema il pointer del nodo da sostituire (uguali a quello da eliminare)
                substitute->left = toDelete->left;
                substitute->right = toDelete->right;
                substitute->parent = toDelete->parent;

                // sistema il pointer dei figli del nodo da eliminare
                if (toDelete->left != nullptr) toDelete->left->parent = substitute;
                if (toDelete->right != nullptr) toDelete->right->parent = substitute;
            }

            // sistema il pointer del genitore
            if (toDelete == head_)
                head_ = substitute;
            else
                _setParentNode(toDelete, substitute);

            size_ -= 1;
            return toDelete;
        }

      public:
        BinaryTree() {
            head_ = nullptr;
            size_ = 0;
        }

        BinaryTree(T data) {
            head_ = new Node(data);
            size_ = 1;
        }

        ~BinaryTree() {
            _recDelete(head_);
        }

        T max() {
            Node *node = _max(head_);
            if (node == nullptr)
                return T();
            else
                return node->data;
        }

        T min() {
            Node *node = _min(head_);
            if (node == nullptr)
                return T();
            else
                return node->data;
        }

        T search(T target) {
            Node *node = _search(target);
            if (node == nullptr)
                return T();
            else
                return node->data;
        }

        size_t getSize() {
            return size_;
        }

        void insert(T elem) {
            Node *newNode = new Node(elem);
            _insert(newNode);
        }

        bool remove(T elem) {
            Node *toDelete = _remove(elem);
            delete toDelete;
            if (toDelete == nullptr)
                return false;
            else
                return true;
        }

        // ritorna la rappresentazione in array dell'albero con visita infissa.
        T *asArray() {
            if (head_ == nullptr) return nullptr;
            counter_ = 0;
            T *newArray = new T[size_];
            _buildArray(newArray, head_);
            return newArray;
        }
    };
}  // namespace datastruct
