#include <iostream>
#include <io.h>
#include <direct.h>
#include <windows.h>
#include <sys/stat.h>
using namespace std;

bool checkDir(char *);
int clearDir(char *, bool &);
int defineOperation(char *);
bool emptyDir(char *);

const int cancellation = 1; // "Действие томенено пользователем"
const int successfully = 0; // "Скопировано успешно"

int main(int argc, char *argv[]) {
	setlocale(LC_CTYPE, "Russian");
	cout << "Программа для удаления каталогов (удаляются все вложенные папки и файлы)." << endl;
	if (argc < 2) {
		// программе переданы меньше одного аргумента
		// продолжение программы бесмысленно 
		cout << "Для запуска программы необходимо передать аргумент" << endl;
		return 0;
	}
	// получаем с командой строки пусть источника и путь назначения
	char source[_MAX_PATH];
	strcpy(source, argv[1]);
	int flag = false;
	// проверка является ли указанный каталог дирректорией
	flag = checkDir(source);
	if (!flag) {
		cout << "Не верно задан путь источника " << source << endl;
		return 0;
	}
	bool readOnly = true;
	int res = clearDir(source, readOnly);
	switch (res) {
		case cancellation:
			cout << "Действие оменено пользователем." << endl;
			break;
		case successfully:
			cout << "Выполнено успешно." << endl;
			cout << source << " удален" << endl;
			break;
		default:
			cout << "Были ошибки" << endl;
	}

	return 0;
}

/*
чистим дирректорию со всеми файлами
path - путь к дирректории
readOnly = true проверять атрибут readOnly, false - удалять без проверки
*/
int clearDir(char *path, bool &readOnly) {
	char *tempPath = new char[_MAX_PATH];
	strcpy(tempPath, path);
	strcat(tempPath, "\\*.*");
	char *fileName = new char[_MAX_PATH];
	int res = 0;
	int menu = 0; // 1. Удалять? 2. Пропустить? 3.Удалять для всех? 4. Отмена? 
	_finddata_t *file = new _finddata_t;
	long result = _findfirst(tempPath, file);
	if (result == -1)
		return res;
	long next = result;
	while (next != -1) {
		if (strcmp(file->name, ".") && strcmp(file->name, "..")) {
			strcpy(fileName, path);
			strcat(fileName, "\\");
			strcat(fileName, file->name);
			if (readOnly && _access(fileName, 2)) { // если установлен атрибут Read only и флаг поставлен readOnly
				menu = defineOperation(fileName);
				switch (menu) {
				case 1: // 1. Удалять? ничего не делаем
					break;
				case 2: // 2. Пропустить?
					next = _findnext(result, file);
					continue;
					break;
				case 3: // 3.Удалять для всех? 4. Отмена? 
					readOnly = false;
					break;
				case 4: // 4. Отмена? 
					return cancellation;
					break;
				}
			} 
			if (file->attrib&_A_SUBDIR) {// входим еще раз
				res = clearDir(fileName, readOnly);
				if (res == cancellation) {
					return cancellation;
				}
			}
			else { // это файл, его удаляем
				if (_access(fileName, 2)) {
					_chmod(fileName, _S_IWRITE);
				}
				res = remove(fileName);
			}
			if (res)
				break;
		}
		next = _findnext(result, file);
	}
	if (!res && emptyDir(path))
		res = _rmdir(path);
	delete[]fileName;
	delete[]tempPath;
	_findclose(result);
	delete file;

	return res;
}

bool emptyDir(char *path) {
	_finddata_t *fileinfo = new _finddata_t;
	char *tempPath = new char[_MAX_PATH];
	strcpy(tempPath, path);
	strcat(tempPath, "\\*.*");
	long result = _findfirst(tempPath, fileinfo);
	long next = result;
	while (next != -1) {
		if (strcmp(fileinfo->name, ".") && strcmp(fileinfo->name, "..")) {

			return false;	// нет не пустая

		}
		next = _findnext(result, fileinfo);
	}
	delete[]tempPath;
	_findclose(result);
	delete fileinfo;

	return true; // да пустая
}

int defineOperation(char *file) {
	int res;
	cout << file << " имеет атрибут Read only" << endl;
	cout << "Выбирите действие" << endl;
	cout << "1. Удалять" << endl;
	cout << "2. Пропустить" << endl;
	cout << "3. Удалять для всех" << endl;
	cout << "4. Отмена" << endl;
 	while (true) {
		cin >> res;
		if (cin.good()) {
			if (res >= 1 && res < 5) {
				break;
			}
		}
		cout << "Неверное значение. Введите 1, 2, 3 или 4" << endl;
		cin.clear();
		_flushall();
	}

	return res;
}


bool checkDir(char *path) {
	bool ret = false;
	_finddata_t *fileinfo = new _finddata_t;
	long result = _findfirst(path, fileinfo);
	if (result != -1 && fileinfo->attrib&_A_SUBDIR) {
		ret = true;
	}
	_findclose(result);
	delete fileinfo;

	return ret;
}

