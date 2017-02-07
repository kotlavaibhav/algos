#include "DataExtractor.cpp"

int main() {


	DataExtractor obj;
	vector<pair<string, DataExtractor>> DataExtractors;
	vector<vector<pair<string, DataExtractor>>> races;
	//	obj.recorddata(obj);
	fstream x1;
	x1.open("Results.txt");
	string line;
	obj.getlines(obj, line, x1, DataExtractors, races);
	obj.display(races);

	//cout << regex_search(input, color);


	cout << "Author: Vaibhav Kotla" << endl << endl;
	DataExtractor obj11;

	char x01;

	do {
		cout << "select a choice" << endl;
		cout << "1. record DataExtractor statistics" << endl;
		cout << "2. display" << endl;
		cout << "x exit" << endl;
		cin >> x01;
		switch (x01) {
		case '1':
			obj11.record();
			break;
		case '2':
			//obj11.display(obj11);
			break;

		default:
			cout << "enter a number" << endl;
			break;
		}
	} while (x01 != 'x');
	return 0;
}