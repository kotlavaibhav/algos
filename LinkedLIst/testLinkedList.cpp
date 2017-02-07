#include<iostream>
#include "orderedLinkedList.h"

using namespace std;

int main()
{
	orderedLinkedList<int> myList;
	orderedLinkedList<int> firstList;
	orderedLinkedList<int> secondList;

	myList.insert(6);
	myList.insert(9);
	myList.insert(12);


	firstList.insert(40);

	cout << "length of mylist = " << myList.length();

	cout << endl;
	

	cout << "mylist contains :";

	myList.print();

	cout << endl;
	cout << "assigning mylist to firstlist";

	firstList = myList;

	cout << endl;

	cout << "first list contains:";

	firstList.print();
	cout << endl;
	cout << "length of firstlist =";
	cout << firstList.length();
	

	

	cout << endl;
	firstList.splitByVal(3, secondList);

	
	

	cout << "second list contains:";
	secondList.print();
	cout << endl;
	cout << "firstlist contains:";

	firstList.print();
	cout << endl;

	cout << "secondlist contains:";
	secondList.print();
	cout << endl;

	

	
	return 0;
}

