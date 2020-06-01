#include <iostream>
#include <string>
using namespace std;
void userfunc();
void adminfunc();
struct user
{
	int id;
	int role;
	char login[20];
	char password[20];
};
struct order
{
	int id;
	int number;
	char name[20];
	char type[20];
	double price;
};
bool check(char* arr1, char* arr2, int n)
{
	for (int i = 0; i < n; i++)
		if (arr1[i] != arr2[i])
			return 0;
	return 1;
}
bool accs1(user& customer)
{
	FILE* keys;
	if (fopen_s(&keys, "data1", "rb"))
	{
		perror("Error");
		return 0;
	}
	else
	{
		user customer2;
		while (!feof(keys))
		{
			fread(&customer2, sizeof(user), 1, keys);
			if (check(customer2.login, customer.login, size(customer.login)) && check(customer2.password, customer.password, size(customer.password)))
			{
				fclose(keys);
				if (customer2.role == 2) adminfunc;
				else userfunc;
				return 1;
			}
		}
	}
	cout << "Check your pass or log!" << endl;
	fclose(keys);
	return 0;
}
void newaccount(user &customer)
{
	FILE* keys;
	if (fopen_s(&keys, "data1", "a+b") == 1)
	{
		perror("Error");
	}
	else
	{

		//user customer;
		//id++;
		//customer.id = id;
		cout << "Create login: ";
		cin >> customer.login;
		//scanf_s("%s", client.login, 24);
		cout << "Create password: ";
		cin >> customer.password;
		//scanf_s("%s", client.password, 24);

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
					char a[4], b[] = "0000";
					cout << "Enter admin's special password: ";
					cin >> a;
					if (check(a, b, 4))
					{
						break;
					}
				}


			fwrite(&customer, sizeof(user), 1, keys);
			fclose(keys);
			if (accs1(customer) == 1)
				cout << "You have successfully signed in." << endl;
			if (customer.role == 2)
				adminfunc();
			else userfunc;
		}

	}
}

bool check_dish(order& str) //проверяет наличие блюда в меню
{
	FILE* library1;
	if (fopen_s(&library1, "library1", "rb"))
	{
		perror("Error");
	}
	else
	{
		order str2;
		while (!feof(library1))
		{
			fread(&str2, sizeof(order), 1, library1);
			//cout << str2.name << ' ' << str2.type << endl;
			//if (check(str.name, str2.name, 20) ) cout << str2.name << ' ' << str.name << endl;
			//if (check(str.type, str2.type, 20)) cout << str2.type << ' ' << str.type << endl;

			if (check(str.name, str2.name, 20) && check(str.type, str2.type, 20)==1)
			{

				//cout << str2.name << ' ' << str.name << endl;

				//if (str2.number == 0) break;
				//else
				return 1;
			}
		}
		//fclose(library1);
		fclose(library1);
		return 1;
	}
	//fclose(library1);
	//return 0;
}

