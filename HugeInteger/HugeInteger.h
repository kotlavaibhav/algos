#ifndef HugeInteger_H
#define HugeInteger_H
#include<vector>


using namespace std;
class HugeInteger
{
public:
	static const int size = 40;
	// constructor: converts a long integer into a HugeInteger object
	HugeInteger(long =0);
	// constructor: converts a string representing a large int to a HugeInteger object
	HugeInteger(const string&);
	// Addition operator: HugeInteger + HugeInteger
	// If overflow, prints “Error: Addition overflow” and return 0 (as HugeInteger)
	HugeInteger add(const HugeInteger &) const;
	// Addition operator: HugeInteger + int
	// If overflow, prints “Error: Addition overflow” and return 0 (as HugeInteger)
	HugeInteger add(int) const;
	// Addition operator: HugeInteger + string representing large integer value
	// If overflow, prints “Error: Addition overflow” and return 0 (as HugeInteger)
	HugeInteger add(const string &) const;
	// subtraction operator (subtract op2 from *this); op1 – op2
	// where op1 is a HugeInteger and op2 is also a HugeInteger
	// if op1 < op2, prints “Error: Tried to subtract larger value from smaller value”
	// and return 0 (as HugeInteger).
	HugeInteger subtract(const HugeInteger & op2) const;
	// subtraction operator (subtract op2 from *this); op1 – op2
	// where op1 is a HugeInteger and op2 is int
	// if op1 < op2, prints “Error: Tried to subtract larger value from smaller value”
	// and return 0 (as HugeInteger).
	HugeInteger subtract(int op2) const;
	// subtraction operator; subtract op2 from *this); op1 – op2
	// where op1 is a HugeInteger and op2 is a string representing large integer value
	// if op1 < op2, prints “Error: Tried to subtract larger value from smaller value”
	// and return 0 (as HugeInteger).
	HugeInteger subtract(const std::string & op2) const;
	// comparison or predicate function between two HugeInteger operators.
	// return true if the relationship holds, else return false 
	bool isEqualTo(const HugeInteger & obj) const; // is equal to
	bool isNotEqualTo(const HugeInteger &) const; // not equal to
	bool isGreaterThan(const HugeInteger &) const; // greater than
	bool isLessThan(const HugeInteger &) const; // less than
	bool isGreaterThanOrEqualTo(const HugeInteger &) const; // greater than or equal to
	bool isLessThanOrEqualTo(const HugeInteger &) const; // less than or equal
	bool isZero() const; // is zero?// convert a string representing a large integer into a HugeInteger
	void input(const string &);
	// display the HugeInteger, skip leading zeros
	void output();



private:
	vector< short > set;		//vector of short values
	int counter;
	
};

#endif