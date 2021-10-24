#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

template<class T>
class linkedList
{
private:
	class node
	{
	public:
		node* next;
		node* prev;
		T data;

		node()
			:next(nullptr), prev(nullptr), data(0)
		{

		}

		node(T _data)
			:data(_data), next(nullptr), prev(nullptr)
		{

		}

		node(T _data, node* _next, node* _prev)
			:data(_data), next(_next), prev(_prev)
		{

		}
	};

	node* head;
	node* tail;

	bool isListEmpty()
	{
		if (head == nullptr && tail == nullptr)
			return true;
		else
			return false;
	}

	void mergeSort(linkedList& list)//doesn't need an array parameter because it has this
	{
		if (list.head != nullptr
			&& list.tail != nullptr
			&& list.tail != list.head)//when we have one item
		{
			//split the array into smaller pieces
			linkedList<T> left;
			linkedList<T> right;

			list.split(left, right);

			list.mergeSort(left);
			//start piecing them back together
			list.mergeSort(right);
			//call merge function
			list.merge(left, right);
		}

		return;
	}
public:
	//sets head and tail to nullptr
	linkedList()
		:head(nullptr), tail(nullptr)
	{

	}

	void push_back(T _data)
	{
		//Create a new node
		node* baby = new node(_data);

		if (tail == nullptr) //list is empty)
		{
			tail = baby;
			head = baby;
			baby->next = nullptr;
			baby->prev = nullptr;
		}
		else
		{
			//Point old last node's next ptr to baby node
			tail->next = baby;

			//Point baby's prev ptr to old last node
			baby->prev = tail;

			//Update tail ptr to be the new baby node
			tail = baby;

			//set next to nullpre
			tail->next = nullptr;
		}
	}

	void push_back(node* p)
	{
		if (tail == nullptr)
		{
			tail = p;
			head = p;

			tail->prev = nullptr;
		}
		else
		{
			tail->next = p;
			p->prev = tail;
			tail = p;

		}
	}

	void push_front(node* p)
	{
		if (head == nullptr)
		{
			head = p;
			tail = p;
			head->next = nullptr;

		}
		else
		{
			head->prev = p;
			p->next = head;
			head = p;

		}
	}

	//A simple print method
	void print()
	{
		//check if empty
		if (isListEmpty())
		{
			cout << "(empty)" << endl;
			return;
		}
		else
		{
			for (node* iptr = head; iptr != nullptr; iptr = iptr->next)
			{
				cout << iptr->data << "\t";
			}
			cout << endl << endl;
		}
	}

	//splits the contents of the current object in two halves. Each half goes to the left and right respectively. Runs in O(n)
	void split(linkedList& left, linkedList& right)
	{
		//check if nullptr
		if (tail == nullptr || head == nullptr)
			return;
		else
		{
			linkedList<T> iList;
			iList.head = head;
			iList.tail = tail;
			while (iList.head->next != iList.tail //EVEN CASE
				&& iList.head != iList.tail) //ODD CASE
			{
				//when list is even
				/*right.push_front(tail);
				left.push_back(head);*/

				iList.head = iList.head->next;
				iList.tail = iList.tail->prev;
			}

			//when the list is odd
			if (iList.head == iList.tail)
			{
				left.head = head;
				left.tail = iList.head;

				right.head = iList.head->next;
				right.tail = tail;
			}
			else //when even
			{
				left.head = head;
				left.tail = iList.head;

				right.head = iList.tail;
				right.tail = tail;
			}

			//clear the list
			head = nullptr;
			tail = nullptr;

			//set both ends of right and left to nullptr
			right.head->prev = nullptr;
			right.tail->next = nullptr;

			left.head->prev = nullptr;
			left.tail->next = nullptr;
		}
	}

	//Uses simple selection sort
	void sort()
	{
		linkedList<T> temp;
		temp.head = head;
		temp.tail = tail;
		mergeSort(temp);

		//now i need to swap temp with this
		this->head = temp.head;
		this->tail = temp.tail;
	}

