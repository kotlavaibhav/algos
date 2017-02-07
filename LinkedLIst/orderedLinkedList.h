#ifndef H_orderedListType
#define H_orderedListType


#include "linkedList.h"

using namespace std;

template <class Type>
class orderedLinkedList : public linkedListType<Type>
{
public:
	bool search(const Type& searchItem) const;
	//Function to determine whether searchItem is in the list.
	//Postcondition: Returns true if searchItem is in the list,
	//    otherwise the value false is returned.

	void insert(const Type& newItem);
	//Function to insert newItem in the list.
	//Postcondition: first points to the new list, newItem
	//    is inserted at the proper place in the list, and
	//    count is incremented by 1.

	void insertFirst(const Type& newItem);
	//Function to insert newItem at the beginning of the list.
	//Postcondition: first points to the new list, newItem is
	//    inserted at the beginning of the list, last points to the
	//    last node in the list, and count is incremented by 1.

	void insertLast(const Type& newItem);
	//Function to insert newItem at the end of the list.
	//Postcondition: first points to the new list, newItem is
	//    inserted at the end of the list, last points to the
	//    last node in the list, and count is incremented by 1.

	void deleteNode(const Type& deleteItem);
	//Function to delete deleteItem from the list.
	//Postcondition: If found, the node containing deleteItem is
	//    deleted from the list; first points to the first node
	//    of the new list, and count is decremented by 1. If
	//    deleteItem is not in the list, an appropriate message
	//    is printed.

	void splitByVal(Type v, orderedLinkedList<Type> &secondList);
	//Divide the list in the class into two sublists.  The first
	//sublist, which replaces the original list in the class, contains
	//all nodes with values less than the specified
	//value v while the second sublist contains the rest of nodes.
	//Note: the function will neither create nor destroy any node.
	//Post condition: first and last point to the first and
	//   last nodes of the first sublist (the list within the class).
	//   secondList.first and secondList.last point to the
	//   first and last nodes of the second sublist.

};

template <class Type>
bool orderedLinkedList<Type>::search(const Type& searchItem) const
{
	bool found = false;
	nodeType<Type> *current; //pointer to traverse the list

	current = this->first;  //start the search at the first node

	while (current != NULL && !found)
		if (current->info >= searchItem)
			found = true;
		else
			current = current->link;

	if (found)
		found = (current->info == searchItem); //test for equality

	return found;
}//end search


template <class Type>
void orderedLinkedList<Type>::insert(const Type& newItem)
{
	nodeType<Type> *current; //pointer to traverse the list
	nodeType<Type> *trailCurrent = NULL; //pointer just before current
	nodeType<Type> *newNode;  //pointer to create a node

	bool  found;

	newNode = new nodeType<Type>; //create the node
	newNode->info = newItem;   //store newItem in the node
	newNode->link = NULL;      //set the link field of the node
	//to NULL

	if (this->first == NULL)  //Case 1
	{
		this->first = newNode;
		this->last = newNode;
		this->count++;
	}
	else
	{
		current = this->first;
		found = false;

		while (current != NULL && !found) //search the list
			if (current->info >= newItem)
				found = true;
			else
			{
				trailCurrent = current;
				current = current->link;
			}

		if (current == this->first)      //Case 2
		{
			newNode->link = this->first;
			this->first = newNode;
			this->count++;
		}
		else                       //Case 3
		{
			trailCurrent->link = newNode;
			newNode->link = current;

			if (current == NULL)
				this->last = newNode;

			this->count++;
		}
	}//end else
}//end insert

template<class Type>
void orderedLinkedList<Type>::insertFirst(const Type& newItem)
{
	insert(newItem);
}//end insertFirst

template<class Type>
void orderedLinkedList<Type>::insertLast(const Type& newItem)
{
	insert(newItem);
}//end insertLast

template<class Type>
void orderedLinkedList<Type>::deleteNode(const Type& deleteItem)
{
	nodeType<Type> *current; //pointer to traverse the list
	nodeType<Type> *trailCurrent = NULL; //pointer just before current
	bool found;

	if (this->first == NULL) //Case 1
		cout << "Cannot delete from an empty list." << endl;
	else
	{
		current = this->first;
		found = false;

		while (current != NULL && !found)  //search the list
			if (current->info >= deleteItem)
				found = true;
			else
			{
				trailCurrent = current;
				current = current->link;
			}

		if (current == NULL)   //Case 4
			cout << "The item to be deleted is not in the "
			<< "list." << endl;
		else
			if (current->info == deleteItem) //the item to be
				//deleted is in the list
			{
			if (this->first == current)       //Case 2
			{
				this->first = this->first->link;

				if (this->first == NULL)
					this->last = NULL;

				delete current;
			}
			else                         //Case 3
			{
				trailCurrent->link = current->link;

				if (current == this->last)
					this->last = trailCurrent;

				delete current;
			}
			this->count--;
			}
			else                            //Case 4
				cout << "The item to be deleted is not in the "
				<< "list." << endl;
	}
}//end deleteNode


template<class Type>
void orderedLinkedList<Type>::splitByVal(Type v, orderedLinkedList<Type> &secondList)
{
	nodeType<Type> *current;
	int listcount, listsub;
	if ((v % 2) != 0)
		listcount = (v / 2 + 1);
	else
		listcount = (v / 2);

	listsub = (v - listcount);

	if (first == NULL) {  // list1 is empty
		cerr << "cannot split an empty  list";
	}

	current = first;
	secondList.last = last;

	for (int i = 0; i <listcount; i++)
	{
		last = current;
		current = current->link;

	}

	secondList.first = current;
	last->link = NULL;


}

#endif