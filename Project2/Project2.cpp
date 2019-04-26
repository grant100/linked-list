// ConsoleApplication1.cpp : Defines the entry point for the console application.


#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cassert>
using namespace std;

const int ZERO = 0;
const int ONE = 1;
const int TWO = 2;

typedef int Node_entry;
//Struct to define node properties
struct Node
{
	Node_entry entry;
	Node *slink = NULL;//used for single linked lists
	Node *rlink = NULL;//used only for double linked lists
	Node *llink = NULL;//used only for double linked lists
	Node();
	Node(int);
};
//Class Definition for Single Linked Lists
class List_Single
{
public:
	List_Single();
	void insert(Node_entry);
	void traverse();
	void traversePrint(void(*visit)(Node *p));//passing print function as a parameter
	bool delete_node(Node_entry);
	void minusCount(){ single_count--; };
	Node_entry getCount() { return single_count; };
	Node_entry getData(Node_entry);
	void traverseDelete();
protected:
	Node *head;
	Node *tail;
	Node_entry single_count = 0;
};
//Class Definition for Double Linked Lists
class List_Double
{
public:
	List_Double();
	void insert_double(Node_entry);
	void traverse_double();
	void traversePrintDouble(void(*visit)(Node *p));//passing print function as a parameter
	void traverseDelete();
protected:
	Node *head;
	Node *tail;
	Node_entry double_count = 0;
};
//Constructor definitions for Node
Node::Node(Node_entry item)
{
	entry = item;
}
//Constructor definitions for Single Linked List
List_Single::List_Single()
{
	head = NULL;
	tail = NULL;
}
//Constructor definitions for Double Linked List
List_Double::List_Double()
{
	head = NULL;
	tail = NULL;
}
// Function Name:	List_Single::insert(Node_entry item) 
// Purpose:	  insert items into single linked list
// Parameters:	integer passed by value
// Returns:	   void
// Pre-conditions:	list object is created
// Post-conditions: node inserted into single linked list	 
void List_Single::insert(Node_entry item)
{
	Node *p = new Node(item);//create new node
	if (head == NULL)
	{
		head = p;
		tail = p;
	}
	else
	{
		tail->slink = p; //set link of tail node to new node
		tail = p; //set tail to look at new node
	}
	single_count++;
}

// Function Name:	List_Double::insert_double(Node_entry item)
// Purpose:	  insert items into double linked list
// Parameters:	integer passed by value
// Returns:	   void
// Pre-conditions:	list object is created
// Post-conditions: node inserted into double linked list
void List_Double::insert_double(Node_entry item)
{
	Node *nNode = new Node(item);
	if (head == NULL)
	{
		head = nNode;
	}
	else
	{
		Node *p, *q;
		p = head;
		q = NULL;
		while (p != NULL && item > p->entry)//check each node, if item is less than p->entry then it comes before p
		{
			q = p;
			p = p->rlink;
		}
		if (q == NULL)//if only one item then nNode comes before node
		{
			nNode->rlink = p; //new node link looks right to old node
			p->llink = nNode;//old node link looks left to new node
			head = nNode;//head now looks at new node
		}
		else
		{
			if (p == NULL)//is true, then biggest item in list so far, point right link of previous node to new node, and new nodes left link to previous node
			{
				q->rlink = nNode;
				nNode->llink = q;
			}
			else //insert node inbetween q and p
			{
				nNode->rlink = p;
				nNode->llink = q;
				p->llink = nNode;
				q->rlink = nNode;
			}
		}

	}
	double_count++;
}

// Function Name:	Print(Node* p)
// Purpose:	  print out data values of node in a list
// Parameters:	node* 
// Returns:	   void
// Pre-conditions:	traversePrint(Print) function is called
// Post-conditions: data value of item is printed to screen
void Print(Node* p)
{
	cout << "\n" << p->entry;
}

// Function Name:	List_Single::delete_node(Node_entry item)
// Purpose:	  delete node with specific value
// Parameters:	Node_entry 
// Returns:	   bool
// Pre-conditions:	user chooses to delete item
// Post-conditions: item is deleted
bool List_Single::delete_node(Node_entry item)
{
	if (head == NULL)
	{
		cout << "\nList is empty";
		return false;
	}
	else
	{
		Node *p, *q;
		p = head;
		q = NULL;
		while (p->entry != item && p->slink != NULL)
		{
			q = p;
			p = p->slink; 
		}
		if (p->entry!= item)
		{
			cout << "\nItem not in list!";
			return false;
		}
		else if (q == NULL)
		{
			head = p->slink;
			cout <<"("<<item<<")"<<" Has been deleted!" << endl;
			delete p;
			return true;
		}
		else
		{
			q->slink = p->slink;
			cout << "(" << item << ")" << " Has been deleted!" << endl;
			delete p;
			return true;
			
		}
		
	}
}

