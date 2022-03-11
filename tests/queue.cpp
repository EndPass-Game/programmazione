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

        for (int i = 0; i < 20; i++) {
            int val = v.pop();
            assert(val == i);
        }
        std::cout << "Ok! ✔️" << std::endl;
    }

    void alternate_push_and_pop() {
        std::cout << "Testando la funzione: " << __func__ << " --- ";
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
        std::cout << "Ok! ✔️" << std::endl;
    }
}

int main() {
    test::basic_push_and_pop();
    test::alternate_push_and_pop();
}