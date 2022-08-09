#pragma once
#include <string.h>
#include "datastruct/vector.hpp"

namespace stringUtility{
    char* copyString(char* str);
    char* copyString(char* str,int lenght);
    char* repeatChar(int len, char charater);
    datastruct::Vector<char*> splitByLen(char* str, int len);
};