// Function Name:	List_Single::traverse()
// Purpose:	  cycle through each node in list
// Parameters:	none 
// Returns:	   void
// Pre-conditions:	none
// Post-conditions: none
void List_Single::traverse()
{
	if (head == NULL)
	{
		cout << "Node Does not exist";
	}
	else
	{
		Node *p;
		p = head;
		while (p != NULL)
		{
			cout << "\n" << p->entry;
			p = p->slink;
		}
	}
}

// Function Name:	List_Double::traverse_double()
// Purpose:	  cycle through each node in list
// Parameters:	none 
// Returns:	   void
// Pre-conditions:	none
// Post-conditions: none
void List_Double::traverse_double()
{
	if (head == NULL)
	{
		cout << "\nList is empty";
	}
	else
	{
		Node *p;
		p = head;
		while (p != NULL)
		{
			cout <<"\n"<< p->entry;
			p = p->rlink;
		}
	}
}

// Function Name:	List_Single::traversePrint(void(*visit)(Node *p))
// Purpose:	  cycle through each node in list, then call Print function to print node data value
// Parameters:	(void(*visit)(Node *p)) --Print function
// Returns:	   void
// Pre-conditions:	none
// Post-conditions: prints values to screen
void List_Single::traversePrint(void(*visit)(Node *p))
{
	Node *p;
	p = head;
	if (head == NULL)
	{
		cout << "\nNo Items!";
	}
	else
	{
		while (p != NULL)
		{

			(*visit)(p);
			p = p->slink;
		}
	}

}

// Function Name: List_Double::traversePrintDouble(void(*visit)(Node *p))
// Purpose:	  cycle through each node in list, then call Print function to print node data value
// Parameters:	(void(*visit)(Node *p)) --Print function
// Returns:	   void
// Pre-conditions:	none
// Post-conditions: prints values to screen
void List_Double::traversePrintDouble(void(*visit)(Node *p))
{
	
	Node *p;
	p = head;
	if (head == NULL)
	{
		cout << "\nNo Items!";
	}
	else
	{
		while (p != NULL)
		{

			(*visit)(p);
			p = p->rlink;
		}
	}

}

// Function Name: List_Single::getData(Node_entry index)
// Purpose:	  get data values out of nodes in single linked list
// Parameters:	Node_entry index
// Returns:	   Node_entry
// Pre-conditions: none	
// Post-conditions: none
Node_entry List_Single::getData(Node_entry index)
{
	if (head == NULL)//check if node exists
	{
		cout << "Node Does not exist";
	}
	else
	{
		Node *p;
		p = head;
		
		for (int i = 0; i < index; i++)//increment through single linked list until index is reached
		{	
			p = p->slink;			
		}
		return p->entry;//return value of node at index			
	}
}

