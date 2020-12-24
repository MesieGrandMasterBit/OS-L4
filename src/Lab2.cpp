#include "Lab2.h"
const char *HELP_FLAG = "-help";
const char *MOVE_FLAG = "-mv";
const char *DELETE_FLAG = "-dl";
const char *COPY_FLAG = "-cp";
const char *LS_FLAG = "-ls";
const char *SZF_FLAG = "-szf";
const char *SZD_FLAG = "-szd";
const char *PROC_FLAG = "-pinf";

#define _GNU_SOURCE
#define PROC_DIRECTORY "/proc/"

using namespace std;

int deleteFile(string fileName);
int DeleteFile(string path, string fileName);
// Копирование файла
int copyFile(string path, string fileName) {
    int pos;
    string newFileName;
    pos = fileName.rfind("/");

    if (pos != -1) {
        newFileName = fileName.substr(pos + 1);
        path = path + "/" + newFileName;
    } else
        path = path + "/" + fileName;

    ifstream file (fileName, ios_base::in | ios_base::binary);
    ofstream newFile (path, ios_base::out | ios_base::binary);

    if (file.is_open() && newFile.is_open()) {
        newFile << file.rdbuf();
    file.close();
    newFile.close();
	return 0;
   } else {
        cout << "Файл не найден" << endl;
		return 1;
	}
}

// Перемещение файла
int moveFile(string path, string fileName) {
    if ((copyFile(path, fileName) == 0) && (deleteFile(fileName) == 0)) return 0;
		else return 1;

}

// Удаление файла
int deleteFile(string fileName)
{
    const char *str = fileName.c_str();
    if (remove(str) != 0) {
        cout << "Не удалось удалить файл" << endl;
		return 1;
	} else return 0;
}

int DeleteFile(string path, string fileName) {
    path = path + "/" + fileName;
    const char *str = path.c_str();
    if (remove(str) != 0) {
        cout << "Не удалось удалить файл" << endl;
		return 1;
	} else return 0;
}

// Процессы
int IsNumeric(const char* ccharptr_CharacterList)
{
    for ( ; *ccharptr_CharacterList; ccharptr_CharacterList++)
        if (*ccharptr_CharacterList < '0' || *ccharptr_CharacterList > '9')
            return 0; // false
    return 1; // true
}

int displayProc()
{
    struct dirent* dirEntity = NULL;
    DIR* dir_proc;

    dir_proc = opendir(PROC_DIRECTORY) ;
    if (dir_proc == NULL)
    {
        perror("Не удалось открыть " PROC_DIRECTORY " директорию") ;
        return (pid_t)-2 ;
    }

    while ((dirEntity = readdir(dir_proc)) != 0) 
    {
        if (dirEntity->d_type == DT_DIR) {
            if (IsNumeric(dirEntity->d_name)) {
                string path = string(PROC_DIRECTORY) + dirEntity->d_name + "/cmdline";

                ifstream cmdLineFile(path.c_str());
                string cmdLine;
                if (cmdLineFile) {
                    getline(cmdLineFile, cmdLine);
                }
                cout << "pid: " << dirEntity->d_name << " " << cmdLine << endl;
            }
        }
    }
    closedir(dir_proc);
}

// Показать файлы
int displayAllFiles(const char *dirName)
{
    DIR *dir = opendir(dirName);
    if (dir == nullptr)
    {
        std::cout << "Неудалось открыть каталог" << dirName << std::endl;
        return -1;
    }

    dirent *contentInfo;
    std::cout << "Содержимое каталога " << dirName << ":\n";
    while ((contentInfo = readdir(dir)) != nullptr)
    {
        if (strcmp(contentInfo->d_name, ".") != 0 && strcmp(contentInfo->d_name, "..") != 0)
            std::cout << contentInfo->d_name << std::endl;
    }
    closedir(dir);
    return 0;
}

// Размер файла или директории
int getFileSize(const char * fileName)
{
    struct stat file_stat;
    stat(fileName, &file_stat);
    return file_stat.st_size;
}

int getDirSize(const char *dirName)
{
    DIR *dir;
    dirent *pdir;
    struct stat st;
    long Size = 0;
    char *tmpstr; //буфер пути
    dir = opendir(dirName);
	if(dir == NULL)
	{
	    perror("Something happened trying to open directory");
	    exit(1);
	}
	while((pdir = readdir(dir)) != NULL) 
	{
		if(pdir->d_name[0] == '.') continue;
		asprintf(&tmpstr, "%s/%s", dirName, pdir->d_name);//выводит и сразу же записывает в памяти директорию, в которую заходит, с указанием её пути
		if(lstat(tmpstr, &st) != 0)//ошибка про чтении файла
		{
		    perror("Что-то случилось с файлом.");
		    exit(1);
		};
		if(S_ISDIR(st.st_mode)) getDirSize(tmpstr); //проверка на доступность файла
		else{
		    //fprintf(stdout, "   %ld: - Filename : %s\n",st.st_size, pdir->d_name); //доп. проверка файлов
		    Size += st.st_size;
		}
    }
    return Size;
}

