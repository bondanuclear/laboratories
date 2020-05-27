#include <iostream>
#include<conio.h>
#include<cstdlib>
using namespace std;
//length
const int word = 20;

void print_1(char* array) {
	int index = 0;

	while (index < word && array[index] != '\0') {
		cout << array[index];
		index++;
	}

}

void copy_1(char* a, char* z) {
	for (int i = 0; i < word; i++) {
		z[i] = a[i];
	}
}

struct node {
	char english[word];
	char ukrainian[word];
	int count = 0;

	node(char* e, char* u) {
		copy_1(e, english);
		copy_1(u, ukrainian);
	}

	node(char* e, char* u, int n) {
		copy_1(e, english);
		copy_1(u, ukrainian);
		count = n;
	}

	node* left = nullptr;
	node* right = nullptr;

	int equivalent(node* Nodee) {
		if (Nodee == nullptr) return 0;

		for (int i = 0; i < word; i++) {
			if (Nodee->english[i] == '\0' && english[i] == '\0') return 0;
			if (english[i] > Nodee->english[i] || Nodee->english[i] == '\0') return -1;
			if (english[i] < Nodee->english[i] || english[i] == '\0') return 1;
		}
		return 0;
	}

	int acc(node* Nodee) {
		if (Nodee == nullptr) return 0;

		if (Nodee->count < count) return -1;
		else if (Nodee->count > count) return 1;
		else {
			for (int i = 0; i < word; i++) {
				if (Nodee->english[i] == '\0' && english[i] == '\0') return 0;
				if (english[i] > Nodee->english[i] || Nodee->english[i] == '\0') return -1;
				if (english[i] < Nodee->english[i] || english[i] == '\0') return 1;
			}
			return 0;
		}
	}

	int equivalent(char* w) {
		for (int i = 0; i < word; i++) {
			if (w[i] == '\0' && english[i] == '\0') return 0;
			if (english[i] > w[i] || w[i] == '\0') return -1;
			if (english[i] < w[i] || english[i] == '\0') return 1;
		}
		return 0;
	};
};

 
static int index = 0;
struct tree {
	node* top = nullptr;
	node* top_1 = nullptr;
	int size = 0;

	void add(node* Nodee) {
		add(Nodee, false);
	}

	void get(char* e) {
		top_1 = top;

		while (true) {
			if (top_1->equivalent(e) == 0) {
				top_1->count++;

				print_1(top_1->ukrainian);
				cout << endl;
				break;
			}
			else if (top_1->equivalent(e) == -1) {
				if (top_1->left == nullptr) {
					cout << "Error! Does not exist!" << endl;
					break;
				}
				else top_1 = top_1->left;
			}
			else {
				if (top_1->right == nullptr) {
					cout << "Error! Doesn't exist!" << endl;
					break;
				}
				else top_1 = top_1->right;
			}
		}
	}

	node** get_() {
		index = 0;
		node** arr = new node * [size];
		ind(top, arr);
		return arr;
	}

	void simplify() {
		node** arr = get_();
		sort(arr, size);
		top = nullptr;
		int size_1 = size;

		for (int i = 0; i < size_1; i++) add(arr[i], true);
		size = size_1;
	}

	void print() {
		if (top != nullptr) print(top, 0);
		else cout << " NULL" << endl;
	}

private:
	void add(node* Nodee, bool sorting) {
		size++;

		Nodee->left = nullptr;
		Nodee->right = nullptr;

		if (top == nullptr) {
			top = Nodee;
		}
		else {
			top_1 = top;

			if (sorting) {
				while (true) {
					if (top_1->acc(Nodee) == -1) {
						if (top_1->left == nullptr) {
							top_1->left = Nodee;
							break;
						}
						else top_1 = top_1->left;
					}
					else {
						if (top_1->right == nullptr) {
							top_1->right = Nodee;
							break;
						}
						else top_1 = top_1->right;
					}
				}
			}
			else {
				while (true) {
					if (top_1->equivalent(Nodee) == -1) {
						if (top_1->left == nullptr) {
							top_1->left = Nodee;
							break;
						}
						else top_1 = top_1->left;
					}
					else {
						if (top_1->right == nullptr) {
							top_1->right = Nodee;
							break;
						}
						else top_1 = top_1->right;
					}
				}
			}
		}
	}

	void print(node* Nodee, int tabs) {
		cout << '{' << endl;

		for (int i = 0; i <= tabs; i++) cout << '\t';
		cout << "english = ";
		print_1(Nodee->english);
		cout << endl;

		for (int i = 0; i <= tabs; i++) cout << '\t';
		cout << "ukrainian = ";
		print_1(Nodee->ukrainian);
		cout << endl;

		for (int i = 0; i <= tabs; i++) cout << '\t';
		cout << "count = " << Nodee->count << endl;

		if (Nodee->left != nullptr) {
			cout << endl;
			for (int i = 0; i <= tabs; i++) cout << '\t';
			cout << "Left = ";
			print(Nodee->left, tabs + 1);
		}
		if (Nodee->right != nullptr) {
			cout << endl;
			for (int i = 0; i <= tabs; i++) cout << '\t';
			cout << "Right = ";
			print(Nodee->right, tabs + 1);
		}

		for (int i = 0; i < tabs; i++) cout << '\t';
		cout << '}' << endl;
	}

	void ind(node* Nodee, node** arr) {
		arr[index] = Nodee;
		index++;

		if (Nodee->left != nullptr) ind(Nodee->left, arr);
		if (Nodee->right != nullptr) ind(Nodee->right, arr);
	}

	void sort(node** array, int size) {
		for (int k = 1; k < size; k++) {
			for (int i = 0; i < size - k; i++) {
				if (array[i]->count < array[i + 1]->count) swap(array[i], array[i + 1]);
			}
		}
	}
};

void menu_main() {
	tree t;

	char english[word];
	char ukrainian[word];
	int c;

	const char* msg_for_help = "----------------------------------------\n"
		"n - New word\n"
		"t - Translation\n"
		"p - Print a tree\n"
		"s - Simplify a tree\n"
		"x - Exit\n"
		"----------------------------------------";
	const char* msg_for_eng = "English word: ";
	const char* msg_for_ukr = "Ukrainian word: ";
	const char* msg_for_count = "Number of using: ";
	const char* msg_for_translate = "Your ukrainian word: ";
	const char* msg_for_print = "A tree: ";
	const char* msg_for_sort = "Simplified tree:";

	char ch;

	while (true) {
		cout << msg_for_help << endl;
		cin >> ch;

		if (ch == 'n') {
			cout << msg_for_eng << endl;
			cin.get();
			cin.getline(english, word);

			cout << msg_for_ukr << endl;
			cin.getline(ukrainian, word);

			cout << msg_for_count << endl;
			cin >> c;

			t.add(new node(english, ukrainian, c));
		}
		else if (ch == 't') {
			cout << msg_for_eng << endl;
			cin.get();
			cin.getline(english, word);
			cout << msg_for_translate << endl;
			t.get(english);
		}
		else if (ch == 'p') {
			cout << msg_for_print << endl;
			t.print();
		}
		else if (ch == 's') {
			t.simplify();
			cout << msg_for_sort << endl;
		}
		else return;
	}
}

int main() {
	menu_main();
	_getch();
	return 0;
}