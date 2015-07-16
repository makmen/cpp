#include <iostream>
#include <io.h>
#include <direct.h>
#include <sys/stat.h>
using namespace std;

bool checkDir(char *);
bool emptyDir(char *);
int copyDir(char *, char *, bool &);
bool copyFile(char *, char *, char *);
bool existsFile(char *, char *);
int defineOperation(char *);
void clearEmptyDir(char *);

const int successfully = 0;		// "Скопировано успешно"
const int cancellation = 1;		// "Действие томенено пользователем"
const int errorCopy = -1;		// "Ошибки копирования"

int main(int argc, char *argv[]) {
	setlocale(LC_CTYPE, "Russian");
	if (argc < 3) {
		// программе переданы меньше двух аргументов, продолжение программы бесмысленно 
		cout << "Для запуска программы необходимо передать два аргумента" << endl;
		return 0;
	}
	// получаем с командой строки пусть источника и путь назначения
	char source[_MAX_PATH];
	strcpy(source, argv[1]);
	bool flag = false;
	// проверка является ли указанный каталог дирректорией
	flag = checkDir(source);
	if (!flag) {
		cout << "Не верно задан путь источника " << source << endl;
		return 0;
	}
	char destination[_MAX_PATH];
	strcpy(destination, argv[2]);

	flag = checkDir(destination);
	if (!flag) {
		// пытаемся создать
		if (_mkdir(destination)) {
			cout << "Не верно задан путь назначения " << destination << endl;
			return 0;
		}
	}
	bool rewriteAll = false;
	int res = copyDir(source, destination, rewriteAll);
	bool readOnly = false;
	switch (res) {
	case cancellation:
		cout << "Действие оменено пользователем." << endl;
		break;
	case successfully:
		// чистим все папки если есть
		clearEmptyDir(source);
		_mkdir(source);
		cout << "Выполнено успешно." << endl;
		cout << source << " скопирован в " << destination << endl;
		break;
	default:
		cout << "Были ошибки" << endl;
	}

	return 0;
}

void clearEmptyDir(char *path) {
	char *tempPath = new char[_MAX_PATH];
	char *fileNameSource = new char[_MAX_PATH];
	strcpy(tempPath, path);
	strcat(tempPath, "\\*.*");
	// проверяем пустой ли каталог
	bool isEmptyDir = emptyDir(path);
	if (isEmptyDir) { // если пустой удаляем его
		_rmdir(path);
	} 
	else { // смотрим есть ли каталоги в дирректории
		_finddata_t *file = new _finddata_t;
		long result = _findfirst(tempPath, file);
		long next = result;
		while (next != -1) {
			if (strcmp(file->name, ".") && strcmp(file->name, "..")) {
				strcpy(fileNameSource, path);
				strcat(fileNameSource, "\\");
				strcat(fileNameSource, file->name);
				if (file->attrib&_A_SUBDIR) {// если дирректория входим еще раз
					clearEmptyDir(fileNameSource);
				}
			}
			next = _findnext(result, file);
		}
		delete[]fileNameSource;
		delete[]tempPath;
		_findclose(result);
		delete file;
		isEmptyDir = emptyDir(path); // проверяем еще раз
		if (isEmptyDir) { // если пустой удаляем его
			_rmdir(path);
		}
	}
}

