#include "gamestruct/string-utility.hpp"

namespace stringUtility {
    char *copyString(char const *str, int length) {
        char *newString = new char[length + 1];
        for (int i = 0; i < length; i++) {
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
        for (int i = 0; i < len; i++) {
            newString[i] = charater;
        }
        newString[len] = '\0';
        return newString;
    }

    datastruct::Vector<char *> splitByLen(char const *str, int len) {
        datastruct::Vector<char *> result;
        int strLen = strlen(str);
        for (int i = 0; i < strLen; i += len) {
            result.push_back(copyString(str + i, (len > strLen - i) ? strLen - i : len));
        }
        return result;
    }

    char* intToString(int number){
        int len = 0;
        int temp = number;
        while(temp != 0){
            temp /= 10;
            len++;
        }
        char *result = new char[len + 1];
        result[len] = '\0';
        for(int i = len - 1; i >= 0; i--){
            result[i] = number % 10 + '0';
            number /= 10;
        }
        return result;
    }

    char* concat(char const *str1, char const *str2){
        int len1 = strlen(str1);
        int len2 = strlen(str2);
        char *result = new char[len1 + len2 + 1];
        for(int i = 0; i < len1; i++){
            result[i] = str1[i];
        }
        for(int i = 0; i < len2; i++){
            result[i + len1] = str2[i];
        }
        result[len1 + len2] = '\0';
        return result;
    }

};  // namespace stringUtility