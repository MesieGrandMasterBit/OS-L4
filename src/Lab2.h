#ifndef LAB2_H
#define LAB2_H

#include <string>
#include <iostream>
#include <experimental/filesystem>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <fstream>
#include <pwd.h>
#include <sys/types.h>
#include <iomanip>

using namespace std;

// Основа
void showMenu();
void printArguments();
void printReadme();
void CreateFile();

// Копирование файла
int copyFile(string path, string fileName);

// Перемещение файла
int moveFile(string path, string fileName);

// Удаление файлов
int deleteFile(string fileName);
int DeleteFile(string path, string fileName);

// Процессы
int IsNumeric(const char* ccharptr_CharacterList);
int displayProc();

// Показать все файлы
int displayAllFiles(const char *dirName);

// Размер файла и директории
int getFileSize(const char *fileName);
int getDirSize(const char *dirName);

int executeRequest(int argc, char *argv[]);

#endif
