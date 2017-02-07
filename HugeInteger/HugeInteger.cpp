#include "HugeInteger.h"
#include <iostream>


using namespace std;


HugeInteger::HugeInteger(long number)			//pre condition constructor: converts a long integer into a HugeInteger object
{
	for (int i = 0; i<size; i++)			//post condition - initialize vector set to 0

		set.push_back(0);



	for (int j = 39; number != 0 && j >= 0; j--)		// convert long int to HugeInteger

	{

		set[j] = number % 10;

		number /= 10;


	}

}
HugeInteger::HugeInteger(const string& other)		// constructor string to HugeInteger

{

	for (int i = 0; i < size; i++)
		set.push_back(0);

	int length = other.length();

	for (int j = size - length, k = 0; j < size; j++, k++)
	{
		set[j] = other[k] - '0';		//convert string to HugeInteger
	}
}

void HugeInteger::output()		//output the contents of set
{

	bool found = false;


	for (int i = 0; i < size; i++)
	{

		if (set[i] != 0)				// find the first non zero number
			found = true;
		if (found == true)
		{
			break;
		}
		else
			counter++;		//increment the counter
	}
	if (found)

		for (int i = counter; i < size; i++)		//remove the leading zeros by printing from the first non zero number
		{
		cout << set[i];
		}
	counter = 0;
}

HugeInteger HugeInteger::add(const HugeInteger & other) const		//addition 
{
	HugeInteger temp;

	int carry = 0;



	for (int i = 39; i >= 0; i--)

	{

		temp.set[i] = set[i] + other.set[i] + carry;	// add the two sets and carry



		if (temp.set[i] > 9)

		{

			temp.set[i] %= 10;

			carry = 1;


		}



		else

			carry = 0;
		if (i == 0)			// for the most significant digit
		{
			if (carry != 0)	//if carry is not 0 then it is overflow
			{



				for (int i = 39; i >= 0; i--)
				{
					temp.set[i] = 0;
					cout << temp.set[i];			//output 0 as a huge integer
				}
				cout << " overflow!!!!!" << endl << endl;
			}
		}
	}

	return temp;
}

HugeInteger HugeInteger::add(int other) const

{

	return (*this).add(HugeInteger(other));			//add function *this + integer

}
HugeInteger HugeInteger::add(const string& other) const

{

	return (*this).add(HugeInteger(other));		//add function *this + string

}

HugeInteger HugeInteger::subtract(const HugeInteger &other) const		//subtract function

{

	if (this->isLessThan(HugeInteger(other)) == true)			//if subtract larger value from smaller value
	{
		cout << "Error: Tried to subtract larger value from smaller value";
		return 0;
	}


	else
	{
		HugeInteger temp, resulttemp;

		int Minuscarry = 0;



		{
			for (int i = 39; i >= 0; i--)

			{


				resulttemp.set[i] = set[i] - other.set[i] + Minuscarry;



				if (resulttemp.set[i] < 0)

				{

					resulttemp.set[i] %= 10;

					temp.set[i] = -1 * resulttemp.set[i];

					Minuscarry = -1;

				}



				else

				{

					temp.set[i] = resulttemp.set[i];

					Minuscarry = 0;

				}

			}
			if (this->isEqualTo(HugeInteger(other)) == true)
			{
				for (int i = 39; i >= 0; i--)
				{
					temp.set[i] = 0;
					cout << temp.set[i];

				}

			}


			return temp;

		}
	}
}

HugeInteger HugeInteger::subtract(int other) const	//subtract function hugeinteger - int

{

	return (*this).subtract(HugeInteger(other));

}

HugeInteger HugeInteger::subtract(const string& other) const//subtract function hugeinteger - string

{

	return (*this).subtract(HugeInteger(other));

}
void HugeInteger::input(const string &other)
{


	int length = other.length();

	for (int j = size - length, k = 0; j < size; j++, k++)
	{
		set[j] = other[k] - '0';
	}
}
bool HugeInteger::isEqualTo(const HugeInteger & other) const		// returns true or false based on the condition isEqualTo
{
	return (set == other.set);


}
bool HugeInteger::isNotEqualTo(const HugeInteger & other) const		// returns true or false based on the condition isNotEqualTo
{
	return (set != other.set);


}
bool HugeInteger::isGreaterThan(const HugeInteger & other) const	// returns true or false based on the condition isGreaterThan
{
	return (set > other.set);


}

bool HugeInteger::isLessThan(const HugeInteger &other) const		// returns true or false based on the condition isLessThan
{
	return (set < other.set);


}
bool HugeInteger::isGreaterThanOrEqualTo(const HugeInteger &other) const	// returns true or false based on the condition isGreaterThanOrEqual
{
	return (set >= other.set);


}
bool HugeInteger::isLessThanOrEqualTo(const HugeInteger & other) const	// returns true or false based on the condition isLessThanOrEqualTo
{
	return (set <= other.set);


}
bool HugeInteger::isZero() const		//checks if HugeInteger is equal to zero
{

	for (int i = 39; i >= 0; i--)
	{
		return  (set[i] == 0);
	}


}