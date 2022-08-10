#include <iostream>
#include <chrono>
#include <assert.h>

#include "datastruct/avl-tree.hpp"
#include "datastruct/binary-tree.hpp"
using namespace datastruct;
struct functionMETA {
    void (*funcPtr) ();
    const char *funcName;
};

// Questo non è un test, è solo un test per vedere in modo pratico la differenza di 
// efficienza fra i due algoritmi.
void time_benchmarch() {
    BinaryTree<int> bt;
    AVLTree<int> avl;
    const int test_size = 10000;

    auto start = std::chrono::steady_clock::now();
    for (int i = 0; i < test_size; i++) {
        bt.insert(i);
    }
 
    auto end = std::chrono::steady_clock::now();


    auto start2 = std::chrono::steady_clock::now();
    for (int i = 0; i < test_size; i++) {
        avl.insert(i);
    }
    auto end2 = std::chrono::steady_clock::now();
    std::cout << std::endl;
    std::cout << "Binary-tree: insertion of " << test_size 
        << " consecutive numbers, elapsed time in microseconds: "
        << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
        << " µs" << std::endl;

    std::cout << "AVL-tree: insertion of " << test_size 
        << " consecutive numbers, elapsed time in microseconds: "
        << std::chrono::duration_cast<std::chrono::microseconds>(end2 - start2).count()
        << " µs" << std::endl;
    

    auto start3 = std::chrono::steady_clock::now();
    for (int i = 0; i < test_size; i++) {
        bt.remove(i);
    }
    auto end3 = std::chrono::steady_clock::now();


    auto start4 = std::chrono::steady_clock::now();
    for (int i = 0; i < test_size; i++) {
        avl.remove(i);
    }
    auto end4 = std::chrono::steady_clock::now();


    std::cout << std::endl;
    std::cout << "Binary-tree: deletion of " << test_size 
        << " consecutive numbers (always head), elapsed time in microseconds: "
        << std::chrono::duration_cast<std::chrono::microseconds>(end3 - start3).count()
        << " µs" << std::endl;

    std::cout << "AVL-tree: deletion of " << test_size 
        << " consecutive numbers, elapsed time in microseconds: "
        << std::chrono::duration_cast<std::chrono::microseconds>(end4 - start4).count()
        << " µs" << std::endl;


    for (int i = 0; i < test_size; i++) {
        bt.insert(i);
    }

    auto start5 = std::chrono::steady_clock::now();
    for (int i = test_size - 1; i > 0; i--) {
        bt.remove(i);
    }
    auto end5 = std::chrono::steady_clock::now();


    std::cout << std::endl;
    std::cout << "Binary-tree: deletion of " << test_size 
        << " consecutive numbers (always tail), elapsed time in microseconds: "
        << std::chrono::duration_cast<std::chrono::microseconds>(end5 - start5).count()
        << " µs" << std::endl;
}

namespace test {
    void insertion() {
        AVLTree<int> h;
        for (int i = 0; i < 100; i++) {
            h.insert(i);
        }

        int *array = h.asArray();
        for (size_t i = 0; i < h.getSize(); i++) {
            assert(array[i] == (int) i);
        }
        assert(h.max() == 99);
        delete []array;
    }

    
    // fa due deletion, uno che testa il caso in cui ci siano entrambi i figli, l'altro 
    // nel caso in cui ci sia solo un figlio 
    void delete_root() {
        AVLTree<int> h;
        h.insert(1);
        h.insert(2);
        h.insert(3);
        /*
        ALBERO ATTUALE:
             2
            / \
           1   3  
        */
        h.remove(2);
        /*
             1
              \
               3  
        */
        int test_array[] = {1, 3};
        int *out = h.asArray();
        assert(test_array[0] == out[0] and test_array[1] == out[1]);
        assert(h.getSize() == 2u);
        assert(h.min() == 1);
        assert(h.max() == 3);
        delete[] out;

        h.remove(1);
        out = h.asArray();
        assert(test_array[1] == out[0]);
        assert(h.getSize() == 1u);

        assert(h.min() == 3);
        assert(h.max() == 3);
        delete[] out;

        h.remove(3);
        assert(h.getSize() == 0u);
    }

    // testa se insert e delete fanno update corretto di size
    void correct_size() {
        AVLTree<int> h;
        const int test_size = 100;
        for (int i = 0; i < test_size; i++) {
            h.insert(i);
            assert(h.getSize() == i + 1u);
        }

        // remove di un elemento che non c'è mantiene la lista uguale:
        h.remove(100);
        assert(h.getSize() == test_size);

        for (int i = 0; i < test_size; i++) {
            h.remove(i);
            assert(h.getSize() == test_size - i - 1u);
        }
    }

    void run(void (*f) (), const char *name) {
        std::cout << "Testando la funzione: " << name  << " --- ";
        f();
        std::cout << "Ok! ✔️" << std::endl;
    }
}

functionMETA func_table[] = {
    {test::insertion, "insertion"},
    {test::delete_root, "delete_root"},
    {test::correct_size, "correct_size"},
    {time_benchmarch, "time_benchmarch"},
};


int main() {
    int n_tests = sizeof(func_table) / sizeof(functionMETA);
    for (int i = 0; i < n_tests; i++) {
        test::run(func_table[i].funcPtr, func_table[i].funcName);
    }
}