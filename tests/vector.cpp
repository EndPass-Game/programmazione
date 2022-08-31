#include "datastruct/vector.tpp"

#include <cassert>
#include <iostream>

using namespace datastruct;
struct functionMETA {
    void (*funcPtr)();
    const char *funcName;
};

namespace test {
    void basic_push_and_pop() {
        Vector<int> v;
        for (int i = 0; i < 20; i++) {
            v.push_back(i);
        }

        for (int i = 19; i >= 0; i--) {
            assert(v.pop_back() == i);
        }
    }

    void empty_pop_remove() {
        Vector<int> v;
        for (int i = 0; i < 20; i++) {
            assert(v.pop_back() == int());
        }
        for (int i = 0; i < 20; i++) {
            assert(v.remove(i) == int());
        }
    }

    void correct_size() {
        Vector<int> v;
        for (size_t i = 0; i < 20; i++) {
            v.push_back(i);
            assert(v.size() == i + 1);
        }
    }

    void bracket_operator() {
        Vector<int> v;
        for (int i = 0; i < 20; i++) {
            v.push_back(i);
            assert(v[i] == i);
        }
        v[0] = 10;
        assert(v[0] == 10);
    }

    void resize_assign() {
        Vector<int> v;
        const int test_size = 20;
        v.assign(test_size, 1);
        for (int i = 0; i < test_size; i++) {
            assert(v[i] == 1);
        }
        v.resize(test_size * 2);
        for (int i = 0; i < test_size; i++) {
            assert(v[i] == 1);
        }

        v.resize(test_size / 2);
        for (int i = 0; i < test_size / 2; i++) {
            assert(v[i] == 1);
        }
    }

    // Wrappa una funzione di test per mostrare l'output di una funzione
    // se gli assert dentro la funzione di test sono corretti, da input a schermo
    void run(void (*f)(), const char *name) {
        std::cout << "Testando la funzione: " << name << " --- ";
        f();
        std::cout << "Ok! ✔️" << std::endl;
    }
}  // namespace test

functionMETA func_table[] = {
    {test::basic_push_and_pop, "basic_push_and_pop"},
    {test::empty_pop_remove, "empty_pop_remove"},
    {test::correct_size, "correct_size"},
    {test::bracket_operator, "bracket_operator"},
    {test::resize_assign, "resize_assign"},
};

int main() {
    int n_tests = sizeof(func_table) / sizeof(functionMETA);
    for (int i = 0; i < n_tests; i++) {
        test::run(func_table[i].funcPtr, func_table[i].funcName);
    }
}