	//Implement a method that takes 2 sorted lists and merges them
	//into your (initially empty) list to create one sorted list.
	//Must run in O(n) time, where n is the total number of items in the two given lists.
	void merge(linkedList& left, linkedList& right)
	{
		//we want to loop until the shortest ends, then attach the remaining list to this
		while (left.head != nullptr && right.head != nullptr)
		{
			if (left.head->data > right.head->data)
			{
				push_back(right.head->data);
				right.head = right.head->next;
			}
			else if (left.head->data < right.head->data)
			{
				push_back(left.head->data);
				left.head = left.head->next;
			}
			else
			{
				push_back(left.head->data);
				left.head = left.head->next;
			}
		}

		//if the left is empty
		if (left.head == nullptr && right.head != nullptr)
		{
			//get the remaining items from the right
			tail->next = right.head;
			right.head->prev = tail;
		}
		else if (right.head == nullptr && left.head != nullptr)//right is empty
		{
			//get the remaining items from the left
			tail->next = left.head;
			left.head->prev = tail;
		}

		//M.I.B. the left and right
		left.head = nullptr;
		left.tail = nullptr;

		right.head = nullptr;
		right.tail = nullptr;
	}

	//loadFromFile should open the file of the specified name and
	//enter each item (words in the novel "Moby Dick" in this case)
	//in the linked list.
	void loadFromFile(string file);

	//writeToFile should write each item in the linked list to the provided output file.
	//In this example, it should write all the words from Moby Dick to the provided output file in sorted order.
	void writeToFile(string file);
};

template<>
class linkedList <string>
{
private:
	class node
	{
	public:
		node* next;
		node* prev;
		string data;

		node()
			:next(nullptr), prev(nullptr), data(0)
		{

		}

		node(string _data)
			:data(_data), next(nullptr), prev(nullptr)
		{

		}

		node(string _data, node* _next, node* _prev)
			:data(_data), next(_next), prev(_prev)
		{

		}
	};

	node* head;
	node* tail;

	bool isListEmpty()
	{
		if (head == nullptr && tail == nullptr)
			return true;
		else
			return false;
	}

	void mergeSort(linkedList& list)//doesn't need an array parameter because it has this
	{
		if (list.head != nullptr
			&& list.tail != nullptr
			&& list.tail != list.head)//when we have one item
		{
			//split the array into smaller pieces
			linkedList<string> left;
			linkedList<string> right;

			list.split(left, right);

			list.mergeSort(left);
			//start piecing them back together
			list.mergeSort(right);
			//call merge function
			list.merge(left, right);
		}

		return;
	}

	

public:
	//sets head and tail to nullptr
	linkedList()
		:head(nullptr), tail(nullptr)
	{

	}

	void push_back(string _data)
	{
		//Create a new node
		node* baby = new node(_data);

		if (tail == nullptr) //list is empty)
		{
			tail = baby;
			head = baby;
			baby->next = nullptr;
			baby->prev = nullptr;
		}
		else
		{
			//Point old last node's next ptr to baby node
			tail->next = baby;

			//Point baby's prev ptr to old last node
			baby->prev = tail;

			//Update tail ptr to be the new baby node
			tail = baby;

			//set next to nullpre
			tail->next = nullptr;
		}
	}

	void push_back(node* p)
	{
		if (tail == nullptr)
		{
			tail = p;
			head = p;

			tail->prev = nullptr;
		}
		else
		{
			tail->next = p;
			p->prev = tail;
			tail = p;

		}
	}

	void push_front(node* p)
	{
		if (head == nullptr)
		{
			head = p;
			tail = p;
			head->next = nullptr;

		}
		else
		{
			head->prev = p;
			p->next = head;
			head = p;

		}
	}

	//A simple print method
	void print()
	{
		//check if empty
		if (isListEmpty())
		{
			cout << "(empty)" << endl;
			return;
		}
		else
		{
			for (node* iptr = head; iptr != nullptr; iptr = iptr->next)
			{
				cout << iptr->data << " ";
			}
			cout << endl << endl;
		}
	}

