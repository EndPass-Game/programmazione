#include "directory-loader.hpp"

#include <cstdlib>
#include <cstring>
#include <dirent.h>  // per lettura delle directory, utilizzata nel corso di architettura

namespace loader {

    DirectoryLoader::DirectoryLoader(const char *dirname)
        : logger_("loader::DirectoryLoader") {
        logger_.info("Loading files from %s", dirname);

        DIR *dir = opendir(dirname);
        if (dir == NULL) {
            logger_.error("Could not open directory %s", dirname);
            logger_.info("Exiting...");
            exit(1);
        }
        const char *allowedExtension = ".txt";

        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL) {
            if (_isExtensionValid(entry->d_name, allowedExtension)) {
                char *fileName = new char[strlen(dirname) + strlen(entry->d_name) + 1];
                strcpy(fileName, dirname);
                strcat(fileName, entry->d_name);  // la null char finale è copiata, non serve metterlo.
                fileNames_.push_back(fileName);

                logger_.debug("Found file: %s", fileName);
            }
        }
        closedir(dir);
    }

    DirectoryLoader::~DirectoryLoader() {
        for (unsigned int i = 0; i < fileNames_.size(); i++) {
            delete[] fileNames_[i];
        }
    }

    const char *DirectoryLoader::getRandomFileName() {
        int index = rand() % fileNames_.size();
        return fileNames_[index];
    }

    datastruct::Vector<char *> DirectoryLoader::getFileNames() {
        return fileNames_;
    }

    bool DirectoryLoader::_isExtensionValid(const char *filename, const char *extension) {
        int len = strlen(filename);
        int extLen = strlen(extension);
        if (len < extLen) {
            return false;
        }
        for (int i = len - extLen; i < len; i++) {
            if (filename[i] != extension[i - len + extLen]) {
                return false;
            }
        }
        return true;
    }
};  // namespace loader