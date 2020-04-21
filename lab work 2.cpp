// lab work 2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <cmath>
using namespace std;
struct Node {
	Node* next;
	Node* prev;
	int coef;
	int power;
};
Node* first(int d, int f);
void add(Node* pend, int d, int f);
void polynomial();
int main()
{
	polynomial();
	return 0;
	
}
Node* first(int d, int f)
{
	Node* pv = new Node;
	pv->coef = d;
	pv->power = f;
	pv->next = 0;
	pv->prev = 0;
	return pv;
}
void add(Node** pend, int d, int f)
{
	Node* pv = new Node;
	Node num1;
	cout << "Enter another term:" << endl;
	cout << "------------------------------" << endl;
	cout << " Enter another coefficient:" << endl;
	cin >> d;
	cout << "Enter another degree" << endl;
	cin >> f;
	pv->coef = d;
	pv->power = f;
	pv->next = 0;
	pv->prev = *pend;
	(*pend)->next = pv;
	*pend = pv;

}

void print(Node* pv)
{
	while (pv) {
		if (pv->coef > 0) {
			cout << "+" << pv->coef << "*x^" << pv->power;
		}
		else
			cout << pv->coef << "*x^" << pv->power;

		pv = pv->next;
	}
	cout << "\n";
}

void remainder (int COUNT, int y)
{
	int rem = COUNT % y;
	cout << "Remainder:" << rem << endl;
}

int count(Node* pv, int x)
{
	int COUNT = 0;
	while (pv)
	{
		int x_power = x;
		x_power = pow(x_power, pv->power);
		x_power *= pv->coef;

		COUNT += x_power;
		pv = pv->next;
	}
	return COUNT;
}

void polynomial()
{
	Node num;
	bool tr = 1;
	int a;
	cout << "Let's code our polynomial" << endl;
	cout << "-----------------------------" << endl;
	cout << "Enter the coefficient:" << endl;
	cin >> num.coef;
	cout << "\n";

	cout << "Enter the degree:" << endl;
	cin >> num.power;
	cout << "\n";
	Node* pbeg = first(num.coef, num.power);
	Node* pend = pbeg;
	//Node* pv = pbeg;
	while (tr) 
	{
		cout << "Would you like to add another term? " << endl << "-------[1 = Yes]- -  -  -  -[2 = No]-------" << endl;
		cin  >> a;
		if (a == 2) break; 
		
		else  {
			
			add(&pend, num.coef, num.power);

		}
		
	}
	cout << "Polynomial \t" << endl;

	print(pbeg);


	cout << "Let's set the value of X" << endl;
	int x;
	cin >> x;
	cout << "Polynomial with " << x << " value " << endl;
	int COUNT = count(pbeg,x);
	cout << COUNT;
	cout << "\n";
	cout << "Find the remainder of the division:" << endl;
	int y;
	cin >> y;
	remainder(COUNT, y);

	/*cout << "Final polynomial" << endl;
	while (pv) {
		cout << "-------------------------------" << endl;

		if (pv->coef > 0) {
			cout << "+" << pow(pv->coef * x, pv->power);
		}
		else
			cout << pow(pv->coef * x,pv->power);

		pv = pv->next;
	
	}*/
}



// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
