

#include <iostream>
#include<fstream>
#include<cstdio>
#include<cstdlib>
#include<conio.h>
#define INF 0x3F3F3F3F
#define MAX 110
using namespace std;
void floyd (int** arr, int rows, int cols)
{
	for (int k = 0; k < rows; k++)

		for ( int i = 0; i < rows; i++)

			for (int j = 0; j < cols; j++)

				if (arr[i][k] + arr[k][j] < arr[i][j])

					arr[i][j] = arr[i][k] + arr[k][j];
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
	for (int i = 0; i < rows; i++)
	{
		delete[] arr[i];
	}
	delete[] arr;
}