// Function Name: validInput()
// Purpose:	  check that input from user is valid
// Parameters: none
// Returns:	  int
// Pre-conditions: none	
// Post-conditions: none
int validInput()
{
	int input;
	std::cin >> input;
	while (std::cin.fail())//if failed, not number
	{
		std::cin.clear();
		std::cin.ignore();
		cout << "\nError... Incorrect input!" << "\nWould you like to delete a number? 1 = Yes 2 = No : ";
		std::cin >> input;
	}
	return input;
}
// Function Name: continueInput()
// Purpose:	  check that input from user is valid
// Parameters: none
// Returns:	  int
// Pre-conditions: none	
// Post-conditions: none
int continueInput()
{
	int input;
	int max = 2;
	int min = 1;
	std::cin >> input;
	while (std::cin.fail() || input > TWO || input < ONE )//if failed, not number
	{
		std::cin.clear();
		std::cin.ignore();
		cout << "\nError... Incorrect input!" << "\nLoad new file? 1 = Yes 2 = No : ";
		std::cin >> input;
	}
	return input;
}
// Function Name:	List_Single::traverseDelete()
// Purpose:	  cycle through each node in list and delete
// Parameters:	none 
// Returns:	   void
// Pre-conditions:	none
// Post-conditions: none
void List_Single::traverseDelete()
{
	Node *p, *q;
	
	
	while (head != NULL)
	{
		p = head;
		q = NULL;
		while (p->slink != NULL)
		{
			q = p;
			p = p->slink;
		}
	    if (q == NULL)
		{
			
			//cout << p->entry<<" -1) Has been deleted!" << endl;
			delete p;
			head = NULL;
		}
		else
		{
			q->slink = NULL;
     		//cout <<p->entry<<" -2) Has been deleted!" << endl;
			delete p;
		}	
		single_count--;
	}
}
// Function Name:	List_Double::traverseDelete()
// Purpose:	  cycle through each node in list and delete
// Parameters:	none 
// Returns:	   void
// Pre-conditions:	none
// Post-conditions: none
void List_Double::traverseDelete()
{
	Node *p, *q;


	while (head != NULL)
	{
		p = head;
		q = NULL;
		while (p->rlink != NULL)
		{
			q = p;
			p = p->rlink;
		}
		if (q == NULL)
		{

			//cout << p->entry<<" -1) Has been deleted!" << endl;
			delete p;
			head = NULL;
		}
		else
		{
			q->rlink = NULL;
			//cout <<p->entry<<" -2) Has been deleted!" << endl;
			delete p;
		}
		double_count--;
	}
}
int _tmain()
{
	//declare variables
	Node_entry data;
	Node_entry count;
	//int input;
	bool toDelete = true;

	bool toContinue = true;

	//list objects
	List_Single  list1;
	List_Double list2;

	//input stream
	fstream iFile;
	

	cout << "Grant Sowards" << "\nCS 2420" << "\nProject 2 Linked Lists" << endl;

	
	while (toContinue)
	{
		bool isOpen = false;
		cout << "\nEnter file name (include extension), e.g. numbers.txt: " << endl;
		//loop for inccorect file name inputs
		while (!isOpen)
		{
			string fileName = " ";
			cin.clear();
			std::cin >> fileName;
			iFile.open(fileName);
			if (iFile.is_open())
			{
				isOpen = true;
				cout << "\nOpening File..." << endl;
			}
			else
			{
				cin.clear();
				cout << "Could not open file!" << "\n\nTry Again: ";
			}

		}

		//begin reading in data and inserting into list
		iFile >> data;
		while (!iFile.eof())
		{
			list1.insert(data);
			iFile >> data;

		}

		//traverse once through list, check if user wants to delete item, if so then loop until bool is false or count is 0
		while (toDelete && list1.getCount() > ZERO)
		{
			cout << "\n----------------Begin List--------------------" << endl;
			list1.traversePrint(Print);
			cout << "\n\n----------------End List----------------------" << endl;
			cout << "\n\nWould you like to delete an item? 1 = Yes 2 = No : ";
			int input = NULL;
			input = validInput();
			if (input == ONE)
			{
				cout << "\nChoose number to delete from list.";
				cout << "\nInput number here: ";
				cin.clear();
				Node_entry item = validInput();
				if (list1.delete_node(item))
				{
					list1.minusCount();
				}
			}
			else if (input == TWO)
			{
				toDelete = false; //will cause loop to exit

			}
			else
			{
				cout << "\nError! Incorrect input" << "\nInput a 1 or 2!";

			}
		}

		//if items are in list then proceed to traverse and print each node in list, get data out of single linked list and insert into double linked list
		count = list1.getCount();
		if (count > ZERO)
		{
			int continue_in;
			cout << "\n*****Processing Lists******" << endl;
			for (int i = 0; i < count; i++)//loop number of times based on count of items in single linked list
			{
				list2.insert_double(list1.getData(i));//call get data function to get node data for each node in single linked list
			}
			cout << "\n---------Traversing Single Node List----------";
			list1.traversePrint(Print);
			cout << "\n---------Traversing Double Node List----------";
			list2.traversePrintDouble(Print);
			cout << "\n\nAll items processed!" << endl;
			
			cout << "Load a new file? 1 = Yes 2 = No: ";
			continue_in = validInput();
			if (continue_in == ONE)
			{
				toContinue = true;
				isOpen = false;
				toDelete = true;
			}
			else if (continue_in == TWO)
			{
				toContinue = false;
			}
		}
		else
		{
			int continue_in;
			cout << "\nNo items in list to process!" << endl;
			cout << "Load a new file? 1 = Yes 2 = No: ";
			continue_in = continueInput();
			if (continue_in == ONE)
			{
				toContinue = true;
				isOpen = false;
				toDelete = true;
			}
			else if (continue_in == TWO)
			{
				toContinue = false;
			}

		}
		list1.traverseDelete();
		list2.traverseDelete();
		iFile.close();
	}
	cout << "\nExiting....";
	
	std::cin.clear();
	std::cin.ignore();
	std::cin.get();

	return 0;
}

