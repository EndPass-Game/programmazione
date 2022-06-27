#include <iostream>
#include <assert.h>

#include "datastruct/vector.hpp"

using namespace datastruct;
struct functionMETA {
    void (*funcPtr) ();
    const char *funcName;
};

namespace test {
    void example_test() {
        assert(true); // TODO: Non riesce a darmi un ❌, mi sa che deve essere sovrascritto, un wrapper ad assert?
    }

    // Wrappa una funzione di test per mostrare l'output di una funzione
    // se gli assert dentro la funzione di test sono corretti, da input a schermo
    void run(void (*f) (), const char *name) {
        std::cout << "Testando la funzione: " << name  << " --- ";
        f();
        std::cout << "Ok! ✔️" << std::endl;
    }
}

functionMETA func_table[] = {
    {test::example_test, "example_test"},
};


int main() {
    uint n_tests = sizeof(func_table) / sizeof(functionMETA);
    for (uint i = 0; i < n_tests; i++) {
        test::run(func_table[i].funcPtr, func_table[i].funcName);
    }
}