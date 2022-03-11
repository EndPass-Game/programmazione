#include <iostream>
#include <cassert>

#include "vector.hpp"

// TODO: questi test falliscono, errori di compilazione
namespace test {
    void basic_push_and_pop() {
        std::cout << "Testando la funzione: " << __func__ << " --- ";
        Vector<int> v;
        for (int i = 0; i < 20; i++) {
            v.push_back(i);
        }

        for (int i = 19; i >= 0; i--) {
            assert(v.pop_back() == i);
        }
        std::cout << "Ok! ✔️" << std::endl;
    }

    void correct_size() {
        std::cout << "Testando la funzione: " << __func__ << " --- ";
        Vector<int> v;
        for (uint i = 0; i < 20; i++) {
            v.push_back(i);
            assert(v.size() == i + 1);
        }
        std::cout << "Ok! ✔️" << std::endl;
    }
}

int main() {
    test::basic_push_and_pop();
    test::correct_size();
}