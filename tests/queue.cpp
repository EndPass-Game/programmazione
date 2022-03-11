#include <iostream>
#include <cassert>

#include "queue.hpp"

namespace test {
    void basic_push_and_pop() {
        std::cout << "Testando la funzione: " << __func__ << " --- ";
        Queue<int> v;
        for (int i = 0; i < 20; i++) {
            v.push(i);
        }

        for (int i = 0; i < 20; i--) {
            assert(v.pop() == i);
        }
        std::cout << "Ok! ✔️" << std::endl;
    }
}

int main() {
    test::basic_push_and_pop();
}