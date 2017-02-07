#include "HugeInteger.h"
#include<string>
#include <iostream>
using namespace std;

int main()
{
	long int p = 3363336;
	string number1;
	string number2;


	HugeInteger a((long int)1111111111), e, g, k((long)5555234431), l((long)1342352); //HugeInteger objects and initialization
	HugeInteger m, n, o, q, r, u;
	HugeInteger b((long)111111111);
	HugeInteger c((long int)44444555);
	HugeInteger d("5555555555555555");
	HugeInteger i("5555555555555555555555555555555555555555");	//Huge Integer String
	HugeInteger j("5555555555555555555555555555555555555555");
	HugeInteger h;
	h.output();
	e = a.add(b);	//add a and b

	cout << "HugeInteger Class by Vaibhav " << endl << endl;
	cout << "HugeInteger + HugeInteger";
	cout << endl << "様様様様様様様様様様様" << endl;
	a.output();
	cout << " + ";
	b.output();
	cout << " = ";
	e.output();
	cout << endl << endl;

	e = c.add(p);


	cout << "HugeInteger + int";
	cout << endl << "様様様様様様様様様様様" << endl;
	c.output();
	cout << " + ";
	cout << p << " = ";
	g = c.add(p);
	g.output();
	cout << endl << endl;

	cout << "HugeInteger + string";
	cout << endl << "様様様様様様様様様様様" << endl;
	c.output();
	cout << " + ";
	d.output();
	cout << " = ";
	h = c.add(d);
	h.output();
	cout << endl << endl;

	cout << "HugeInteger + string (overflow test)";
	cout << endl << "様様様様様様様様様様様" << endl;
	i.output();
	cout << " + ";
	j.output();
	cout << " = ";
	h = i.add(j);
	h.output();
	cout << endl << endl;


	cout << "HugeInteger - HugeInteger";
	cout << endl << "様様様様様様様様様様様" << endl;
	k.output();
	cout << " - ";
	l.output();
	cout << " = ";
	m = k.subtract(l);
	m.output();
	cout << endl << endl;




	cout << "HugeInteger - int";
	cout << endl << "様様様様様様様様様様様" << endl;
	c.output();
	cout << " - ";
	cout << p << " = ";
	g = c.subtract(p);
	g.output();
	cout << endl << endl;

	cout << "HugeInteger - string";
	cout << endl << "様様様様様様様様様様様" << endl;
	d.output();
	cout << " - ";
	c.output();
	cout << " = ";
	h = d.subtract(c);
	h.output();
	cout << endl << endl;

	cout << "HugeInteger - string (smaller - larger) test";
	cout << endl << "様様様様様様様様様様様" << endl;
	c.output();
	cout << " - ";
	d.output();
	cout << " = ";
	r = c.subtract(d);
	r.output();
	cout << endl << endl;


	cout << "String input and comparision test" << endl << "様様様様様様様様様様様" << endl << "Enter a string upto 40 values to convert it into a huge integer" << endl;
	cin >> number1;

	n.input(number1);

	cout << "Enter another string of numbers ";
	cout << endl;
	cin >> number2;
	o.input(number2);

	cout << endl << "demonstrating addition";
	cout << endl << "様様様様様様様様様様様" << endl;

	n.output();

	cout << " + ";

	o.output();


	cout << " = ";
	q = n.add(o);

	q.output();

	cout << endl << endl;

	cout << endl << "demonstrating substraction";
	cout << endl << "様様様様様様様様様様様" << endl;

	n.output();

	cout << " - ";

	o.output();


	cout << " = ";
	u = n.subtract(o);

	u.output();

	cout << endl << endl;

	cout << "comparing HugeInteger A and B ";
	cout << endl << "様様様様様様様様様様様" << endl;

	n.output();

	cout << " and ";

	o.output();

	cout << endl << endl;
	if (n.isEqualTo(o))
		cout << "A equal B - true" << endl << endl;
	else
		cout << "A equal B - false" << endl << endl;


	if (n.isNotEqualTo(o))
		cout << "A isnotEqual B - true" << endl << endl;
	else
		cout << "A isnotEqual B - false" << endl << endl;


	if (n.isGreaterThan(o))
		cout << "A isGreaterThan B - true" << endl << endl;
	else
		cout << "A isGreaterThan B - false" << endl << endl;


	if (n.isGreaterThanOrEqualTo(o))
		cout << "A isGreaterThanOrEqual B - true" << endl << endl;
	else
		cout << "A isGreaterThanOrEqual B - false" << endl << endl;


	if (n.isLessThan(o))
		cout << "A isLessThan B - true" << endl << endl;
	else
		cout << "A isLessThan B- false" << endl << endl;


	if (n.isLessThanOrEqualTo(o))
		cout << "A isLessThanOrEqualTo B- true" << endl << endl;
	else
		cout << "A isLessThanOrEqualTo B - False" << endl << endl;
	if (n.isZero())
	{
		cout << "A isZero - true";
		cout << endl << endl;
	}
	else
	{
		cout << "A isZero - false";
		cout << endl << endl;
	}
	if (o.isZero())
		cout << "B isZero - true";
	else
		cout << "B isZero - false";
	cout << endl << endl;


	system("pause");
	return 0;
}