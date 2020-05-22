#include<iostream>
#include<conio.h>
#include<iomanip>
#include<stdio.h>
#include<stdlib.h>
#include<fstream>
using namespace std;

void  clear1(int** arr, int rows)
{
	for (int i = 0; i < rows; i++)
	{
		delete[] arr[i];
	}
	delete[] arr;

}
void compress(ofstream &fout, ifstream &inp_file) // зжимання текстового файлу за алгоритмом RLE
{
	printf("Compressing...\n");
	inp_file.open("input1.txt");
	fout.open("output.txt");
	char    ch;
	int     num(0);
	while (!inp_file.eof()) {
		ch = inp_file.get();
		num++;
		if (ch != inp_file.peek()) {
			num > 1 ? fout << (char)(num - 128) << ch : fout << ch;
			num = 0;
		}
		else if (num == 127) {
			fout << (char)(num - 128) << ch;
			num = 0;
		}
	}
	inp_file.close();
	fout.close();
	printf("Complete!\n");
}
void decompress(ofstream &fout, ifstream &inp_file) // декомпресування
{
	printf("Decompressing...\n");
	inp_file.open("output.txt");
	fout.open("output2.txt");
	char    ch;
	int     num(0);
	while (!inp_file.eof()) {
		ch = inp_file.get();
		if ((int)ch < 0) { num = (int)ch + 128; inp_file >> ch; for (int i(0); i < num; i++) if (inp_file.peek() != '\0') fout << ch; }
		else if (inp_file.peek() != '\0') fout << ch;
	}
	inp_file.close();
	fout.close();
	printf("Complete!\n");
}
void write_read(int **arr, int cols,int rows, ofstream &fout, ifstream &inp_file) // записуємо матрицю А в файл і зчитуємо з файлу + друкуємо
{
	//ofstream fout;
	fout.open("input1.txt");
	if (!fout.is_open())
	{
		cout << "Error" << endl;
	}
	else
	{

		cout << "Let's set a matrix:" << endl;
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				cin >> arr[i][j];
			}
			cout << endl;
		}

	}
	fout.close();
	//ifstream inp_file;
	inp_file.open("input1.txt");

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
	cout << "A Matrix:" << endl;
	for (int i = 0;i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
}
void index_value_repres(int** Arr, int colArB, int rowsA) // зв'язне стисле зберігання і індексне зберігання матриці А
{
	int num = 0;

	for (int i = 0; i < rowsA; i++) {
		for (int j = 0; j < colArB; j++) {
			if (Arr[i][j] != 0) { num++; }
		}
	}
	int** compactMatrix = new int* [3];
	for (int i = 0; i < 3; i++) {
		compactMatrix[i] = new int[num];
	}
	int k = 0;
	for (int i = 0; i < rowsA; i++)
		for(int j = 0; j < colArB; j++)
			if (Arr[i][j] != 0)
			{
				compactMatrix[0][k] = i;
				compactMatrix[1][k] = j;
				compactMatrix[2][k] = Arr[i][j];
				k++;
			}
	cout << "Representation of the matrix:" << endl;
	for (int i = 0; i < 3; i++) {
		if (i == 0) cout << " Row: " << endl;
		if (i == 1) cout << "Column:" << endl;
		if (i == 2) cout << "Value:" << endl;
		for (int j = 0; j < num; j++) 
			printf("%d ", compactMatrix[i][j]);

		printf("\n");
	}
	

}

void choose_your_hero(int** aArr, int colB, int rowsA, int colArB, int** bArr, int** cArr, int** dArr) // вибір матриці для побудови індексного та стислого зберігання
{
	char m;
	cout << "Choose a matrix to representate: " << endl;
	cin >> m;
	switch (m)
	{
	case 'A': index_value_repres(aArr, colArB, rowsA);
		break;
	case 'B': index_value_repres(bArr, colB, colArB);
		break;
	case 'C':index_value_repres(cArr, colB, colArB);
		break;
	case 'D': index_value_repres(dArr, colB, colArB);
		break;

	}
}

