#include <iostream>
#include <string>
#include <stdio.h>
#include <Windows.h>
#include <string>
#include <functional>
using namespace std;
void userfunc();
void adminfunc();

double bill = 0;

struct user
{
	int id;
	int role;
	char login[20];
	char password[20];
};
struct order
{
	//int id;
	//int number;
	char name[20];
	char type[20];
	double price;
	int quantity;
};
bool check(char* arr1, char* arr2, int n)
{
	for (int i = 0; i < n; i++)
		if (arr1[i] != arr2[i])
			return 0;
	return 1;
}
/*bool check_registration(user& customer)
{

	bool arr = 1;
	FILE* passw;
	fopen_s(&passw, "information", "a+b");
	fclose(passw);
	if (fopen_s(&passw, "information", "rb"))
	{
		cout << "Error";
		return 0;
	}
	else
	{
		user customer2;
		while (!feof(passw))
		{
			fread(&customer2, sizeof(user), 1, passw);
			if (check(customer2.login, customer.login, size(customer.login)) && check(customer2.password, customer.password, size(customer.password)))
			{
				fclose(passw);
				return 1;
				break;
			}

		}

	}
	fclose(passw);
	return 0;
}*/
bool accs1(user& customer)
{
	FILE* passw;
	if (fopen_s(&passw, "information", "rb"))
	{
		cout << "Error";
		return 0;
	}
	else
	{
		user customer2;
		while (!feof(passw))
		{
			fread(&customer2, sizeof(user), 1, passw);
			if (check(customer2.login, customer.login, size(customer.login)) && check(customer2.password, customer.password, size(customer.password)))
			{
				fclose(passw);
				if (customer2.role == 2) adminfunc;
				else userfunc();
				return 1;
			}
		}
	}
	cout << "Check your pass or log!" << endl;
	fclose(passw);
	return 0;
}
void newaccount(user& customer)
{
	FILE* passw;
	order str;
	if (fopen_s(&passw, "information", "a+b") == 1)
	{
		cout << "Error";
	}
	else
	{


		cout << "Create login: ";
		cin >> customer.login;

		cout << "Create password: ";
		cin >> customer.password;
		hash<char*> ptr_hash;
		cout << "Hash:" << ptr_hash(customer.password) << endl;
		cout << endl;
		cout << "1 - user" << endl << "2 - admin" << endl << "_________" << endl;
		cout << "Choose your role: ";
		cin >> customer.role;
		if (customer.role != 1 && customer.role != 2)
			cout << "Invalid role!";
		else
		{
			if (customer.role == 2)
				while (1)
				{
					char pass1[4], pass2[] = "keys";
					cout << "Enter admin's special password: ";
					cin >> pass1;
					if (check(pass1, pass2, 4))
					{
						break;
					}
				}


			fwrite(&customer, sizeof(user), 1, passw);
			fclose(passw);
			if (accs1(customer) == 1)
				cout << "You have successfully signed in." << endl;
			if (customer.role == 2)
				adminfunc();
			else userfunc();

		}

	}
}

bool check_dish(order& str)
{
	FILE* MENU_;
	if (fopen_s(&MENU_, "MENU_", "rb"))
		cout << "Error";
	else
	{
		order str2;
		while (!feof(MENU_))
		{
			fread(&str2, sizeof(order), 1, MENU_);

			if (check(str.name, str2.name, size(str.name)) && check(str.type, str2.type, size(str.type)))
			{
				str = str2;
				fclose(MENU_);
				return 1;
			}
		}
	}
	fclose(MENU_);
	return 0;
}

