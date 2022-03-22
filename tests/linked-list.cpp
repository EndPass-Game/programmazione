#include <iostream>
#include <assert.h>

#include "linked-list.hpp"

using namespace datastruct;
struct functionMETA {
    void (*funcPtr) ();
    const char *funcName;
};

namespace test {
    void push_front() {
        LinkedList<int> l;
        for (int i = 0; i < 100; i++) {
            l.push_front(i);
            assert(l.front() == i);
        }
    }

    void push_back() {
        LinkedList<int> l;
        for (int i = 0; i < 100; i++) {
            l.push_back(i);
            assert(l.back() == i);
        }
    }

    void push_and_pop() {
        LinkedList<int> l;
        const int test_size = 50;
        for (int i = 0; i < test_size; i++) {
            l.push_back(i);
        }
        for (int i = 0; i < test_size; i++) {
            assert(l.back() == test_size - i - 1);
            l.pop_back();
        }

        for (int i = 0; i < test_size; i++) {
            l.push_front(i);
        }
        for (int i = 0; i < test_size; i++) {
            assert(l.front() == test_size - i - 1);
            l.pop_front();
        }
    }
    
    void size_is_correct() {
        LinkedList<int> l;
        const int test_size = 50;
        for (int i = 0; i < test_size; i++) {
            l.push_back(i);
            assert(l.size() == i + 1u);
        }
        for (int i = 0; i < test_size; i++) {
            l.pop_back();
            assert(l.size() == test_size - i - 1u);
        }
    }

    void default_value() {
        LinkedList<int> l;
        assert(l.front() == int());
        assert(l.back() == int());
    }

    void run(void (*f) (), const char *name) {
        std::cout << "Testando la funzione: " << name  << " --- ";
        f();
        std::cout << "Ok! ✔️" << std::endl;
    }
}

functionMETA func_table[] = {
    {test::push_front, "push_front"},
    {test::push_back, "push_back"},
    {test::push_and_pop, "push_and_pop"},
    {test::size_is_correct, "size_is_correct"},
    {test::default_value, "default_value"},
};


int main() {
    uint n_tests = sizeof(func_table) / sizeof(functionMETA);
    for (uint i = 0; i < n_tests; i++) {
        test::run(func_table[i].funcPtr, func_table[i].funcName);
    }
}