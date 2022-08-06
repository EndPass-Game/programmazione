#include <cstring> 
#include "loader/directory-loader.hpp"
#include "loader/loader-handler.hpp"
#include "datastruct/vector.hpp"


int getExtensionIdx(char *filename) {
    // se il punto è all'inizio, non è considerato come una estensione
    int len = strlen(filename);
    for (int i = len - 1; i >= 0; i--) {
        if (filename[i] == '.') {
            return i;
        }
    }
    return 0;
}

char *substituteExtensions(char *filename, const char *extension) {
    int extIdx = getExtensionIdx(filename);
    char *newFilename;
    if (extIdx == 0) {
        newFilename = new char[strlen(filename) + strlen(extension) + 1];
        strcpy(newFilename, filename);
    } else {
        newFilename = new char[extIdx + strlen(extension)];
        for (int i = 0; i < extIdx; i++) {
            newFilename[i] = filename[i];
        }
    }
    strcat(newFilename, extension);
    return newFilename;
}

void print(char *source, char *target) {
    loader::LoaderHandler *handler = loader::LoaderHandler(source);
    char map[12][62];  
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 61; j++) {
            map[i][j] = ' ';
        }
        map[i][61] = '\n';
    }

    // print segments 
    // TODO(ang):
    // print doors
    // TODO(ang):

    // print player 
    // TODO(ang):

    // print artifacts
    // TODO(ang):

    // print power 
    // TODO(ang):

    delete handler; 
}

int main(int argc, char *argv[]) {
    loader::DirectoryLoader *loader = new loader::DirectoryLoader();
    char []fileName = loader->getAllFilenames();
    int i = 0;
    while (fileName[i] != '\0') {
        char *target = substituteExtensions(fileName[i], ".map");
        print(fileName[i], target);
        delete target; 
        i++;
    }
    delete loader;
    return 0;
}