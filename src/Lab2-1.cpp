#include <iostream>
#include "Lab2.hpp"

using namespace std;

void showMenu()
{
	cout << "==========================" << endl;
	cout << "Сделайте ваш выбор:" << endl;
	cout << " a - Разработчики" << endl;
	cout << " u - Доступные аргументы" << endl;
	cout << " r - Описание" << endl;
	cout << " e - Пример" << endl;
	cout << "==========================" << endl;
	cout << "Введите аргумент: ";
}

void printArguments()
{
	cout << "==============================================================" << endl;
	cout << " m - Перемещение файла" << endl;
	cout << " c - Копирование файла" << endl;
	cout << " d - Удаление файла из данной папки" << endl;
	cout << " D - Удаление файла из другой папки" << endl;
	cout << " s - Подсчёт общего размера указанной файла" << endl;
	cout << " S - Подсчёт общего размера указанной директории" << endl;
	cout << " f - Отображение всех файлов в указанной директории" << endl;
	cout << " p - Отображение всех процессов из файловой системы procfs" << endl;
        cout << "==============================================================" << endl;
        cout << "ЕСЛИ ФАЙЛ НА УРОВЕНЬ ВЫШЕ, ТО ИСПОЛЬЗУЙТЕ В В НАЧАЛЕ ../" << endl;
}

void printReadme()
{
    cout << "==============================================================" << endl;
    cout << "Данная программа включает в себя:"<< endl <<
    "-Копирование файла;" << endl <<
    "-Перемещение файла;" << endl <<
    "-Удаление файла;"<< endl <<
    "-Удаление файла из папки;" << endl <<
    "-Подсчёт общего размера указанной директории или файла; "<< endl <<
    "-Отображение всех файлов в указанной директории;" << endl <<
    "-Отображение всех процессов из фаловой системы procfs"<< endl;
    cout << "==============================================================" << endl;
}

void CreateFile()
{
	char* name;
	name = (char*)malloc(sizeof(char) * 256);
	cout << "Введите название файла: ";
	cin >> name;
	ofstream File;
	File.open(name);
	File.close();
}

int main()
{
    char command, camm2;
    string path, fileName;
    int S;
    char* dir;
    char* file;
    dir = (char*)malloc(sizeof(char) * 256);
    file = (char*)malloc(sizeof(char) * 256);
    do {
	cout << "\033c";
        showMenu();
        cin >> command;
        switch(command)
        {
            case 'a' : cout << " Высотин Кирилл Евгеньевич \n Пахомов Илья Максимович \n Юрьев Юрий Вадимович"<< endl; 
                            break;
            case 'u' : printArguments();
		do {
			cout << "Введите, сколько хотите создать файлов: ";
			cin >> S;
			if (S > 0) {
				for (int i=0;i<S;i++) {
					CreateFile();
				}
			}
			cout << "Введите аргумент: ";
			cin >> camm2;
			switch(camm2)
			{
				case 'm' : cout << "Введите название папки: ";
					cin >> path;
					cout << "Введите имя файла: ";
                                        cin >> fileName;
					cout << endl;
                                        moveFile(path,fileName);
                                                break;

				case 'c' : cout << "Введите название папки: ";
                                        cin >> path;
                                        cout << "Введите имя файла: ";
                                        cin >> fileName;
					cout << endl;
                                        copyFile(path,fileName);
                                                break;

				case 'd' : cout << "Введите название файла: ";
					cin >> fileName;
					deleteFile(fileName);
						break;

				case 'D' : cout << "Введите название папки: ";
					cin >> path;
					cout << "Введите имя файла: ";
				      	cin >> fileName;
					DeleteFile(path, fileName);
						break;

				case 's' : cout << "Введите название файла: ";
					cin >> file;
					cout << getFileSize(file) << " Kb" << endl;
						break;

                                case 'S' : cout << "Введите имя папки: ";
                                        cin >> dir;
                                        cout << getDirSize(dir) << " Kb" << endl;
						break;


				case 'f' : cout << "Введите имя папки: ";
					cin >> dir;
					displayAllFiles(dir);
						break;

				case 'p' : displayProc();
						break;

				default : cout << "Не понял. Попробуйте ещё раз" << endl;
			}
				cout << "Продолжить работу с этим аргументом? (y) ";
				cin >> camm2;
			} while (camm2 == 'y' || camm2 == 'Y');
				break;

            case 'r' : printReadme();
                            break;
            case 'e' : cout << "Всем ку, уважаемые дамы и господа"<<endl;
                            break;
            default : cout << "Каво? \n";
         }
        cout << "Продолжить работу? (y) ";
        cin >> command;
    } while (command == 'y' || command == 'Y');
    return 0;
}
