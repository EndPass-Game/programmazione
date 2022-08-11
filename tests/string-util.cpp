#include <assert.h>
#include <iostream>
#include <string.h>

#include "datastruct/vector.hpp"
#include "gamestruct/string-utility.hpp"

using namespace datastruct;
struct functionMETA {
    void (*funcPtr)();
    const char *funcName;
};

namespace test {
    void copyString() {
        char const *str = "Hello World";
        char const *str1 = stringUtility::copyString(str);
        assert(strcmp(str, str1) == 0);  // TODO: Non riesce a darmi un ❌, mi sa che deve essere sovrascritto, un wrapper ad assert?
        delete[] str1;
        str1 = stringUtility::copyString(str, 5);
        str = "Hello";
        assert(strcmp(str, str1) == 0);  // TODO: Non riesce a darmi un ❌, mi sa che deve essere sovrascritto, un wrapper ad assert?
        delete[] str1;
    }
    void repeatChar() {
        char const *str = "aaaaaaaaaa";
        char const *str1 = stringUtility::repeatChar(10, 'a');
        assert(strcmp(str, str1) == 0);  // TODO: Non riesce a darmi un ❌, mi sa che deve essere sovrascritto, un wrapper ad assert?
        delete[] str1;
    }
    void splitString() {
        char const *str = "abcdefghijklmnopqrstuvwxyz";
        char const *array[6] = {"abcde", "fghij", "klmno", "pqrst", "uvwxy", "z"};
        datastruct::Vector<char *> vec = stringUtility::splitByLen(str, 5);
        assert(vec.size() == 6);
        for (size_t i = 0; i < vec.size(); i++) {
            assert(strcmp(array[i], vec[i]) == 0);
            delete[] vec[i];
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
    {test::copyString, "copyString"},
    {test::repeatChar, "repeatchar"},
    {test::splitString, "splitString"},
};

int main() {
    int n_tests = sizeof(func_table) / sizeof(functionMETA);
    for (int i = 0; i < n_tests; i++) {
        test::run(func_table[i].funcPtr, func_table[i].funcName);
    }
}