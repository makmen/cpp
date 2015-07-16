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

const int cancellation = 1; // "�������� �������� �������������"
const int successfully = 0; // "����������� �������"

int main(int argc, char *argv[]) {
	setlocale(LC_CTYPE, "Russian");
	cout << "��������� ��� �������� ��������� (��������� ��� ��������� ����� � �����)." << endl;
	if (argc < 2) {
		// ��������� �������� ������ ������ ���������
		// ����������� ��������� ����������� 
		cout << "��� ������� ��������� ���������� �������� ��������" << endl;
		return 0;
	}
	// �������� � �������� ������ ����� ��������� � ���� ����������
	char source[_MAX_PATH];
	strcpy(source, argv[1]);
	int flag = false;
	// �������� �������� �� ��������� ������� ������������
	flag = checkDir(source);
	if (!flag) {
		cout << "�� ����� ����� ���� ��������� " << source << endl;
		return 0;
	}
	bool readOnly = true;
	int res = clearDir(source, readOnly);
	switch (res) {
		case cancellation:
			cout << "�������� ������� �������������." << endl;
			break;
		case successfully:
			cout << "��������� �������." << endl;
			cout << source << " ������" << endl;
			break;
		default:
			cout << "���� ������" << endl;
	}

	return 0;
}

/*
������ ����������� �� ����� �������
path - ���� � �����������
readOnly = true ��������� ������� readOnly, false - ������� ��� ��������
*/
int clearDir(char *path, bool &readOnly) {
	char *tempPath = new char[_MAX_PATH];
	strcpy(tempPath, path);
	strcat(tempPath, "\\*.*");
	char *fileName = new char[_MAX_PATH];
	int res = 0;
	int menu = 0; // 1. �������? 2. ����������? 3.������� ��� ����? 4. ������? 
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
			if (readOnly && _access(fileName, 2)) { // ���� ���������� ������� Read only � ���� ��������� readOnly
				menu = defineOperation(fileName);
				switch (menu) {
				case 1: // 1. �������? ������ �� ������
					break;
				case 2: // 2. ����������?
					next = _findnext(result, file);
					continue;
					break;
				case 3: // 3.������� ��� ����? 4. ������? 
					readOnly = false;
					break;
				case 4: // 4. ������? 
					return cancellation;
					break;
				}
			} 
			if (file->attrib&_A_SUBDIR) {// ������ ��� ���
				res = clearDir(fileName, readOnly);
				if (res == cancellation) {
					return cancellation;
				}
			}
			else { // ��� ����, ��� �������
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

			return false;	// ��� �� ������

		}
		next = _findnext(result, fileinfo);
	}
	delete[]tempPath;
	_findclose(result);
	delete fileinfo;

	return true; // �� ������
}

int defineOperation(char *file) {
	int res;
	cout << file << " ����� ������� Read only" << endl;
	cout << "�������� ��������" << endl;
	cout << "1. �������" << endl;
	cout << "2. ����������" << endl;
	cout << "3. ������� ��� ����" << endl;
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