void multiply(int rowsA, int colB,int colArB, int**bArr, int** aArr, int** cArr)
{
	//cout << "Matrix C: " << endl;
	if (colArB > rowsA) {
		for (int i = 0; i < rowsA; i++) {
			for (int j = 0; j < colB; j++) {
				for (int k = 0; k < colB + 1; k++) {
					cArr[i][j] += (aArr[i][k] * bArr[k][j]);
					//cout << cArr[i][j] << " ";
				}
			}
		}
	} else 

		for (int i = 0; i < rowsA; i++) {
			for (int j = 0; j < colB; j++) {
				for (int k = 0; k < colArB; k++) {
					cArr[i][j] += (aArr[i][k] * bArr[k][j]);
					//cout << cArr[i][j] << " ";
				}
			}
		}



	cout << "(Multiplying)Matrix C: " << endl;

	for (int i = 0; i < rowsA; i++)

	{

		for (int j = 0; j < colB; j++)
		{
			cout << cArr[i][j] << " ";
		}
		cout << endl;

	}
	//clear1(cArr,rowsA);
	_getch();
}
void addition(int** aArr, int** bArr, int** dArr, int rowsA, int colB, int colArB)
{
	if ((colArB == rowsA) || (colArB == colB)) {
		for (int i = 0; i < rowsA; i++) {
			for (int j = 0; j < colB; j++) {
				dArr[i][j] += (aArr[i][j] + bArr[i][j]);
			}
		}
	}
	else cout << "Addition is not possible" << endl;
	cout << "(Addition)Matrix D: " << endl;

	for (int i = 0; i < rowsA; i++)

	{

		for (int j = 0; j < colB; j++)
		{
			cout << dArr[i][j] << " ";
		}
		cout << endl;

	}
	_getch();
}
int main()

{
	//char m;
	int op;
	ofstream fout("input1.txt");
	ifstream inp_file("input1.txt");
	int colArB, rowsA, colB,i, j;
cout << "Enter number of columns in matrix A and number of rows in matrix B: "; // Однакова кількість стовпчиків А і рядків В, щоб множення матриць відбувалось завжди. АвтоРсьКа заДумКа:)

	cin >> colArB;

	cout << "Enter number of rows in matrix A: ";

	cin >> rowsA;

	cout << "Enter number of columns in matrix B: ";

	cin >> colB;

	int** aArr = new int* [rowsA];

	for (i = 0; i < rowsA; i++)

		aArr[i] = new int[colArB];
	cout << "Let's set matrix A:" << endl;
	for (i = 0; i < rowsA; i++)

	{

		for (j = 0; j < colArB; j++)

		{

			

			cin >> aArr[i][j];

		}
		
	}

	cout << "Matrix A: " << endl;

	for (i = 0; i < rowsA; i++)

	{

		for (j = 0; j < colArB; j++)
		{
			cout << aArr[i][j] << " ";
		}
		cout << endl;

	}

	int** bArr = new int* [colArB];

	for (i = 0; i < colArB; i++)

		bArr[i] = new int[colB];
	cout << "Let's set matrix B:" << endl;

	for (i = 0; i < colArB; i++)

		{

		for (j = 0; j < colB; j++)

		{


		cin >> bArr[i][j];

		}

		}

	cout << "Matrix B: " << endl;

	for (i = 0; i < colArB; i++)

	{

		for (j = 0; j < colB; j++) {

			cout << bArr[i][j] << " ";
		}
		cout << endl;

	}

	int** cArr = new int* [rowsA];

	for (i = 0; i < rowsA; i++)

		cArr[i] = new int[colB];

	for (i = 0; i < rowsA; i++)
		for (j = 0; j < colB; j++)
           cArr[i][j] = 0;

	int** dArr = new int* [rowsA];

	for (i = 0; i < rowsA; i++)

		dArr[i] = new int[colB];

	for (i = 0; i < rowsA; i++)
		for (j = 0; j < colB; j++)
			dArr[i][j] = 0;

		

	multiply(rowsA, colB,colArB, bArr, aArr, cArr);
	addition(aArr, bArr, dArr, rowsA, colB, colArB);
	cout << endl;
	choose_your_hero(aArr, colB, rowsA, colArB, bArr, cArr, dArr);
	while (true) {

		printf("1 to compress\n2 to decompress\n");
		scanf_s("%d", &op);
		if (op == 1) compress(fout, inp_file);
		else decompress(fout, inp_file);
	}
	//index_value_repres(aArr, colArB, rowsA);
	clear1(aArr,rowsA);
	clear1(bArr, colArB);
	clear1(cArr, rowsA);
	clear1(dArr, rowsA);

	_getch();
	return 0;

}