void dish_search(order &str)
{
	cout << "Information about dishes" << endl;
	cout << "Name of a dish: ";
	cin >> str.name;
	cout << "Type of a dish: ";
	cin >> str.type;
	FILE* library1;
	
	if (fopen_s(&library1, "library1", "rb"))
	{
		perror("Error");
	}
	else
	{
		order str2;
		while (!feof(library1))
		{
			fread(&str2, sizeof(order), 1, library1);
			if (check(str.name, str2.name, 20) && check(str.type, str2.type, 20) == 1)
			{
				cout /*<< "ID: " << str2.id << endl */<< "Amount: " << str2.number << endl;
				cout << "Name of a dish: " << str2.name << "Type of a dish: " << str2.type << endl;
			}
		}
	}
	fclose(library1);
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
	cout << "How many portions do we have?: ";
	cin >> registration.number;
	int f1;

	FILE* library1;
	if (fopen_s(&library1, "library1", "a+b"))
	{
		perror("Error");
	}
	else
	{
		order str1;
		//while (!feof(library1))
		//{
		  //fread(&str1, sizeof(book), 1, library1);
		  //cout << str1.id << " ";
		  //registration.id = str1.id + 1;
		//}
		//fclose(library1);
		//FILE* library2;
		//if (fopen_s(&library2, "library", "rb"))
		  //perror("Error");
		//else 
		fwrite(&registration, sizeof(order), 1, library1);
		fclose(library1);
		
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
	bool b = 0, arr = 1;
	while (arr)
	{
		order str;
		//cin.ignore(32767, '\n');
		cout << "Choose what you would like to order: ";
		cin >> str.name;
		cout << "Choose a type of a dish: ";
		cin  >> str.type;
		if (check_dish(str)==1)
		{
			cout << "Name of dish: " << str.name << endl << "Type of dish: " << str.type << endl << "Available." << endl << endl << "Would you like to order again?" << endl;
			cout << "1 - Yes,please." << endl << "0 -No,thank you" << endl << "_______" << endl;
			cin >> b;
			if (b == 1) 
			{
				
				 userfunc(); 
			} 

		}
		else
			cout << "We do not serve this dish." << endl;
		cout << endl << "Would you like to reorder?" << endl;
		cout << "1 - Yes,please" << endl << "0 - No, thank you." << endl << "_______" << endl;
		cin >> arr;
	}
	cout << "Thank you for choosing our restaurant!" << endl;
}
void deletedish()
{
	char dish1[20];
	order str;
	cout << " Choose what dish you would like to delete:" << endl;
	cin.getline(dish1, 20);
	FILE* library1;
	FILE* librarynew;
	if (fopen_s(&library1, "library1", "rb"))
	{
		perror("Error");
		
	}
	else
	{
		fread(&dish1, sizeof(order), 1, library1);
		
			if (check(dish1, str.name, size(str.name)) == 0)
			{
				fopen_s(&librarynew, "librarynew", "wb");
				fwrite(&str, sizeof(order), 1, librarynew);
				fclose(librarynew);
				fclose(library1);
			}
		
	}
	
	
}
void adminfunc()
{
	int k;
	order str;
	
	cout << endl << "1 - Information about dish" << endl << "2 - Create a menu" << endl << "3 - Delete a dish";
	cout << endl << "______________________" << endl;
	cout << "Your choice: ";
	cin >> k;
	switch (k)
	{
	case 1:
			dish_search(str);
		break;
	case 2:
		dish_registration();
		break;
	case 3:
		//deletedish();
		break;
	default:
		break;
	}	
}

void verification(user &customer)
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
	setlocale(LC_ALL, "");
	bool bw = 1;
	int k;
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
					if (accs1(customer) == 1) // bool function that check if the user is in the database
					{
						cout << "You are 1 - user, 2 - admin:" << endl;
						int you;
						cin >> you;
						if (you == 2) {
							while (1)
							{
								char a[4], b[] = "0000";
								cout << "Enter admin's special password: ";
								cin >> a;
								if (check(a, b, 4))
								{
									adminfunc();
									break;
								}
								 
							}
						
						}
						else userfunc();
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
				/*cout << "Would you like to order?" << endl;
				cout << "1 - Yes,please" << endl << "0- No, thank you" << endl << "_______" << endl;
				cin >> bw;
				if (bw == 0)
				{
					cout << "See you later!" << endl;
					break;
					bw = 0;
				}*/
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
	///////////////////////////////////////////////////////////
	/*bw = 1;
	while (bw)
	{
		int role;
		cout << endl << "Choose your role: " << endl;
		cout << "1 - user" << endl << "2 - admin" << endl << "_________" << endl;
		cin >> role;
		if (role != 1 && role != 2)
			cout << "Invalid role!";
		else
		{
			if (role == 1) userfunc();
			else
			{
				while (1)
				{
					char a[4], b[] = "0000";
					cout << "Enter admin's special password: ";
					cin >> a;
					if (check(a, b, 4))f
					{
						adminfunc();
						break;
					}
				}
			}
			cout << "Would you like to continue ordering?" << endl;
			cout << "1 - Yes,please" << endl << "0 - No,thank you" << endl << "_______" << endl;
			cin >> k;
			if (k == 0)
			{
				cout << "Thank you for choosing us, goodbye!" << endl;
				break;
			}
		}
	}*/
}

int main()
{
	user customer;
	setlocale(LC_ALL, "");
	menu_user(customer);
	double bill;
}