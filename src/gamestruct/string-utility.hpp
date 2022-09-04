#pragma once
#include <string.h>

#include "datastruct/vector.tpp"

namespace stringUtility {
    char *copyString(char const *str);
    char *copyString(char const *str, int lenght);
    char *repeatChar(int len, char charater);
    char *intToString(int number);
    char *concat(char const *str1, char const *str2);
    datastruct::Vector<char *> splitByLen(char const *str, int len);
};  // namespace stringUtility
