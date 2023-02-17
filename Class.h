#pragma once
#include<iostream>
#include<string>
#include<stdlib.h>
#include<cassert>
#include<time.h>
using namespace std;
template<class type>
struct nodetype																	//creates nodes
{
	type info;
	nodetype<type>* link;
};
template<class type>
class linked_list
{
protected:
	int count;
	nodetype<type>* first;														//pointer points to the first element
	nodetype<type>* last;														//pointer points to the last element
private:
	void copy_list(const linked_list<type>& other_list);
public:
	const linked_list<type>& operator=(const linked_list<type>& other_list);
	void initialize_list();														//calls destroy_list() function
	type front() const;
	type back() const;
	linked_list();
	void destroy_list();
	virtual void print(int transaction_number) = 0;
	bool is_empty_list() const;
	int length() const;
	bool search(const type& search_item) const;
	virtual void insert_first(const type& new_item) = 0;
	virtual void insert_last(const type& new_item) = 0;
	virtual void delete_node(const type& delete_item) = 0;
	linked_list(const linked_list<type>& other_list);
	~linked_list();
};
template <class type>
class unordered_linked_list : public linked_list<type>
{
public:
	void insert_first(const type& new_item);
	void insert_last(const type& new_item);
	void delete_node(const type& delete_item);
	void print(int transaction_number);
};
template<class type>
class array_list
{
private:
	type* list;
	int length;
	int max_size;
public:
	const array_list<type>& operator=(const array_list<type>& other_list);		//operator overloading
	bool is_empty() const;
	bool is_full() const;
	int list_size() const;
	int max_array_size() const;
	void print() const;
	bool is_item_at_equal(int location, const type& item) const;				//Compares the input item with an item at a specified location
	void insert_at(int location, const type& insert_item);
	void insert_end(const type& insert_item);
	void remove_at(int location);
	void retrieve_at(int location, bool& inserted, type& ret_item) const;
	void replace_at(int location, const type& rep_item);
	void clear_list();
	int search(const type& item) const;
	array_list(int size);
	array_list(const array_list<type>& other_list);								//copy constructor
	~array_list();
};
class account_functions
{
	friend ostream& operator<<(ostream& ostream, const account_functions&);		//friend function operator overloading for cout
private:
	string name, password;
	double  balance;
	int id;
	int transaction_number;														//count for number of transactions
	unordered_linked_list<double> transaction_history;
public:
	bool operator==(const account_functions other_account);
	void set_name(string n);
	string get_name() const;
	void set_password(string p);
	string get_password() const;
	account_functions(double b, string p, string n);
	account_functions();
	void rand_id();																//generates random ID between 0 and 100, integer
	int get_id() const;
	void set_balance(double b);
	double get_balance() const;
	void display_balance();
	void update_name();
	void update_password();
	void withdraw();
	void deposit();
	void account_info();
	void trans_his();															//displays unordered linked list containing transaction history
};