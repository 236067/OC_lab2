#include <windows.h>
#include <iostream>
using namespace std;

struct params {
	int n;
	int min = INT_MAX;
	int max = INT_MIN;
	double aver;
	int* arr;
};

DWORD WINAPI min_max(LPVOID arr)
{
	params* p = (params*)arr;

	for (int i = 0; i < p->n; i++) {
		if (p->arr[i] < p->min) {
			p->min = p->arr[i];
		}
		Sleep(7);
		if (p->arr[i] > p->max) {
			p->max = p->arr[i];
		}
		Sleep(7);
	}
	cout << "min element in array is :" << p->min << '\n';
	cout << "max element in array is :" << p->max << '\n';
	return 0;
}

DWORD WINAPI average(LPVOID arr)
{
	params* p = (params*)arr;
	double sum = 0;
	for (int i = 0; i < p->n; i++) {
		sum += p->arr[i];
		Sleep(12);
	}
	p->aver = sum / (p->n);
	cout << "average of array is :" << p->aver << endl;
	return 0;
}

int main()
{
	HANDLE hThread1;
	HANDLE hThread2;
	int n;
	cin >> n;
	int* arr = new int[n];
	for (int i = 0; i < n; i++)
		cin >> arr[i];

	params p;
	p.n = n;
	p.arr = arr;
	hThread1 = CreateThread(NULL, 0, min_max, &p, 0, NULL);
	hThread2 = CreateThread(NULL, 0, average, &p, 0, NULL);
	WaitForSingleObject(hThread1, INFINITE);
	WaitForSingleObject(hThread2, INFINITE);
	for (int i = 0; i < n; i++)
	{
		if (arr[i] == p.max) arr[i] = p.aver;
		if (arr[i] == p.min) arr[i] = p.aver;
		cout << arr[i] << endl;

	}

	delete[] arr;
	CloseHandle(hThread1);
	CloseHandle(hThread2);
	return 0;
}
