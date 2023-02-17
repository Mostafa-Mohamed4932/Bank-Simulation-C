#include"Class.h"
///////////////////////////////////// Implementation //////////////////////////////////////
///////////////////////////////////// Account Functions Implementation //////////////////////////////////////
ostream& operator<<(ostream& ostream, const account_functions& account)
{
	ostream << "Account Name - " << account.get_name() << endl;
	return ostream;
}
bool account_functions::operator==(const account_functions other_account)
{
	return(this->balance == other_account.balance && this->name == other_account.name && this->password == other_account.password);
}
void account_functions::set_name(string n)
{
	n[0] = toupper(n[0]);															//capitalizes first letter in name member
	name = n;
}
string account_functions::get_name() const
{
	return name;
}
void account_functions::set_password(string p)
{
	password = p;
}
string account_functions::get_password() const
{
	return password;
}
account_functions::account_functions(double b, string p, string n)
{
	set_balance(b);
	set_password(p);
	set_name(n);
	rand_id();
	transaction_history.insert_first(get_balance());
	transaction_number = 1;
}
account_functions::account_functions()
{
	balance = 0;
	rand_id();
	transaction_history.insert_first(get_balance());
	transaction_number = 1;
}
void account_functions::rand_id()
{
	// Use current time as seed for random generator
	srand(time(0));
	id = rand() % 100;
}
int account_functions::get_id() const
{
	return id;
}
void account_functions::set_balance(double b)
{
	balance = b;
}
double account_functions::get_balance() const
{
	return balance;
}
void account_functions::display_balance()
{
	cout << "Your current balance is: " << get_balance() << "$." << endl;
	transaction_history.insert_last(get_balance());
	transaction_number++;
}
void account_functions::update_name()
{
	string new_name;
	cout << "Please, enter your new name." << endl;
	cin >> new_name;
	while (get_name() == new_name)
	{
		cout << "Your new name can't be the same as the old name, please enter a new name." << endl;
		cin >> new_name;
	}
	set_name(new_name);
}
void account_functions::update_password()
{
	string test;
	bool flag = false;
	int count = 0;
	cout << "Please, enter your original password." << endl;
	cin >> test;
	while ((count < 3) && (flag == false))
	{
		if (test == get_password())
		{
			flag = true;
		}
		else
		{
			count++;
			cout << "Wrong password, please try again." << endl;
			cin >> test;
		}
	}
	if (flag)
	{
		string new_password;
		cout << "Please, enter your new password." << endl;
		cin >> new_password;
		while (get_password() == new_password)
		{
			cout << "This password is already in use, please enter a new one." << endl;
			cin >> new_password;
		}
		set_password(new_password);
	}
}
void account_functions::withdraw()
{
	double w;
	cout << "Please, enter the amount that you would like to withdraw." << endl;
	cin >> w;
	while (w > get_balance())
	{
		cout << "Insufficient balance, please try again." << endl;
		cin >> w;
	}
	set_balance(get_balance() - w);
	cout << "You have withdrawn " << w << "$, your current balance is " << get_balance() << "$." << endl << endl;;
	transaction_history.insert_last(get_balance());
	transaction_number++;
}
void account_functions::deposit()
{
	double d;
	cout << "Please, enter the amount that you would like to deposit." << endl;
	cin >> d;
	set_balance(get_balance() + d);
	cout << "You have deposited " << d << "$, your current balance is " << get_balance() << "$." << endl << endl;
	transaction_history.insert_last(get_balance());
	transaction_number++;
}
void account_functions::account_info()
{
	cout << "Your account name is: " << get_name() << ", your ID is: " << get_id() << ",and your password is: " << get_password() << "." << endl << endl;
}
void account_functions::trans_his()
{
	transaction_history.print(transaction_number);
}
///////////////////////////////////////// ADT Linked List ////////////////////////////////////////////////
template <class type>
const linked_list<type>& linked_list<type>::operator=(const linked_list<type>& other_list)
{
	if (this != &other_list)
	{
		copy_list(other_list);
	}
	return *this;
}
template <class type>
type linked_list<type>::front() const
{
	assert(first != NULL);
	return first->info;
}
template <class type>
type linked_list<type>::back() const
{
	assert(last != NULL);
	return last->info;
}
template <class type>
void linked_list<type>::initialize_list()
{
	destroy_list();
}
template<class type>
linked_list<type>::linked_list()
{
	first = NULL;
	last = NULL;
	count = 0;
}
template<class type>
void linked_list<type>::destroy_list()
{
	nodetype<type>* temp;
	while (first != NULL)
	{
		temp = first;
		first = first->link;
		delete temp;
	}
	last = NULL;
	count = 0;
}
template<class type>
bool linked_list<type>::is_empty_list() const
{
	if (first == last)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
template<class type>
int linked_list<type>::length() const
{
	return count;
}
template<class type>
bool linked_list<type>::search(const type& search_item) const
{
	nodetype<type>* current;
	bool found = false;
	current = first;
	while (current != NULL && !found)
	{
		if (current->info == search_item)
		{
			found = true;
		}
		else
		{
			current = current->link;
		}
	}
	return found;
}
template<class type>
void linked_list<type>::copy_list(const linked_list<type>& other_list)
{
	nodetype<type>* new_node;
	nodetype<type>* current;
	if (first != NULL)
	{
		destroy_list();
	}
	if (other_list.first == NULL)
	{
		first = NULL;
		last = NULL;
		count = 0;
	}
	else
	{
		current = other_list.first;
		count = other_list.count;
		first = new nodetype<type>;
		first->info = current->info;
		first->link = NULL;
		last = first;
		current = current->link;
		while (current != NULL)
		{
			new_node = new nodetype<type>;
			new_node->info = current->info;
			new_node->link = NULL;
			last->link = new_node;
			last = new_node;
			current = current->link;
		}
	}
}
template<class type>
linked_list<type>::linked_list(const linked_list<type>& other_list)
{
	first = NULL;
	copy_list(other_list);
}
template<class type>
linked_list<type>::~linked_list()
{
	destroy_list();
}
template<class type>
void unordered_linked_list<type>::print(int transaction_number)
{
	nodetype<type>* current;
	current = linked_list<type>::first;
	for (int i = 0; i < transaction_number;)
	{
		while (current != NULL) {
			cout << "Transaction #" << i + 1 << ": " << current->info << endl;
			current = current->link;
			i++;
		}
	}
}
template<class type>
void unordered_linked_list<type>::insert_first(const type& new_item)
{
	nodetype<type>* new_node;
	new_node = new nodetype<type>;
	new_node->info = new_item;
	new_node->link = linked_list<type>::first;
	linked_list<type>::first = new_node;
	linked_list<type>::count++;
	if (linked_list<type>::last == NULL)
	{
		linked_list<type>::last = new_node;
	}
}
template<class type>
void unordered_linked_list<type>::insert_last(const type& new_item)
{
	nodetype<type>* new_node;
	new_node = new nodetype<type>;
	new_node->info = new_item;
	new_node->link = NULL;
	linked_list<type>::last->link = new_node;
	linked_list<type>::last = new_node;
	linked_list<type>::count++;
	if (linked_list<type>::first == NULL)
	{
		linked_list<type>::first = new_node;
	}
}
template<class type>
void unordered_linked_list<type>::delete_node(const type& delete_item)
{
	nodetype<type>* current;
	nodetype<type>* trail_current;
	bool found;
	if (linked_list<type>::first == NULL)
	{
		cout << "Cannot delete from an empty list." << endl;
	}
	else
	{
		if (linked_list<type>::first->info == delete_item)
		{
			current = linked_list<type>::first;
			linked_list<type>::first = linked_list<type>::first->link;
			linked_list<type>::count--;
			if (linked_list<type>::first == NULL)
			{
				linked_list<type>::last = NULL;
			}
			delete current;
		}
		else
		{
			found = false;
			trail_current = linked_list<type>::first;
			current = linked_list<type>::first->link;
			while (current != NULL && !found) {
				if (current->info != delete_item)
				{
					trail_current = current;
					current = current->link;
				}
				else
				{
					found = true;
				}
			}
			if (found)
			{
				trail_current->link = current->link;
				linked_list<type>::count--;
				if (linked_list<type>::last == current)
				{
					linked_list<type>::last = trail_current;
				}
				delete current;
			}
			else
			{
				cout << "The item to be deleted is not in the list." << endl;
			}
		}
	}
}
///////////////////////////////////////// ADT Array List ////////////////////////////////////////////////
template <class type>
const array_list<type>& array_list<type>::operator=(const array_list<type>& other_list)
{
	if (this != &other_list)
	{
		delete[] list;
		max_size = other_list.max_size;
		length = other_list.length;
		list = new type[max_size];
		assert(list != NULL);
		for (int i = 0; i < length; i++)
		{
			list[i] = other_list.list[i];
		}
	}
	return *this;
}
template<class type>
bool array_list<type>::is_empty() const
{
	return (length == 0);
}
template<class type>
bool array_list<type>::is_full() const
{
	return (length == max_size);
}
template<class type>
int array_list<type>::list_size() const
{
	return length;
}
template<class type>
int array_list<type>::max_array_size() const
{
	return max_size;
}
template<class type>
void array_list<type>::print() const
{
	for (int i = 0; i < length; i++)
	{
		cout << i + 1 << ": " << list[i];
	}
	cout << endl;
}
template<class type>
bool array_list<type>::is_item_at_equal(int location, const type& item) const
{
	return(list[location] == item);
}
template<class type>
void array_list<type>::insert_at(int location, const type& insert_item)
{
	if (location < 0 || location >= max_size)
	{
		cout << "The position of the item to be inserted is out of range." << endl;
	}
	else if (length >= max_size)
	{
		cout << "Cannot insert in a full list." << endl;
	}
	else
	{
		for (int i = length; i > location; i--)
		{
			list[i] = list[i - 1];
		}
		list[location] = insert_item;
		length++;
	}
}
template<class type>
void array_list<type>::insert_end(const type& insert_item)
{
	if (length >= max_size)
	{
		cout << "Cannot insert in a full list." << endl;
	}
	else
	{
		list[length] = insert_item;
		length++;
	}
}
template<class type>
void array_list<type>::remove_at(int location)
{
	if (location < 0 || location >= length)
	{
		cout << "The location of the item to be removed is out of range." << endl;
	}
	else
	{
		for (int i = location; i < length - 1; i++)
		{
			list[i] = list[i + 1];
		}
		length--;
	}
}
template<class type>
void array_list<type>::retrieve_at(int location, bool& inserted, type& ret_item) const
{
	if (location < 0 || location >= length)
	{
		cout << "The location of the item to be retrieved is out of range." << endl;
		inserted = 0;
	}
	else
	{
		ret_item = list[location];
		inserted = 1;
	}
}
template<class type>
void array_list<type>::replace_at(int location, const type& rep_item)
{
	if (location < 0 || location >= length)
	{
		cout << "The location of the item to be replaced is out of range." << endl;
	}
	else
	{
		list[location] = rep_item;
	}
}
template<class type>
void array_list<type>::clear_list()
{
	length = 0;
}
template<class type>
int array_list<type>::search(const type& item) const
{
	int loc;
	bool found = false;
	for (loc = 0; loc < length; loc++)
	{
		if (list[loc] == item)
		{
			found = true;
		}
	}
	if (found)
	{
		return loc;
	}
	else {
		return -1;
	}
}
template<class type>
array_list<type>::array_list(int size)
{
	if (size < 0)
	{
		cout << "The array size must be positive. Creating an array of size 100." << endl;
		max_size = 100;
	}
	else
	{
		max_size = size;
	}
	length = 0;
	list = new type[max_size];
	assert(list != NULL);
}
template<class type>
array_list<type>::array_list(const array_list<type>& other_list)
{
	max_size = other_list.max_size;
	length = other_list.length;
	list = new type[max_size];
	assert(list != NULL);
	for (int j = 0; j < length; j++)
	{
		list[j] = other_list.list[j];
	}
}
template<class type>
array_list<type>::~array_list()
{
	delete[] list;
}
//////////////////////////////////////////// Main ////////////////////////////////////////////
void initialize_list(array_list<account_functions>& accounts_list);
void create_account(array_list<account_functions>& accounts_list);
bool password_valid(const account_functions);
void operations_on_account(account_functions);
int main()
{
	array_list<account_functions> accounts_list(100);
	account_functions acc;
	int choice_of_account, choice_of_start;
	bool in_range, flag = false;
	initialize_list(accounts_list);
	do
	{
		cout << "Please choose one of the following operations:\n1.Create an account\n2.Choose an account\n\n";
		cin >> choice_of_start;
		if (choice_of_start == 1 || choice_of_start == 2)
		{
			if (choice_of_start == 1)
			{
				create_account(accounts_list);
			}
			cout << "Choose one of the following accounts: \n";
			accounts_list.print();
			cin >> choice_of_account;

			accounts_list.retrieve_at(choice_of_account - 1, in_range, acc);

			if (in_range == 1) {

				flag = password_valid(acc);

				if (flag) {
					cout << "Correct Password\nWelcome " << acc.get_name() << "!\n\n";
					operations_on_account(acc);
				}
				else {
					cout << "Failed Password Attempts\n";
				}
			}
			else {
				cout << "\nAccount chosen doesn't exist\n";
			}
		}
		else
		{
			cout << "Unknown operation\n";
			cout << "Please try again\n\n";
		}
	} while (choice_of_start != 1 && choice_of_start != 2);
	system("pause");
	return 0;
}
void initialize_list(array_list<account_functions>& accounts_list)
{
	account_functions acc1(500000, "Pass1", "Ahmed");
	account_functions acc2(2500, "Pass2", "Mohamed");
	account_functions acc3(5000, "Pass3", "Mostafa");
	account_functions acc4(10000, "Pass4", "Yousef");
	account_functions acc5(60, "Pass5", "Ashraf");
	accounts_list.insert_at(0, acc1);
	accounts_list.insert_at(1, acc2);
	accounts_list.insert_at(2, acc3);
	accounts_list.insert_at(3, acc4);
	accounts_list.insert_at(4, acc5);
}
void create_account(array_list<account_functions>& accounts_list)
{
	string name, password;
	int balance;
	cout << "Please, Enter your name." << endl;
	cin >> name;
	cout << endl;
	cout << "Please, Enter your password." << endl;
	cin >> password;
	cout << endl;
	cout << "Please, Enter your initial deposit." << endl;
	cin >> balance;
	cout << endl;
	account_functions new_acc(balance, password, name);
	accounts_list.insert_end(new_acc);
}
bool password_valid(const account_functions acc)
{
	int count = 0;
	bool flag = false;
	string enter_password;
	cout << "Enter password of account:\n";
	cin >> enter_password;
	while ((count < 3) && (flag == false))
	{
		if (enter_password == acc.get_password())
		{
			flag = true;
		}
		else
		{
			count++;
			cout << "Wrong password, please try again:\n";
			cin >> enter_password;
		}
	}
	cout << endl;
	return flag;
}
void operations_on_account(account_functions acc)
{
	int choice_of_operation;
	char choice_of_reseting;
	do
	{
		cout << "Please, Choose an operation:\n1. Change Name\n2. Change Password\n3. Deposit\n4. Withdraw\n5. Display Balance\n6. Transaction History\n7. Display Account Info\n\n";
		cin >> choice_of_operation;
		switch (choice_of_operation)
		{
		case 1:
			acc.update_name();
			break;
		case 2:
			acc.update_password();
			break;
		case 3:
			acc.deposit();
			break;
		case 4:
			acc.withdraw();
			break;
		case 5:
			acc.display_balance();
			break;
		case 6:
			acc.trans_his();
			break;
		case 7:
			acc.account_info();
			break;
		default:
			cout << "Unknown operation";
		}
		cout << "Do you want another operation? (Y/N)\n";
		cin >> choice_of_reseting;
		cout << endl;
		if (choice_of_reseting != 'n' && choice_of_reseting != 'N' && choice_of_reseting != 'y' && choice_of_reseting != 'Y') {
			do
			{
				cout << "Unkown choice, please try again\n";
				cout << "Do you want another operation? (Y/N)\n\n";
				cin >> choice_of_reseting;
				cout << endl;
			} while (choice_of_reseting != 'n' && choice_of_reseting != 'N' && choice_of_reseting != 'y' && choice_of_reseting != 'Y');
		}
	} while (choice_of_reseting == 'y' || choice_of_reseting == 'Y');
}