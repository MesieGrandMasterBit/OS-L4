[![Build Status](https://travis-ci.org/MesieGrandMasterBit/OS-L4.svg?branch=main)](https://github.com/MesieGrandMasterBit/OS-L4)

## Проект «LiteSH»

### Язык программирования: С/С++

### Автор: Высотин Кирилл
### Реализовано:
#### В проекте создано два приложения сервер и клиент:
#### На стороне клиента:
##### Обрабатывается аргумент "-help" для вывода справки, в которой отображаются:
- Авторы;
- Все доступные аргументы;
- Краткое описание проекта;
- Примеры запуска.
- Сборка проекта будет осуществлятся с помощью Make
##### В проекте обрабатывается аргумент "-mv" для переноса файла в другую директорию, пример:
- `-mv <Имя директории> <Имя файла>`
##### В проекте обрабатывается аргумент "-dl" для удаления файла, пример:
- `-dl <Имя директории> <Имя файла>`
##### В проекте обрабатывается аргумент "-cp" для создания копии файла, пример:
- `-cp <Имя директории> <Имя файла>`
##### В проекте обрабатывается аргумент "-szf" для измерения размера файла, пример:
- `-szf <Имя файла>`
##### В проекте обрабатывается аргумент "-szd" для измерения размера директории, пример:
- `-szd <Имя директории>`
##### В проекте обрабатывается аргумент "-ls" для вывода всего содержимого директории, пример:
- `-ls <Имя директории>`
##### В проекте обрабатывается аргумент "-pinf" для вывода запущенных процессов из директории /proc, пример:
- `-pinf`
##### В проекте обрабатывается аргумент "-ch" для создания дочернего процесса:
- `-ch`
##### В проекте обрабатывается аргумент "-chbg" для создания дочернего процесса, который будет работать в фоновом режиме:
- `-chbg`
#### На стороне сервера:
##### Запускается с помощью systemd и работает в фоновом режиме
##### Обрабатывает все команды клиента
