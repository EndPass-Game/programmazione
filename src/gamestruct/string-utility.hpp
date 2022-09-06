#pragma once
#include <string.h>

#include "datastruct/vector.tpp"

namespace stringUtility {
    /**
     * @brief ritorna una copia della stringa in input che deve essere liberata
     */
    char *copyString(char const *str);

    /**
     * @brief ritorna una copia della stringa fino la lunghezza `lenght`
     * che deve essere liberata
     */
    char *copyString(char const *str, int lenght);

    /**
     * @brief ritorna una stringa contenente `len` volte il carattere `charater`
     * che deve essere liberata
     */
    char *repeatChar(int len, char charater);

    /**
     * @brief ritorna la rappresentazione in stringa del numero inserito.
     * la stringa deve essere liberata.
     */
    char *intToString(int number);

    /**
     * @brief ritorna una stringa contenente la concatenazione di `str1` e `str2`
     * che deve essere liberata
     */
    char *concat(char const *str1, char const *str2);

    /**
     * @brief ritorna un vettore con le stringhe ottenute dividendo `str`
     * a seconda della sua lunghezza.
     * L'intero array deve essere liberato.
     *
     * esempio:
     * aaabbbccc, len = 3, ritorna [aaa, bbb, ccc]
     */
    datastruct::Vector<char *> splitByLen(char const *str, int len);
};  // namespace stringUtility
