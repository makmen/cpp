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

const int successfully = 0;		// "����������� �������"
const int cancellation = 1;		// "�������� �������� �������������"
const int errorCopy = -1;		// "������ �����������"

int main(int argc, char *argv[]) {
	setlocale(LC_CTYPE, "Russian");
	if (argc < 3) {
		// ��������� �������� ������ ���� ����������, ����������� ��������� ����������� 
		cout << "��� ������� ��������� ���������� �������� ��� ���������" << endl;
		return 0;
	}
	// �������� � �������� ������ ����� ��������� � ���� ����������
	char source[_MAX_PATH];
	strcpy(source, argv[1]);
	bool flag = false;
	// �������� �������� �� ��������� ������� ������������
	flag = checkDir(source);
	if (!flag) {
		cout << "�� ����� ����� ���� ��������� " << source << endl;
		return 0;
	}
	char destination[_MAX_PATH];
	strcpy(destination, argv[2]);

	flag = checkDir(destination);
	if (!flag) {
		// �������� �������
		if (_mkdir(destination)) {
			cout << "�� ����� ����� ���� ���������� " << destination << endl;
			return 0;
		}
	}
	bool rewriteAll = false;
	int res = copyDir(source, destination, rewriteAll);
	bool readOnly = false;
	switch (res) {
	case cancellation:
		cout << "�������� ������� �������������." << endl;
		break;
	case successfully:
		// ������ ��� ����� ���� ����
		clearEmptyDir(source);
		_mkdir(source);
		cout << "��������� �������." << endl;
		cout << source << " ���������� � " << destination << endl;
		break;
	default:
		cout << "���� ������" << endl;
	}

	return 0;
}

void clearEmptyDir(char *path) {
	char *tempPath = new char[_MAX_PATH];
	char *fileNameSource = new char[_MAX_PATH];
	strcpy(tempPath, path);
	strcat(tempPath, "\\*.*");
	// ��������� ������ �� �������
	bool isEmptyDir = emptyDir(path);
	if (isEmptyDir) { // ���� ������ ������� ���
		_rmdir(path);
	} 
	else { // ������� ���� �� �������� � �����������
		_finddata_t *file = new _finddata_t;
		long result = _findfirst(tempPath, file);
		long next = result;
		while (next != -1) {
			if (strcmp(file->name, ".") && strcmp(file->name, "..")) {
				strcpy(fileNameSource, path);
				strcat(fileNameSource, "\\");
				strcat(fileNameSource, file->name);
				if (file->attrib&_A_SUBDIR) {// ���� ����������� ������ ��� ���
					clearEmptyDir(fileNameSource);
				}
			}
			next = _findnext(result, file);
		}
		delete[]fileNameSource;
		delete[]tempPath;
		_findclose(result);
		delete file;
		isEmptyDir = emptyDir(path); // ��������� ��� ���
		if (isEmptyDir) { // ���� ������ ������� ���
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
	bool resCopy = false; // ���� ��������� �����������
	int menu = 0; // 1. ������������? 2. ����������? 3. �������������� ��� ����? 4. ������? 

	long next = result;
	while (next != -1) {
		if (strcmp(fileSource->name, ".") && strcmp(fileSource->name, "..")) {
			strcpy(fileNameSource, source);
			strcat(fileNameSource, "\\");
			strcat(fileNameSource, fileSource->name);
			strcpy(fileNameDestination, destination);
			strcat(fileNameDestination, "\\");
			strcat(fileNameDestination, fileSource->name);
			if (fileSource->attrib&_A_SUBDIR) { // ������ ��� ���
				if (!checkDir(fileNameDestination)) {
					// �������� �������
					if (_mkdir(fileNameDestination)) {
						cout << "�� ����� ����� ���� ���������� " << fileNameDestination << endl;
						return errorCopy;
					}
				}
				res = copyDir(fileNameSource, fileNameDestination, rewriteAll);
			}
			else { // ��� ����, �������� ���
				// ��� ������ �������� ���������� �� � destination ��� ����� ����
				if (!rewriteAll && existsFile(destination, fileSource->name)) {
					// ���� ���������� 
					menu = defineOperation(fileNameDestination);
					switch (menu) {
					case 1: // 1. ������������
						break;
					case 2: // 2. ����������?
						next = _findnext(result, fileSource);
						continue;
						break;
					case 3: // �������������� ��� ����
						rewriteAll = true;
						break;
					case 4: // 4. ������? 
						return cancellation;
						break;
					}
				}
				resCopy = copyFile(source, destination, fileSource->name);
				if (!resCopy) {
					res = errorCopy;
				}
				else {
					// ������� ���� ����� ���������������
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

// �������� ���� � ������ ����� �� ������ 
// ������� ���������� true � ������ ��������� �����������
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
	// ��������������� ��������
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

// ������� ������???
bool emptyDir(char *path) {
	_finddata_t *fileinfo = new _finddata_t;
	char *tempPath = new char[_MAX_PATH];
	strcpy(tempPath, path);
	strcat(tempPath, "\\*.*");
	long result = _findfirst(tempPath, fileinfo);
	long next = result;
	while (next != -1) {
		if (strcmp(fileinfo->name, ".") && strcmp(fileinfo->name, "..")) {

			return false;	// ��� �� ������

		}
		next = _findnext(result, fileinfo);
	}
	delete[]tempPath;
	_findclose(result);
	delete fileinfo;

	return true; // �� ������
}

// ��� �������???
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
	cout << file << " ����������" << endl;
	cout << "�������� ��������" << endl;
	cout << "1. ������������" << endl;
	cout << "2. ����������" << endl;
	cout << "3. �������������� ��� ����" << endl;
	cout << "4. ������" << endl;
	while (true) {
		cin >> res;
		if (cin.good()) {
			if (res >= 1 && res < 5) {
				break;
			}
		}
		cout << "�������� ��������. ������� 1, 2, 3 ��� 4" << endl;
		cin.clear();
		_flushall();
	}

	return res;
}
