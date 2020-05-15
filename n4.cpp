#define _USE_MATH_DEFINES
#include<iostream>
#include<string>
#include<stack>
#include<cmath>

using namespace std;
struct node
{
	char* str;
	double x;
	node* left;
	node* right;

	node(double x, char* strtemp) {
		this->x = x;
		this->str = strtemp;
		left = nullptr;
		right = nullptr;
	}
};
double eval(node* root)
{
	if (root == NULL)
		return 0;
	//cout<<root->x<<" ";
	if (root->x != -1)
		return root->x;

	int l = eval(root->left);
	int r = eval(root->right);
	if (int(root->str[0]) == 43)
	{
		return l + r;
	}
	if (int(root->str[0]) == 45)
	{
		return l - r;
	}
	if (int(root->str[0]) == 42)
	{
		return l * r;
	}
	if (int(root->str[0]) == 47)
	{
		return l / r;
	}
	if (int(root->str[0]) == 94) 
	{
		return pow(l,r);
	}
	
	if (int(root->str[0]) == 108) // logarithm
	{
		return log(r)/log(l);
	}
}
void inorder(node* root)
{
	if (root == NULL)
		return;
	inorder(root->left);
	if (root->x == -1)
	{
		cout << root->str << " ";
	}
	else
	{
		cout << root->x << " ";
	}
	inorder(root->right);
}
void preorder(node* root)
{
	if (root == NULL)
		return;
	if (root->x == -1)
	{
		cout << root->str << " ";
	}
	else
	{
		cout << root->x << " ";
	}
	preorder(root->left);

	preorder(root->right);
}
int main() {

	int size;
	cout << "Enter size of string:" << endl;
	cin >> size; // enter size + 1
	cin.ignore();
	char* s = new char[size];
	cout << "Enter your string:" << endl;
	cin.getline(s, size);
	stack<node*> st;
	for (int i = 0; i < size - 1; i++)
	{
		
		if (int(s[i]) == 32)
		{

			continue;
		}
		if (s[i] == '+' || s[i] == '*' || s[i] == '/' || s[i] == '-' || s[i] == '^'  || s[i] == 'l')
		{
			char* strtemp = new char[2];
			strtemp[0] = s[i];
			strtemp[1] = '\0';
			//*strtemp=s[i];
			node* temp = new node(-1, strtemp);
			node* t1 = st.top(); st.pop();
			node* t2 = st.top(); st.pop();
			temp->left = t2;
			temp->right = t1;
			st.push(temp);
		}
		else if (s[i] == 'e') { // exp
			char* strtemp = new char[2];
			strtemp[0] = s[i];
			strtemp[1] = '\0';
			node* temp = new node(M_E, strtemp);
			st.push(temp);
		}
		else
		{
			int x = 0;
			
			char* strtemp = new char[20];
			int counter = 0;
			
			while (int(s[i]) != 32)
			{

				x = x * 10;
				x += (int(s[i]) - int('0'));
				
				strtemp[counter] = s[i];
				counter++;
				i++;
			}
			for (int j = 0; j < 20; j++) {
				if (!(strtemp[i] > 47 && strtemp[i] < 58)) {
					strtemp[i] = '\0';
				}
				
			}
			node* temp = new node(x, strtemp);
			st.push(temp);
		}



	}
	inorder(st.top());  cout << endl;
	preorder(st.top()); cout << endl;
	double ans = eval(st.top());
	cout << ans << endl;
	return 0;
}
// EXAMPLE size = 6 string :6 8 +  => 6 + 8 = 14
// l = logarithm. e = exp
// EXAMPLE size = 14 string:6 8 + 5 4 l + = 6 + 8 + l 5 4 = 14
