

#include <iostream>
#include<fstream>
#include<cstdio>
#include<cstdlib>
#include<conio.h>
#define INF 0x3F3F3F3F
#define MAX 110
using namespace std;
void merge(int merged[], int lenD, int L[], int lenL, int R[], int lenR);
void floyd (int** arr, int rows, int cols)
{
	for (int k = 0; k < rows; k++)

		for ( int i = 0; i < rows; i++)

			for (int j = 0; j < cols; j++)

				if (arr[i][k] + arr[k][j] < arr[i][j])

					arr[i][j] = arr[i][k] + arr[k][j];
}
void ShellSort(int* mass, int n)
{
	int i, j, step;
	int tmp;
	for (step = n / 2; step > 0; step /= 2)
		for (i = step; i < n; i++)
		{
			tmp = mass[i];
			for (j = i; j >= step; j -= step)
			{
				if (tmp < mass[j - step])
					mass[j] = mass[j - step];
				else
					break;
			}
			mass[j] = tmp;
		}
	cout << endl;
	cout << "Shell sort" << endl;
	for (int i = 0; i < n; i++) {
		cout << mass[i] << " ";
	}
}
void swapEl(int* arr, int i)
{
	int buff;
	buff = arr[i];
	arr[i] = arr[i - 1];
	arr[i - 1] = buff;
}
void ShakerSort(int* arr, int size)
{
	int leftMark = 1;
	int rightMark = size - 1;
	while (leftMark <= rightMark)
	{
		for (int i = rightMark; i >= leftMark; i--)
			if (arr[i - 1] > arr[i]) swapEl(arr, i);
		leftMark++;


		for (int i = leftMark; i <= rightMark; i++)
			if (arr[i - 1] > arr[i]) swapEl(arr, i);
		rightMark--;

		//cout << "\nИтерация: " << leftMark - 1; // просмотр количества итераций
	}
	cout << endl;
	cout << "Shaker sort" << endl;
	for (int i = 0; i < size; i++) {
		cout << arr[i] << " ";
	}
}
void mergeSort(int* data, int lenD)
{

	if (lenD > 1) {
		int middle = lenD / 2;
		int rem = lenD - middle;
		int* L = new int[middle];
		int* R = new int[rem];
		for (int i = 0;i < lenD;i++) {
			if (i < middle) {
				L[i] = data[i];
			}
			else {
				R[i - middle] = data[i];
			}
		}
		mergeSort(L, middle);
		mergeSort(R, rem);
		merge(data, lenD, L, middle, R, rem);
	}
	cout << endl;
	cout << "Merge sort" << endl;
	for (int i = 0; i < lenD; i++) {
		cout << data[i] << " ";
	}

}

