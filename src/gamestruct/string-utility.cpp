#include "gamestruct/string-utility.hpp"

namespace stringUtility
{
    char *copyString(char const *str, int length) {
        char *newString = new char[length + 1];
        for (int i = 0; i < length; i++)
        {
            newString[i] = str[i];
        }
        newString[length] = '\0';
        return newString;
    }

    char *copyString(char const *str) {
        return copyString(str, strlen(str));
    }

    char *repeatChar(int len, char charater) {
        char *newString = new char[len + 1];
        for (int i = 0; i < len; i++)
        {
            newString[i] = charater;
        }
        newString[len] = '\0';
        return newString;
    }

    datastruct::Vector<char *> splitByLen(char const *str, int len)
    {
        datastruct::Vector<char *> result;
        int strLen = strlen(str);
        for (int i = 0; i < strLen; i += len)
        {
            result.push_back(copyString(str + i, (len > strLen - i) ? strLen - i : len));
        }
        return result;
    }

}; // namespace stringUtility