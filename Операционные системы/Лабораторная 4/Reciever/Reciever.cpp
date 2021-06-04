#include<iostream>
#include<fstream>
#include<string>
#include<Windows.h>
#include"message.h"
#include<vector>

using namespace std;

HANDLE start_process(wstring command_line) {
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);

	if (!CreateProcess(NULL, (LPWSTR)command_line.c_str(), NULL, NULL,
		FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi)) {
		return NULL;
	}

	CloseHandle(pi.hThread);
	return pi.hProcess;
}

int main() {
	wstring file_name;
	cout << "Enter file name:";
	wcin >> file_name;
	fstream file(file_name,ios::binary|ios::out);
	int number_of_records;
	cout << "Enter number of records:";
	cin >> number_of_records;
	if (!file.is_open()) {
		cout << "Error while creating file!";
		return 0;
	}
	file.close();

	int number_of_senders;
	cout << "Enter number of Senders:";
	cin >> number_of_senders;

	HANDLE* senders = new HANDLE[number_of_senders];
	HANDLE* events = new HANDLE[number_of_senders];



	HANDLE mutex = CreateMutex(NULL, FALSE, L"mutex");
	HANDLE write_sem = CreateSemaphore(NULL, number_of_records, number_of_records, L"write_sem");
	HANDLE read_sem = CreateSemaphore(NULL, 0, number_of_records, L"read_sem");
	if (!mutex || !write_sem || !read_sem){
		cout << "Error";
		return -1;
	}

	for (int i = 0; i < number_of_senders; ++i) {
		wstring command_line = L"Sender.exe " + file_name + L" " + to_wstring(number_of_records) + L" " + to_wstring(i);

		HANDLE event = CreateEvent(NULL, FALSE, FALSE, (to_wstring(i) + L"ready").c_str());
		events[i] = event;
		senders[i] = start_process(command_line);
		if (senders[i] == NULL) {
			cout << "Error while creating process";
			return -1;
		}
	}

	WaitForMultipleObjects(number_of_senders, events, TRUE, INFINITE);

	int action = 1;

	while (true) {
		cout << "1 to read message" << "\n";
		cout << "0 to exit" << "\n";
		cin >> action;
		if (action != 0 && action != 1) {
			cout << "Unknown command";
			continue;
		}
		if (action == 0) {
			break;
		}
		WaitForSingleObject(read_sem, INFINITE);
		WaitForSingleObject(mutex, INFINITE);
		file.open(file_name, ios::binary | ios::in);
		message mes;
		file >> mes;
		cout << "new message:" << mes.get_text() << "\n";
		vector<message> file_text;
		while (file>>mes) {
			file_text.push_back(mes);
		}
		file.close();
		file.open(file_name, ios::binary | ios::out);
		for (int i = 0; i < file_text.size(); ++i) {
			file << file_text[i];
		}
		file.close();
		ReleaseMutex(mutex);
		ReleaseSemaphore(write_sem, 1, NULL);

	}

	for (int i = 0; i < number_of_senders; ++i) {
		CloseHandle(events[i]);
		CloseHandle(senders[i]);
	}

	delete[] events;
	delete[] senders;
	CloseHandle(mutex);
	CloseHandle(read_sem);
	CloseHandle(write_sem);
	return 0;
}