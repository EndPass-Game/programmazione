#include "datastruct/binary-tree.hpp"

#include <assert.h>
#include <iostream>
using namespace datastruct;
struct functionMETA {
    void (*funcPtr)();
    const char *funcName;
};

namespace test {
    void insertion() {
        BinaryTree<int> h;
        for (int i = 0; i < 100; i++) {
            h.insert(i);
        }

        int *array = h.asArray();
        for (size_t i = 0; i < h.getSize(); i++) {
            assert(array[i] == (int) i);
        }
        assert(h.max() == 99);
        delete[] array;
    }

    // fa due deletion, uno che testa il caso in cui ci siano entrambi i figli, l'altro
    // nel caso in cui ci sia solo un figlio
    void delete_root() {
        BinaryTree<int> h;
        h.insert(2);
        h.insert(3);
        h.insert(1);
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
        BinaryTree<int> h;
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

    void run(void (*f)(), const char *name) {
        std::cout << "Testando la funzione: " << name << " --- ";
        f();
        std::cout << "Ok! ✔️" << std::endl;
    }
}  // namespace test

functionMETA func_table[] = {
    {test::insertion, "insertion"},
    {test::delete_root, "delete_root"},
    {test::correct_size, "correct_size"},
};

int main() {
    int n_tests = sizeof(func_table) / sizeof(functionMETA);
    for (int i = 0; i < n_tests; i++) {
        test::run(func_table[i].funcPtr, func_table[i].funcName);
    }
}