int executeRequest(int argc, char *argv[])
{
    if (argc < 2)
    {
        cout << "Ошибка! Слишком мало аргументов -help для помощи\n";
        return -1;
    }

    char *flag = nullptr;
    for (int i = 1; i < argc; i++)
    {
        flag = argv[i];
        if (strcmp(flag, HELP_FLAG) == 0)
        {
            cout << "Автор (ИС-841): Высотин Кирилл\n"
                      << "Аргументы:\n"
                      << "1) -mv <oldName> <newName> - перемещает файл из oldName в newName\n"
                      << "Пример: -mv code.cpp src/code.cpp\n"
                      << "2) -dl <fileName> - удаляет файл fileName\n"
                      << "Пример: -dl src/code.cpp\n"
                      << "3) -cp <fileName> <destionation> - копирует файл fileName в destionation\n"
                      << "Пример: -cp src/code.cpp ../code.cpp\n"
                      << "4) -ls <fileName> - показывает содержимое каталога fileName\n"
                      << "Пример: -ls src/\n"
                      << "3) -sz <fileName> - показывае размер файла или каталога fileName\n"
                      << "Пример: -sz src/\n"
                      << "3) -pinf - показывает информацию о процессах из procfs\n"
                      << "Пример: -pinf\n";
            continue;
        }
        if (strcmp(flag, MOVE_FLAG) == 0)
        {
            if (argc < i + 2) // 2 означает, что присутствуют стрый путь и новый
                cout << "Ошибка! Недостаточно аргументов для флага " << MOVE_FLAG << std::endl;
            else
            {
		//moveFile(argv[i + 1], argv[i + 2]);
                if (moveFile(argv[i + 1], argv[i + 2]) == 0)
                {
                    cout << "Файл успешно перенесен!\n";
                }
                else
                {
                    cout << "Ошибка! Неудалось переместить файл\n";
                };
                i += 2;
            }
            continue;
        }
        if (strcmp(flag, DELETE_FLAG) == 0)
        {
            if (argc < i + 2)
                cout << "Ошибка! Недостаточно аргументов для флага " << DELETE_FLAG << endl;
            else
            {
		//DeleteFile(argv[i + 1], argv[i + 2]);
                if (DeleteFile(argv[i + 1], argv[i + 2]) == 0)
                {
                    cout << "Файл успешно удален!\n";
                }
                else
                {
                    cout << "Ошибка! Не удалось удалить файл\n";
                };
                i += 2;
            }
            continue;
        }
        if (strcmp(flag, COPY_FLAG) == 0)
        {
            if (argc < i + 2)
                cout << "Ошибка! Недостаточно аргументов для флага " << COPY_FLAG << endl;
            else
            {
		//copyFile(argv[i + 1], argv[i + 2]);
                if (copyFile(argv[i + 1], argv[i + 2]) == 0)
                {
                    cout << "Файл успешно копирован!\n";
                }
                else
                {
                    cout << "Ошибка! Неудалось скопировать файл\n";
                };
                i += 2;
            }
            continue;
        }
        if (strcmp(flag, LS_FLAG) == 0)
        {
            if (argc < i + 1)
                cout << "Ошибка! Недостаточно аргументов для флага " << LS_FLAG << endl;
            else
            {
                displayAllFiles(argv[i + 1]);
                ++i;
            }
            continue;
        }
        if (strcmp(flag, SZF_FLAG) == 0)
        {
            if (argc < i + 1)
                cout << "Ошибка! Недостаточно аргументов для флага " << SZF_FLAG << endl;
            else
            {
                try
                {
                    cout << getFileSize(argv[i + 1]) << " byte\n";
                }
                catch (std::string error)
                {
                    cout << error << endl;
                }
                ++i;
            }
            continue;
        }
        if (strcmp(flag, SZD_FLAG) == 0)
        {
            if (argc < i + 1)
                cout << "Ошибка! Недостаточно аргументов для флага " << SZD_FLAG << endl;
            else
            {
                try
                {
                    cout << getDirSize(argv[i + 1]) << " byte\n";
                }
                catch (std::string error)
                {
                    cout << error << endl;
                }
                ++i;
            }
            continue;
        }
        if (strcmp(flag, PROC_FLAG) == 0)
        {
            try
            {
                displayProc();
            }
            catch (string error)
            {
                cout << "error" << endl;
            }
            continue;
        }
        cout << "Ошибка! Неизвестный флаг " << flag << endl;
    }
    return 0;
}