void dish_seek(order& str)
{
	cout << "Information about dishes" << endl;
	cout << "Name of a dish: ";
	cin >> str.name;
	cout << "Type of a dish: ";
	cin >> str.type;
	FILE* MENU_;

	if (fopen_s(&MENU_, "MENU_", "rb"))
	{
		cout << "Error";
	}
	else
	{
		order str2;
		while (!feof(MENU_))
		{
			fread(&str2, sizeof(order), 1, MENU_);
			if (check(str.name, str2.name, 20) && check(str.type, str2.type, 20) == 1)
			{
				
				cout << "Name of the dish: " << str2.name << endl << "Type of the dish: " << str2.type << endl << "Price of the dish: " << str2.price << endl;
			}
			else adminfunc();
		}
	}
	fclose(MENU_);
}
void show_menu(order& str)
{
	order show;
	order str2;
	bool inf = 1;
	FILE* MENU_;
	if (fopen_s(&MENU_, "MENU_", "rb"))
	{
		cout << "Error";
	}
	else
	{
		while (inf)
		{
			fread(&str, sizeof(order), 1, MENU_);
			if (feof(MENU_)) break;

			cout << "Name of the dish:\t" << str.name << "\t" << endl;
			cout << "Type of the dish:\t" << str.type << "\t" << endl;
			cout << "Price of the dish:\t" << str.price << "\t " << endl;

		}
	}
	fclose(MENU_);
}
void dish_registration()
{
	order registration;
	cin.ignore(32767, '\n');
	cout << "Enter the  name of a dish: ";
	cout << endl;
	cin >> registration.name;
	cout << "Enter the type of a dish: ";
	cin >> registration.type;
	//cout << "How many portions do we have?: ";
	//cin >> registration.number;
	cout << "Price of the dish:";
	cin >> registration.price;

	int f1;

	FILE* MENU_;
	if (fopen_s(&MENU_, "MENU_", "a+b"))
	{
		cout << "Error";
	}
	else
	{
		order str1;
		fwrite(&registration, sizeof(order), 1, MENU_);
		fclose(MENU_);

		cout << "Continue?" << endl << "Yes - 1, No - 0" << endl;
		cin >> f1;
		if (f1 == 0) {
			userfunc();
		}
		else adminfunc();


	}
}
// /////////////////////////////////////////////////////////////////////////

void userfunc()
{
	bool b = 0, inf = 1;
	int a, aw;
	order str;

	while (inf)
	{

		//cin.ignore(32767, '\n');


		cout << "Choose what you would like to order: ";
		cin >> str.name;
		cout << "Choose a type of a dish: ";
		cin >> str.type;

		if (check_dish(str) == 1)
		{

			cout << "Name of dish: " << str.name << endl << "Type of dish: " << str.type << endl << "Price of the dish: " << str.price << endl << "Available." << endl;

			cout << "How many portions would you like to order:" << endl;
			cin >> str.quantity;
			bill = bill + (str.quantity * str.price);
			cout << "Would you like to order again?" << endl;
			cout << "1 - Yes,please." << endl << "0 -No,thank you" << endl << "_______" << endl;
			cin >> b;
			if (b == 1)
			{


				userfunc();
			}
		}
		else
			cout << "We do not serve this dish." << endl;
		cout << endl << "Are you done with ordering?" << endl;
		cout << "1- No, I'll order more" << endl << "0 - Yes,please the bill." << endl << "_______" << endl;
		cin >> a;
		if (a == 1) {

			userfunc();

		}

		else {
			cout << "Thank you for choosing our restaurant!" << endl << "Here's your bill:" << ' ' << endl << bill << endl;
			system("pause");
		}
	}

}
void deletedish()
{
	order delete_dish;
	bool inf = 1;
	bool arr = 1;
	while (inf)
	{
		cout << "Choose what dish you wanna delete: " << endl;

		cin >> delete_dish.name;

		cin >> delete_dish.type;

		FILE* MENU_;
		FILE* menu_2;

		if (check_dish(delete_dish))
		{
			if (fopen_s(&MENU_, "MENU_", "rb") || fopen_s(&menu_2, "menu_2", "wb"))
				cout << "Error";
			else
			{
				order str;
				while (!feof(MENU_))
				{
					fread(&str, sizeof(order), 1, MENU_);
					if (feof(MENU_))
						break;
					fwrite(&str, sizeof(order), 1, menu_2);
				}
				fclose(MENU_);
				fclose(menu_2);
			}

			if (fopen_s(&MENU_, "MENU_", "wb") || fopen_s(&menu_2, "menu_2", "rb"))
				cout << "Error";
			else
			{
				order str;
				while (!feof(menu_2))
				{
					fread(&str, sizeof(order), 1, menu_2);

					if (feof(menu_2))

						break;
					if ((!check(delete_dish.name, str.name, 20)) && (!check(delete_dish.type, str.type, 20)))  fwrite(&str, sizeof(order), 1, MENU_);

				}
				fclose(MENU_);
				fclose(menu_2);
			}
			if (!check_dish(delete_dish))
				cout << "The dish has been removed!" << endl;
			break;
		}
	}
}
void adminfunc()
{
	int k;
	order str;

	cout << endl << "1 - Information about dish" << endl << "2 - Create a menu" << endl << "3 - Delete a dish" << endl << "4 - Show a menu" << endl;
	cout << endl << "______________________" << endl;
	cout << "Your choice: ";
	cin >> k;
	switch (k)
	{
	case 1:
		dish_seek(str);
		break;
	case 2:
		dish_registration();
		break;
	case 3:
		deletedish();
		break;
	case 4:
		show_menu(str);
		break;
	default:
		break;
	}
}