	//splits the contents of the current object in two halves. Each half goes to the left and right respectively. Runs in O(n)
	void split(linkedList& left, linkedList& right)
	{
		//check if nullptr
		if (tail == nullptr || head == nullptr)
			return;
		else
		{
			linkedList<string> iList;
			iList.head = head;
			iList.tail = tail;
			while (iList.head->next != iList.tail //EVEN CASE
				&& iList.head != iList.tail) //ODD CASE
			{
				//when list is even
				/*right.push_front(tail);
				left.push_back(head);*/

				iList.head = iList.head->next;
				iList.tail = iList.tail->prev;
			}

			//when the list is odd
			if (iList.head == iList.tail)
			{
				left.head = head;
				left.tail = iList.head;

				right.head = iList.head->next;
				right.tail = tail;
			}
			else //when even
			{
				left.head = head;
				left.tail = iList.head;

				right.head = iList.tail;
				right.tail = tail;
			}

			//clear the list
			head = nullptr;
			tail = nullptr;

			//set both ends of right and left to nullptr
			right.head->prev = nullptr;
			right.tail->next = nullptr;

			left.head->prev = nullptr;
			left.tail->next = nullptr;
		}
	}

	//Uses simple selection sort
	void sort()
	{
		linkedList<string> temp;
		temp.head = head;
		temp.tail = tail;
		mergeSort(temp);

		//now i need to swap temp with this
		this->head = temp.head;
		this->tail = temp.tail;
	}

	//Implement a method that takes 2 sorted lists and merges them
	//into your (initially empty) list to create one sorted list.
	//Must run in O(n) time, where n is the total number of items in the two given lists.
	void merge(linkedList& left, linkedList& right)
	{
		//we want to loop until the shortest ends, then attach the remaining list to this
		while (left.head != nullptr && right.head != nullptr)
		{
			if (left.head->data.compare(right.head->data) > 0)
			{
				push_back(right.head->data);
				right.head = right.head->next;
			}
			else if (left.head->data.compare(right.head->data) < 0)
			{
				push_back(left.head->data);
				left.head = left.head->next;
			}
			else
			{
				push_back(left.head->data);
				left.head = left.head->next;
			}
		}

		//if the left is empty
		if (left.head == nullptr && right.head != nullptr)
		{
			//get the remaining items from the right
			tail->next = right.head;
			right.head->prev = tail;
		}
		else if (right.head == nullptr && left.head != nullptr)//right is empty
		{
			//get the remaining items from the left
			tail->next = left.head;
			left.head->prev = tail;
		}

		//M.I.B. the left and right
		left.head = nullptr;
		left.tail = nullptr;

		right.head = nullptr;
		right.tail = nullptr;
	}

	//loadFromFile should open the file of the specified name and
	//enter each item (words in the novel "Moby Dick" in this case)
	//in the linked list.
	void loadFromFile(string file)
	{
		fstream load;
		load.open(file, fstream::in);
		string in;
		while(load >> in)
		{
			//make a new node
			node* babynode = new node(in);
			push_back(babynode);
		
			//ensure to resest in to being empty
			in = "";		

		}

		//done with load
		load.close();
	}

	//writeToFile should write each item in the linked list to the provided output file.
	//In this example, it should write all the words from Moby Dick to the provided output file in sorted order.
	void writeToFile(string file)
	{
		fstream write;
		write.open(file, fstream::out);

		//ensure that the thing is not empty
		if (isListEmpty())
		{
			write << "List is empty" << endl;
		}
		else
		{
			long i = 0;
			//start at head, copy data to file, then go to next node
			for (node* iptr = head; iptr != nullptr; iptr = iptr->next)
			{
				if (++i % 50 == 0)
					write << iptr->data << " " << endl;
				else
					write << iptr->data << " ";

			}
		}

		//don't forget to close the file
		write.close();
	}
};