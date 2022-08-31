#include "datastruct/queue.tpp"

#include <cassert>
#include <iostream>
using namespace datastruct;
struct functionMETA {
    void (*funcPtr)();
    const char *funcName;
};

namespace test {
    void basic_push_and_pop() {
        Queue<int> v;
        for (int i = 0; i < 20; i++) {
            v.push(i);
        }

        for (int i = 0; i < 20; i++) {
            int val = v.pop();
            assert(val == i);
        }
    }

    void accessElement() {
        Queue<int> v;
        for (int i = 0; i < 10; i++) {
            v.push(i);
        }
        for (int i = 0; i < 10; i++) {
            assert(v[i] == i);
        }
        for (int i = 0; i < 5; i++) {
            v.pop();
        }
        for (int i = 0; i < 5; i++) {
            v.push(i + 10);
        }
        for (int i = 0; i < 10; i++) {
            assert(v[i] == i + 5);
        }
    }

    void alternate_push_and_pop() {
        // questo è per verificare che la queue ciclica funzioni
        int counter = 0;
        Queue<int> v;
        for (int i = 0; i < 100; i++) {
            v.push(i);
            if (i % 5 == 0) {
                int val = v.pop();
                assert(val == counter);
                counter++;
            }
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
    {test::alternate_push_and_pop, "alternate_push_and_pop"},
    {test::accessElement, "accessElement"},
};

int main() {
    int n_tests = sizeof(func_table) / sizeof(functionMETA);
    for (int i = 0; i < n_tests; i++) {
        test::run(func_table[i].funcPtr, func_table[i].funcName);
    }
}