void verification(user& customer)
{
	switch (customer.role)
	{
	case 1: userfunc(); break;
	case 2: adminfunc(); break;
	default:
		break;

	}
}
void menu_user(user& customer) {
	static long long id = 0;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (WORD)((7 << 4) | 0));
	system("color F0");
	setlocale(LC_ALL, "");
	bool bw = 1;
	int k, aw;
	order str;
	while (bw)
	{

		cout << "1 - authorize" << endl << "2 - registration" << endl << "______________________" << endl;
		cout << "Please, choose 1 or 2: ";
		cin >> k;
		if (k != 1 && k != 2)

			cout << "Invalid number!" << endl;
		else
		{
			if (k == 1)
			{
				int trials = 0;
				while (trials < 3)
				{


					cout << "Enter your login: ";
					cin >> customer.login;
					cout << "Enter your pass: ";
					cin >> customer.password;
					hash<char*> ptr_hash;
					cout << "Hash:" << ptr_hash(customer.password) << endl;
					if (accs1(customer) == 1) // bool function that check if the user is in the database
					{hash<char*> ptr_hash;
						cout << "You are 1 - user, 2 - admin:" << endl;
						int you;
						cin >> you;
						if (you == 2) {
							while (1)
							{
								char pass1[4], pass2[] = "keys";
								cout << "Enter admin's special password: ";
								cin >> pass1;
								if (check(pass1, pass2, 4))
								{
									adminfunc();
									break;
								}

							}

						}
						else
						{
							cout << "Would you like to see the menu?" << endl << "______________________________________________" << endl;
							cout << "1 - Yes,please" << endl << "2 - No,please" << endl;
							cin >> aw;
							if (aw == 1) {
								show_menu(str);
							}
							userfunc();



						}
					}
					trials++;
				}
				if (trials == 3)
				{
					cout << "Please, ensure you are registered." << endl;
					k = 2;
				}
			}
			if (k == 2)
			{
				newaccount(customer);
				break;

			}
		}
	}
	while (1)
	{
		int k1;
		verification(customer);
		cout << "Continue?" << endl;
		cout << "1 - Yes" << endl << "0 - No" << endl;
		cin >> k1;
		if (k1 == 0) {
			cout << "See you!" << endl;
			break;
		}
	}
}




int main()
{
	user customer;
	double bill = 0;
	setlocale(LC_ALL, "");
	menu_user(customer);

	return 0;
}