void merge(int merged[], int lenD, int L[], int lenL, int R[], int lenR) {
	int i = 0;
	int j = 0;
	while (i < lenL || j < lenR) {
		if (i < lenL & j < lenR) {
			if (L[i] <= R[j]) {
				merged[i + j] = L[i];
				i++;
			}
			else {
				merged[i + j] = R[j];
				j++;
			}
		}
		else if (i < lenL) {
			merged[i + j] = L[i];
			i++;
		}
		else if (j < lenR) {
			merged[i + j] = R[j];
			j++;
		}
	}

}
void quickSort(int* data, int rows)
{
	int const lenD = rows;
	int pivot = 0;
	int ind = lenD / 2;
	int i, j = 0, k = 0;
	
	
	if (lenD > 1) {
		int* L = new int[lenD];
		int* R = new int[lenD];
		pivot = data[ind];
		for (i = 0;i < lenD;i++) {
			if (i != ind) {
				if (data[i] < pivot) {
					L[j] = data[i];
					j++;
				}
				else {
					R[k] = data[i];
					k++;
				}
			}
		}
		quickSort(L, j);
		quickSort(R, k);
		for (int cnt = 0;cnt < lenD;cnt++) {
			if (cnt < j) {
				data[cnt] = L[cnt];;
			}
			else if (cnt == j) {
				data[cnt] = pivot;
			}
			else {
				data[cnt] = R[cnt - (j + 1)];
			}
		}
	}
	cout << endl;
	cout << "Quick Sort:" << endl;
	for (int i = 0; i < rows; i++) {
		cout << data[i] << " ";
	}
	//delete[] data;
}
void insertionSort(int* data, int rows) 
{
	int key = 0;
	int i = 0;
	

	for (int j = 1; j < rows; j++) {
		key = data[j];
		i = j - 1;
		while (i >= 0 && data[i] > key) {
			data[i + 1] = data[i];
			i = i - 1;
			data[i + 1] = key;
		}
	}
	cout << endl;
	cout << "Insertion Sort:" << endl;
	for (int i = 0; i < rows; i++) {
		cout << data[i] << " ";
	}
	//delete[] data;
}
void bubble_sort(int* arr, int rows)
{
	int tmp = 0;
	for (int i = 0; i < rows; i++) { // bubble sort
		for (int j = (rows - 1); j >= (i + 1); j--) 
		{
			if (arr[j] < arr[j - 1]) {
				tmp = arr[j];
				arr[j] = arr[j - 1];
				arr[j - 1] = tmp;
				

			}
		}
		
	}
	cout << endl;
	cout << "(Bubble) Sorted array:" << endl;
	for (int i = 0; i < rows; i++) {
		cout << arr[i]  << " ";
	}
	//delete[] arr;
}
void main()
{
	
	int rows;
	int cols;
	cout << "Enter the size of rows:" << endl;
	cin >> rows;
	cout << "Enter the size of cols:" << endl;
	cin >> cols;
	int** arr = new int* [rows];
	for (int i = 0; i < rows; i++)
	{
		arr[i] = new int[cols];
	}
	ofstream fout;
	fout.open("input1.txt");
	if (!fout.is_open())
	{
		cout << "Error" << endl;
	}
	else
	{
		
		cout << "Let's set an adjacency matrix:" << endl;
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				cin >> arr[i][j];
			}
			cout << endl;
		}
		
	}
	fout.close();
	ifstream inp_file("input1.txt");

	if (!inp_file.is_open())
	{
		cout << "Error" << endl;
		//_getch(); 
		//exit(1);
	}
	else
	{
		for (int i = 0;i < rows;i++)
			for (int j = 0;j < cols;j++)
				inp_file >> arr[i][j];
	}

	inp_file.close();
	cout << "Adjacency Matrix:" << endl;
	for (int i = 0;i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}

	
	//scanf("%d", &n);

	for (int i = 0; i < rows; i++)

		for (int j = 0; j < cols; j++)

		{

			//scanf_s("%d", &g[i][j]);

			if (arr[i][j] < 0) arr[i][j] = INF;

		}
	floyd (arr,rows,cols);
	int diam = 0; int  radius = INF;

	for (int i = 0; i < rows; i++)

	{

		int max = 0;

		for (int j = 0; j < cols; j++)

			if (arr[i][j] > max) max = arr[i][j];

		if (max > diam) diam = max;

		if (max < radius) radius = max;

	}
	cout << endl;
	cout << "Diameter:" << diam << endl;
	cout << "Radius:" << radius << endl;
	cout << endl;
	/////////////////////////////////////////
	int* data = new int[rows];
	for (int i = 0; i < rows; i++) {
		data[i] = 0;
		for (int j = 0; j < cols; j++) {
			data[i] += arr[i][j];
		}
		//cout << "Summa " << i + 1 << " vershiny:" << data[i] << endl;
	}
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {

			cout << arr[i][j] << " ";
		}
		cout << endl;
		cout << i + 1 << " vershina" << endl;
	}
	bubble_sort(data, rows);
	cout << endl;
	insertionSort(data, rows);
	cout << endl;
	quickSort(data, rows);
	cout << endl;
	mergeSort(data, rows);
	cout << endl;
	ShakerSort(data, rows);
	cout << endl;
	ShellSort(data, rows);
	delete[] data;
}