int copyDir(char *source, char *destination, bool &rewriteAll) {
	char *tempPathSource = new char[_MAX_PATH];
	strcpy(tempPathSource, source);
	strcat(tempPathSource, "\\*.*");
	char *fileNameSource = new char[_MAX_PATH];
	char *fileNameDestination = new char[_MAX_PATH];
	int res = 0;
	_finddata_t *fileSource = new _finddata_t;
	long result = _findfirst(tempPathSource, fileSource);
	if (result == -1)
		return res;
	bool resCopy = false; // флаг результат копирования
	int menu = 0; // 1. Перезаписать? 2. Пропустить? 3. Перезаписывать для всех? 4. Отмена? 

	long next = result;
	while (next != -1) {
		if (strcmp(fileSource->name, ".") && strcmp(fileSource->name, "..")) {
			strcpy(fileNameSource, source);
			strcat(fileNameSource, "\\");
			strcat(fileNameSource, fileSource->name);
			strcpy(fileNameDestination, destination);
			strcat(fileNameDestination, "\\");
			strcat(fileNameDestination, fileSource->name);
			if (fileSource->attrib&_A_SUBDIR) { // входим еще раз
				if (!checkDir(fileNameDestination)) {
					// пытаемся создать
					if (_mkdir(fileNameDestination)) {
						cout << "Не верно задан путь назначения " << fileNameDestination << endl;
						return errorCopy;
					}
				}
				res = copyDir(fileNameSource, fileNameDestination, rewriteAll);
			}
			else { // это файл, копируем его
				// для начало проверим существует ли в destination уже такой файл
				if (!rewriteAll && existsFile(destination, fileSource->name)) {
					// если существует 
					menu = defineOperation(fileNameDestination);
					switch (menu) {
					case 1: // 1. Перезаписать
						break;
					case 2: // 2. Пропустить?
						next = _findnext(result, fileSource);
						continue;
						break;
					case 3: // Перезаписывать для всех
						rewriteAll = true;
						break;
					case 4: // 4. Отмена? 
						return cancellation;
						break;
					}
				}
				resCopy = copyFile(source, destination, fileSource->name);
				if (!resCopy) {
					res = errorCopy;
				}
				else {
					// удаляем файл после перезаписывания
					res = remove(fileNameSource);
				}
			}
		}
		next = _findnext(result, fileSource);
	}
	delete[]fileNameDestination;
	delete[]fileNameSource;
	delete[]tempPathSource;
	_findclose(result);
	delete fileSource;

	return res;
}

bool existsFile(char *path, char *fileName) {
	bool ret = false;
	char *tmpfileName = new char[_MAX_PATH];
	strcpy(tmpfileName, path);
	strcat(tmpfileName, "\\");
	strcat(tmpfileName, fileName);
	_finddata_t *fileinfo = new _finddata_t;
	long result = _findfirst(tmpfileName, fileinfo);
	if (result != -1) {
		ret = true;
	}
	_findclose(result);
	delete fileinfo;
	delete[]tmpfileName;

	return ret;
}

// копируем файл с одного места во второе 
// функция возвращает true в случае успешного копирования
bool copyFile(char *source, char *destination, char *fileName) {
	FILE *fpSource, *fpDestination;
	char *tempFileSource = new char[_MAX_PATH];
	strcpy(tempFileSource, source);
	strcat(tempFileSource, "\\");
	strcat(tempFileSource, fileName);
	if (!(fpSource = fopen(tempFileSource, "rb")))
	{
		return false;
	}
	char *tempFileDestination = new char[_MAX_PATH];
	strcpy(tempFileDestination, destination);
	strcat(tempFileDestination, "\\");
	strcat(tempFileDestination, fileName);
	if (!(fpDestination = fopen(tempFileDestination, "wb")))
	{
		return false;
	}
	// непосредственно копируем
	size_t bytes;
	signed BUFFSIZE = 1024;
	signed *temp = new signed[BUFFSIZE];
	while ((bytes = fread(temp, sizeof(char), BUFFSIZE, fpSource)) > 0) {
		if (!fwrite(temp, sizeof(char), bytes, fpDestination)) {
			return false;
		}
	}
	delete[]temp;
	delete[]tempFileSource;
	delete[]tempFileDestination;
	if (fpDestination)
		fclose(fpDestination);
	if (fpSource)
		fclose(fpSource);

	return true;
}

// Каталог пустой???
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

// Это каталог???
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

int defineOperation(char *file) {
	int res;
	cout << file << " существует" << endl;
	cout << "Выбирите действие" << endl;
	cout << "1. Перезаписать" << endl;
	cout << "2. Пропустить" << endl;
	cout << "3. Перезаписывать для всех" << endl;
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
