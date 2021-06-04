#include <iostream>
#include <Windows.h>

using namespace std;

struct thread_info {
	int array_size;
	int* arr;
	int thread_index;
	HANDLE stop_work;//Event
	HANDLE start_work;//Event
	HANDLE* terminate_or_continue;//Events [0] - terminate, [1] - continue
};

CRITICAL_SECTION cs;

void set_zeros(int* arr, int size, int thread_index) {
	for (int i = 0; i < size; ++i) {
		if (arr[i] == thread_index) { arr[i] = 0; }
	}
}

bool need_to_terminate(HANDLE* terminate_or_continue) {
	return WaitForSingleObject(terminate_or_continue[0], 0) == WAIT_OBJECT_0;
}

void continue_thread(HANDLE* terminate_or_continue) {
	ResetEvent(terminate_or_continue[1]);
}

DWORD WINAPI thread_func(LPVOID params) {
	thread_info info = *((thread_info*)params);
	bool end_thread = false;
	int number_of_marked_elements = 0;
	srand(info.thread_index);

	WaitForSingleObject(info.start_work, INFINITE);

	while (!end_thread) {
		int ind = rand() % info.array_size;
		EnterCriticalSection(&cs);
		if (info.arr[ind] == 0) {
			Sleep(5);
			info.arr[ind] = info.thread_index;
			LeaveCriticalSection(&cs);
			number_of_marked_elements++;
			Sleep(5);
		}
		else {
			cout << "\nThread " << info.thread_index << ", number of marked elements: " << number_of_marked_elements << ", can't mark element with index " << ind;
			LeaveCriticalSection(&cs);
			SetEvent(info.stop_work);
			//waiting for main response
			int k = WaitForMultipleObjects(2, info.terminate_or_continue, FALSE, INFINITE) - WAIT_OBJECT_0;
			if (k== 0) {
				end_thread = true;
			}
		}
	}
	set_zeros(info.arr, info.array_size, info.thread_index);
	return 0;
}

void print_array(int* arr, int size) {
	cout << "Array: ";
	for (int i = 0; i < size; ++i) {
		cout << arr[i] << " ";
	}
	cout << "\n";
}

bool all_threads_terminated(bool* terminated_threads, int size) {
	for (int i = 0; i < size; ++i) {
		if (terminated_threads[i] == false) {
			return false;
		}
	}
	return true;
}

int main() {
	InitializeCriticalSection(&cs);

	int size;
	cout << "Enter array size: ";
	cin >> size;
	int* arr = new int[size];
	for (int i = 0; i < size; ++i) {
		arr[i] = 0;
	}
	cout << "Enter number marker of threads: ";
	int number_of_threads;
	cin >> number_of_threads;

	HANDLE* threads = new HANDLE[number_of_threads];
	thread_info* information = new thread_info[number_of_threads];
	bool* terminated_threads = new bool[number_of_threads];
	HANDLE start_work = CreateEvent(NULL, TRUE, FALSE, NULL);
	HANDLE* stopped_threads = new HANDLE[number_of_threads];

	for (int i = 0; i < number_of_threads; ++i) {
		information[i].arr = arr;
		information[i].array_size = size;
		information[i].thread_index = i + 1;
		information[i].start_work = start_work;
		stopped_threads[i] = information[i].stop_work = CreateEvent(NULL, TRUE, FALSE, NULL);
		information[i].terminate_or_continue = new HANDLE[2];
		information[i].terminate_or_continue[0] = CreateEvent(NULL, FALSE, FALSE, NULL);
		information[i].terminate_or_continue[1] = CreateEvent(NULL, FALSE, FALSE, NULL);
		threads[i] = CreateThread(NULL, 0, thread_func, (LPVOID)(&information[i]), NULL, NULL);
		terminated_threads[i] = false;
	}

	SetEvent(start_work);

	int ended_threads = 0;

	while (ended_threads != number_of_threads) {
		WaitForMultipleObjects(number_of_threads, stopped_threads, TRUE, INFINITE);
		cout << "\n";
		print_array(arr, size);
		bool is_thread_terminated = false; //checks if we had stopped thread at this iteration
		while (!is_thread_terminated) {
			int thread_to_terminate_ind;
			cout << "Enter index of thread to be terminated(starts with 1): ";
			cin >> thread_to_terminate_ind;
			thread_to_terminate_ind--;
			if (thread_to_terminate_ind >= number_of_threads || thread_to_terminate_ind < 0) {
				cout << "No thread with such index\n";
				continue;
			}
			if (terminated_threads[thread_to_terminate_ind]) {
				cout << "Thread is already terminated\n";
			}
			else {
				SetEvent(information[thread_to_terminate_ind].terminate_or_continue[0]);
				WaitForSingleObject(threads[thread_to_terminate_ind], INFINITE);
				print_array(arr, size);
				terminated_threads[thread_to_terminate_ind] = true;
				is_thread_terminated = true;
				ended_threads++;
			}
		}

		for (int j = 0; j < number_of_threads; ++j) {
			if (!terminated_threads[j]) {
				ResetEvent(information[j].stop_work);
				SetEvent(information[j].terminate_or_continue[1]);
			}
		}

	}

	cout << "All threads are terminated\n";

	CloseHandle(start_work);
	for (int i = 0; i < number_of_threads; ++i) {
		CloseHandle(threads[i]);
		CloseHandle(stopped_threads[i]);
		CloseHandle(information[i].terminate_or_continue[0]);
		CloseHandle(information[i].terminate_or_continue[1]);
	}
	delete[] threads;
	delete[] stopped_threads;
	for (int i = 0; i < number_of_threads; ++i) {
		delete[] information[i].terminate_or_continue;
	}
	delete[] information;
	delete[] terminated_threads;
	delete[] arr;

	DeleteCriticalSection(&cs);

	return 0;
}