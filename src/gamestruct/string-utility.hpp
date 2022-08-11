#pragma once
#include <string.h>

#include "datastruct/vector.hpp"

namespace stringUtility {
    char *copyString(char const *str);
    char *copyString(char const *str, int lenght);
    char *repeatChar(int len, char charater);
    datastruct::Vector<char *> splitByLen(char const *str, int len);
};  // namespace stringUtility