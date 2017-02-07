#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <regex>
#include <unordered_map>
#include <iomanip>  
using namespace std;


class DataExtractor {
private:
	string DataExtractorname;
	vector<string> winplaceandraceno;
	vector<double> pastratings;
	vector<double> pastweight;
	vector<int> winplace;
	vector<int> DataExtractorclass;
	vector<int> bendpositions;
	vector<string> bendpositionsraw;
	vector<double> winnertime;
	vector<double> losertime;
	vector<int> pastracemeters;
	int presentracemeters;
	double presentweight;
	string ptwt;
	vector<pair<string, vector<DataExtractor>>> DataExtractors;
	//vector < pair<string, DataExtractor>> DataExtractor1;
	int ratingh;
	double Total;
	int onebestpoint;
	int bendtofinalpoint;
public:
	DataExtractor();
	~DataExtractor();
	DataExtractor(int size);
	void display(vector<vector<pair<string, DataExtractor>>>& races2);
	vector<int> split(string track);
	vector<double> split1(string x);
	vector<string> splitstring(string line);
	vector<string> splitstringdetails(string line);
	int romanToInt(string s);
	void extractintoReadData(vector<vector<pair<string, DataExtractor>>>& races2);
	void recorddata(DataExtractor& obj, string& line, fstream& x1, vector<pair<string, DataExtractor>>& DataExtractors2, vector<vector<pair<string, DataExtractor>>>& races2);
	//vector< vector<pair<string,DataExtractor>>> races;
	void getlines(DataExtractor& obj, string& line, fstream& x1, vector<pair<string, DataExtractor>>& DataExtractors2, vector<vector<pair<string, DataExtractor>>>& races2);
};
