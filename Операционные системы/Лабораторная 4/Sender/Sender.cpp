#include<iostream>
#include<fstream>
#include<string>
#include<Windows.h>
#include"../Reciever/message.h"

using namespace std;

int main(int argc, char* argv[]) {
	HANDLE ready = OpenEvent(EVENT_MODIFY_STATE, FALSE, (to_wstring(atoi(argv[3])) + L"ready").c_str());
	HANDLE mutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, L"mutex");
	HANDLE write_sem = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, L"write_sem");
	HANDLE read_sem = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, L"read_sem");
	if (!ready || !read_sem || !write_sem || !mutex) {
		cout << "Error" << "\n";
		return -1;
	}
	SetEvent(ready);
	fstream file;
	int action;
	while (true) {
		cout << "1 to write message" << "\n";
		cout << "0 to exit" << "\n";
		cin >> action;
		if (action != 0 && action != 1) {
			cout << "Unknown command" << "\n";
			continue;
		}
		if (action == 0) {
			break;
		}
		cin.ignore();
		string text;
		cout << "Enter message text:";
		getline(cin, text);
		WaitForSingleObject(write_sem, INFINITE);
		WaitForSingleObject(mutex, INFINITE);
		message mes(text);
		file.open(argv[1], ios::binary | ios::app);
		file << mes;
		file.close();
		ReleaseMutex(mutex);
		ReleaseSemaphore(read_sem, 1, NULL);
		cout << "Written succesfully"<<"\n";
	}

	CloseHandle(mutex);
	CloseHandle(ready);
	CloseHandle(write_sem);
	CloseHandle(read_sem);
	return 0;
}