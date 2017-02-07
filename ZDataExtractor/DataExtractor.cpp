#include "DataExtractor.h"

DataExtractor::DataExtractor() {

}
DataExtractor::~DataExtractor() {

}
DataExtractor::DataExtractor(int size) {

}
int DataExtractor::romanToInt(string s)
{
	unordered_map<char, int> T = { { 'I' , 1 },
	{ 'V' , 5 },
	{ 'X' , 10 },
	{ 'L' , 50 },
	{ 'C' , 100 },
	{ 'D' , 500 },
	{ 'M' , 1000 } };

	int sum = T[s.back()];
	for (int i = s.length() - 2; i >= 0; --i)
	{
		if (T[s[i]] < T[s[i + 1]])
		{
			sum -= T[s[i]];
		}
		else
		{
			sum += T[s[i]];
		}
	}

	return sum;
}


vector<double> DataExtractor::split1(string x) {	//splits a string into a vector of double values

	stringstream iss;
	vector<double> elems;
	iss.str(x);
	std::string item;
	while (getline(iss, item, ',')) {
		elems.push_back(stod(item));
	}
	return elems;
}
vector<int> DataExtractor::split(string track) {	//splits a string into a vector of int values
	stringstream iss;
	vector<int> elems;
	iss.str(track);
	std::string item;
	while (getline(iss, item, ',')) {
		elems.push_back(stoi(item));
	}
	return elems;
}
vector<string> DataExtractor::splitstring(string line) {
	stringstream iss;
	vector<string> elems;
	iss.str(line);
	std::string item;
	while (getline(iss, item, ',')) {
		elems.push_back(item);
	}
	return elems;
}
vector<string> DataExtractor::splitstringdetails(string line) {
	stringstream iss;
	vector<string> elems;
	iss.str(line);
	std::string item;
	while (getline(iss, item, ' ')) {
		elems.push_back(item);
	}
	return elems;
}

smatch sm;	// match for a regular expression
//regex expre("^(\\d{1})\\.\\s(.*?)\\s\\d+\\s|^(\\d{2})\\.\\s(.*?)\\s\\d+\\s");
regex expre("^(\\d{1})\\.\\s(.*?)\\s(\\d{2}\\.?\\d?)\\s?|^(\\d{2})\\.\\s(.*?)\\s(\\d{2}\\.?\\d?)\\s?");	// expression to extract numbers from string during parsing
regex extractnames("(\\d{1}\\.\\s.*?)(\\d+|\\.?).*?\\s(\\d{2}\\.?\\d?)\\s|(\\d{2}\\.\\s.*?)(\\d+|\\.?).*?\\s(\\d{2}\\.?\\d?)\\s");
regex expre2("^\\d{1}\\.$|^\\d{2}\\.$");
regex expre3("^1.\\s");
regex expre4("^1.$");
regex expremain("No\\.\\d{2}\\.\\..*(\\d{4})|No\\.\\d{3}\\..*(\\d{4})|\\dNo\\.\\d+.*(\\d{4})|\\dNo\\.\\d+");
regex expreabbre("ABBREVIATIONS");
string fin;
string line2;
streampos oldpos;
streampos oldpos2;
streampos oldpos3;
streampos oldpos5;
streampos oldpos4andhalf;
streampos start1;


void DataExtractor::extractintoReadData(vector<vector<pair<string, DataExtractor>>>& FileDatas2) {
	regex ex1("\\s\\d+|^\\d+|,\\d+");
	regex ex2("\\(\\d+\\)");
	smatch s1;
	int i = FileDatas2.size() - 1;
	for (int j = 0;j < FileDatas2[i].size();j++) {
		string x = FileDatas2[i][j].second.ptwt;
		regex pt("[A-Z]?[a-z]+?");// extract if it matches A-Z or small a-z
		regex htwt("H.Wt-\\s(.*)");	//extracts string if it matches anything followed by H.Wt.
		regex directptwt("(?=)(\\d+\\-.*)"); // positive lookahead to head a number followed by - followed by anything
		regex pt2("[A-Z]+,[A-Z]+,[A-Z]+");
		smatch level1;
		smatch level2;
		string temphtwt;
		vector<string> FileDatano;
		FileDatano = splitstring(x);
		if (regex_search(x, level1, htwt)) {
			 temphtwt = level1.str(1);
			 x = temphtwt;
			 FileDatano = splitstring(temphtwt);
			
		}
		if (regex_search(x, level1, pt)||regex_search(x,level1,pt2)) {
			if (regex_search(x, level2, directptwt)) {
				x = level2.str(1);
				FileDatano.clear();
				FileDatano = splitstring(x);
			}
			else {
				FileDatano.erase(FileDatano.begin());
			}
		}

		for (int k = 0;k < FileDatano.size();k++) {

			string y = FileDatas2[i][j].second.winplaceandFileDatano[k];

			if (regex_search(y, s1, ex2)) {
				y.erase(y.begin());
				y.erase(y.end() - 1);
				//	cout << 1 << endl;
				FileDatas2[i][j].second.winplace.push_back(1);
			}
			else {
				smatch s2;
				string line = FileDatano[k];
				regex ex1("\\d+");
				if (regex_search(line, s2, ex1)) {
					string line2 = s2.str(0);
					int location = line2.size();
					for (int p = 0;p < line2.size();p++) {
						if (line2[p] != y[p])
							break;
					}
					y.erase(y.begin(), y.begin() + location);
					//	cout << "location " <<  y << endl;
					if (y == "dq" || y == "rd" || y == "upl"||y=="ns") {
						FileDatas2[i][j].second.winplace.push_back(0);
					}
					else {
						FileDatas2[i][j].second.winplace.push_back(stoi(y));
					}
				}

			}

		}
	}
		

}

void DataExtractor::recorddata(DataExtractor& obj, string& line, fstream& x1, vector<pair<string, DataExtractor>>& DataExtractors2, vector<vector<pair<string, DataExtractor>>>& FileDatas2) {
	vector<DataExtractor> inputdata;

	while (getline(x1, line)) {
		if (regex_search(line, sm, expremain)||regex_search(line, sm, expreabbre)) {
			cout << endl;
			//start1 = x1.tellg();
			x1.seekg(oldpos);
			DataExtractors.push_back(make_pair(obj.DataExtractorname, inputdata));
			DataExtractors2.push_back(make_pair(obj.DataExtractorname, obj));

			
				cout << endl;							//end of FileData and starts next number 1.
				FileDatas2.push_back(DataExtractors2);
				DataExtractors2.clear();
				obj.extractintoReadData(FileDatas2);
			
			//	cout << endl;
			/*smatch s10;
			regex temp("\\dNo\\.\\d+");

			cout << endl << sm.str(3);
			if (sm.str(3) == "") {
				if (regex_search(line, s10, temp)) {
					getline(x1, line);
					cout << line;
					cout << s10.str(5);
				}
			}
			else {
				cout << line;
			}
			*/
			return;
		}
		if (regex_search(line, sm, expre2)) {
			inputdata.push_back(obj);
			DataExtractors.push_back(make_pair("x", inputdata));
			DataExtractors2.push_back(make_pair("x", obj));
			if (regex_search(line, sm, expremain)) {
				cout << endl;						// end of FileData and start of next FileData number 1.
				FileDatas2.push_back(DataExtractors2);
				DataExtractors2.clear();
			}
			x1.seekg(oldpos);

			return;
		}
		
		if (regex_search(line, sm, expre) || regex_search(line, sm, expreabbre)) {
			inputdata.push_back(obj);

			DataExtractors.push_back(make_pair(obj.DataExtractorname, inputdata));
			DataExtractors2.push_back(make_pair(obj.DataExtractorname, obj));

			if (regex_search(line, sm, expre3)) {
				cout << endl;							//end of FileData and starts next number 1.
				FileDatas2.push_back(DataExtractors2);
				DataExtractors2.clear();
				obj.extractintoReadData(FileDatas2);
			}
			//	cout << endl;

			x1.seekg(oldpos);

			return;
		}
		else {
			
			if (line != "") {
				regex rating("R\\s(\\d{1})\\d\\d?\\/|R\\s(\\d{2})|R\\s\(\\d{3})|R\\s\(\\d{3})$|R\\s(\\d{1})\\s"); // extracts the rate of the element following his regex pattern
				//regex winprefix("(?=)H\.Wt-(.*?)[A-Za-z]");
				//regex winprefix("(?=)H.Wt-(.*?)[A-Za-z]|(?=)H.Wt-(.*?)\\s?(.*)");
				regex winprefix("(?=)H.Wt-\\s((.*?))\\s[A-Za-z]|(?=)H.Wt-\\s(.*?)$\\s?(.*)|H.Wt-\\s(.*)");
				//regex winplace("\\d+[FMJASOND][aepuoc][nbrynlgptvc]$|\\d+[FMJASOND][aepuoc][nbrynlgptvc]\\s");
				regex winplace("\\d+[FMJASOND][aepuoc][nbrynlgptvc][e]?[w]?[n]?|\\d+[FMJASOND][aepuoc][nbrynlgptvc]\\s|\\d+[FMJASOND][aepuoc][nbrynlgptvc][e]?[w]?[x]?");
				//regex winprefexline2("(^\\d.\\d+)|(^\\d+)");
				regex winprefexline2("(^[1-9][0-9]+\\.\\d+)|(^[1-9]\\.\\d+)|(^[1-9][0-9][0-9]?\\-)|(^[0-9]\\/)|(^\\,\\s[1-9][0-9]+\\-)|(^\\d+\\-\\d\\/)|(^\\d\\-\\d\\.)");
				regex winprefexline2special("H.Wt\\-$");
				smatch s1;
				smatch s3;
				smatch s4;
				smatch s17;
				if (regex_search(line, s1, rating)) {
					if (regex_search(line, s4, winprefix)) {
						//cout << s4.str(1) << endl; //winprefix match line 1
						obj.ptwt += s4.str(1);

					}
					smatch s2;
					regex ratingextract("R\\s(\\d{1})\\s\\d?\\/|R\\s(\\d{2}|\\d{3})\\s|R\\s\(\\d{3}|\\d{2})$|R\\s(\\d{1})\\s\\d?"); // this leads into s2.str(1)="" if block;
					regex ratingextract111("R\\s(\\d{2}|\\d{3})\\s|R\\s\(\\d{3}|\\d{2})$|R\\s(\\d{1})\\s\\d?"); // previous ratingextract which leads into winprefexline2;
					regex_search(line, s2, ratingextract);
					if (s2.str(1) == "") {
						cout << "Rating:" << s2.str(2) << endl << endl;
						smatch ratingtemp1;
						regex ratingtempreg1("R\\s(\\d{1})\\s\\d?");
						if (regex_search(line, ratingtemp1, ratingtempreg1)) {
							obj.ratingh = stoi(ratingtemp1.str(1));
						}
						else {
							if (s2.str(2) == "") {
								obj.ratingh = (stoi(s2.str(3)));
								break;
							}

							obj.ratingh = (stoi(s2.str(2)));
						}
						regex lastrunday("(\\d+\\/\\d+)$");
						smatch lastrun;
						regex_search(line, lastrun, lastrunday);
						cout << lastrun.str(1);
						oldpos4andhalf = x1.tellg();
						getline(x1, line);
						while (line == "") {
							getline(x1, line); //winprefix line 2
						}
							if (regex_search(line, s4, winprefexline2)) {

							//	cout << line << endl;
							obj.ptwt += line;
							oldpos5 = x1.tellg();
							getline(x1, line);
							while (line == "") {
								getline(x1, line);
							}
							if (regex_search(line, s4, winprefexline2)) {
								//	cout << line << endl;
								obj.ptwt += line;
							}
							else {
								x1.seekg(oldpos5);
							}
							oldpos5 = x1.tellg();
							getline(x1, line);
							while (line == "") {
								getline(x1, line);
							}
							if (regex_search(line, s4, winprefexline2)) {
								//		cout << line << endl;
								obj.ptwt += line;
							}
							else {
								x1.seekg(oldpos5);
										}
								}
							else {
								x1.seekg(oldpos4andhalf);
							}
						}

					else {

						cout << "Rating:" << s2.str(1) << endl << endl;
						regex lastrunday1("(\\d+\\/\\d+)$");//lastrunday
						smatch lastrun1;
						regex_search(line, lastrun1, lastrunday1);
						cout << lastrun1.str(1);
						obj.ratingh= (stoi(s2.str(1)));
						oldpos4andhalf = x1.tellg();
						getline(x1, line);
						while (line == "") {
							getline(x1, line); //winprefix line 2
						}
						if (regex_search(line, s4, winprefexline2)) {

						//	cout << line << endl;
							obj.ptwt += line;
							oldpos5 = x1.tellg();
							getline(x1, line);
							while (line == "") {
								getline(x1, line);
							}
							if (regex_search(line, s4, winprefexline2)) {
							//	cout << line << endl;
								obj.ptwt += line;
							}
							else {
								x1.seekg(oldpos5);
							}
							oldpos5 = x1.tellg();
							getline(x1, line);
							while (line == "") {
								getline(x1, line);
							}
							if (regex_search(line, s4, winprefexline2)) {
						//		cout << line << endl;
								obj.ptwt += line;
							}
							else {
								x1.seekg(oldpos5);
							}
						}
						else {
							x1.seekg(oldpos4andhalf);
						}
					}
					//cout << obj.ptwt << endl;
				}
		
				else if (regex_search(line, s3, winplace)) {
					//getline(x1, line);
				/*	regex xEV("xEv\\.\\s(.*)");
					if (regex_search(line, s3, xEV)) {
						cout << "winplace: " << s3.str(1) << endl;
						obj.winplaceandFileDatano.push_back(s3.str(1));
						getline(x1, line);
						cout << line << endl;
						o
					}
					*/
					
						//regex help("\\((\\d+)\\)|(?=)\\s([0-9][0-9][0-9]?[0-9]?)|^[0-9]+$");
					regex help("(\\d+[FMJASOND][aepuoc][nbrynlgptvc])\\s(.*?)\\s(.*)");
					regex help2("(\\d+[FMJASOND][aepuoc][nbrynlgptvc]ewn\\d?\\d?\\??\\d?)\\s(.*?)\\s(.*)");
					
					smatch s3ewn;
					smatch s3ewx;
						if (regex_search(line, s3, help)|| regex_search(line, s3ewn, help2)) {
							//cout << "winplace: " << s3.str(3) << endl;
							vector<string> arr1;
							string temp;
							string temp14;
							if (regex_search(line, s3ewn, help2)) {
								string win = s3ewn.str(2);
								
								temp = s3ewn.str(3);
								
								
							}
							else {
								temp = s3.str(3);
								regex tempmonth("m");
								smatch m;
								vector<string> temparray;
								temparray = splitstringdetails(temp);
								if (regex_search(temparray[0], m, tempmonth)) {
									temp14 = s3.str(2);
									temp14 = temp14 + " ";
									temp14 = temp14 + temp;
									temp = temp14;
								}
								
								if (temp.size() > 0) {
									if (temp[0] == ' ') {
										temp.erase(temp.begin());
									}
								}
								arr1 = splitstringdetails(temp);
								
								

							}
							
							obj.winplaceandFileDatano.push_back(arr1[0]);
							
							
							regex metersandroman("(\\d+)m(.*)");
							smatch s9;
							string temp2 = arr1[1];
							regex_search(temp2, s9, metersandroman);
							string temp3 = s9.str(1);
							temp3.push_back('0'); 
							temp3.push_back('0');
							int meters = stoi(temp3);
							obj.pastFileDatameters.push_back(meters);
							int FileDataclass = romanToInt(s9.str(2));
							obj.DataExtractorclass.push_back(FileDataclass);
							 temp3 = arr1[2];
							obj.pastweight.push_back(stod(temp3));
							string temp4 = arr1[3];
							if (temp4 == "-") {
								obj.pastratings.push_back(0);
							}
							else {
								obj.pastratings.push_back(stoi(temp4));
							}
							 temp4 = arr1[4];
							string temp5 = arr1[5];
							regex timeorLS("\\d-(\\d+?(\\.|\\-)\\d+)");
							smatch timeorLS1;
							regex looserextract("(\\d{2}.\\d+).*");
							if (regex_search(temp5, timeorLS1, timeorLS)) {
								obj.winnertime.push_back(stod(timeorLS1.str(1)));

								string temp6 = arr1[6];
								regex_search(temp6, timeorLS1, looserextract);
								if (timeorLS1.str(1) == "") {
									obj.losertime.push_back(0);
									

								}
								else {
									obj.losertime.push_back(stod(timeorLS1.str(1)));
									//for(auto x:obj.losertime)
									//cout << x;
								}
								string rawbendposition = arr1[9];
								regex rawbendregex("[A-Z][a-z]+|[A-Z]+");
								smatch raw1;
								if (regex_search(rawbendposition, raw1, rawbendregex)) {
									string tempbeforerawbend = arr1[8];
									smatch rawbendbeforearr9;
									regex bendbefore("(^\\d+$)");
										if (regex_search(tempbeforerawbend, rawbendbeforearr9, bendbefore)) {
											obj.bendpositionsraw.push_back(rawbendbeforearr9.str(1));
										}
										else {
											obj.bendpositionsraw.push_back("0");
										}
								}
								else {
									obj.bendpositionsraw.push_back(rawbendposition);
								}
							}
							else {
								string temp6 = arr1[6];
								regex_search(temp6, timeorLS1, timeorLS);
								obj.winnertime.push_back(stod(timeorLS1.str(1)));
								string temp7 = arr1[7];
								regex_search(temp7, timeorLS1, looserextract);
								//asdfasdf
								obj.losertime.push_back(stod(timeorLS1.str(1)));
								string rawbendposition = arr1[10];
								regex rawbendregex("[A-Z][a-z]+|[A-Z]+");
								smatch raw1;
								if (regex_search(rawbendposition, raw1, rawbendregex)) {
									string tempbeforerawbend = arr1[9];
									smatch rawbendbeforearr9;
									regex bendbefore("(^\\d+$)");
									if (regex_search(tempbeforerawbend, rawbendbeforearr9, bendbefore)) {
										obj.bendpositionsraw.push_back(rawbendbeforearr9.str(1));
									}
									else {
										obj.bendpositionsraw.push_back("0");
									}
								}
								else {
									obj.bendpositionsraw.push_back(rawbendposition);
								}
								
							}
							
						//	regex_search()
						}
						else {
							getline(x1, line);
							cout << "winplace: " << line << endl;
							obj.winplaceandFileDatano.push_back(line);
							getline(x1, line);
							cout << line << endl;

						}
					
				}
			}
		}
		oldpos = x1.tellg();
	}

	//string name;
	//DataExtractors.push_back(make_pair(name, inputdata));
	//FileDatas.push_back(make_pair(1, obj.DataExtractors));


}
void DataExtractor::getlines(DataExtractor& obj, string& line, fstream& x1, vector<pair<string, DataExtractor>>& DataExtractors, vector<vector<pair<string, DataExtractor>>>& FileDatas) {

	while (getline(x1, line)) {
		DataExtractor obj12;
		smatch abb;
		if (regex_search(line, sm, expremain)||regex_search(line,abb,expreabbre)) {
			if (regex_search(line, abb, expreabbre)) {
				return;
			}
			cout << endl;
			obj.presentFileDatameters = 0;
			smatch s10;
			regex temp("\\dNo\\.\\d+");

			cout << sm.str(3);
			if (sm.str(3) == "") {
				if (regex_search(line, s10, temp)) {
					getline(x1, line);
					//cout << line;
					regex temp12("\\d{4}");
					regex_search(line, s10, temp12);
					cout << s10.str(0);
					obj.presentFileDatameters = stoi(s10.str(0));

				}
			}
			else {
				//cout << line;
				int presentm = stoi(sm.str(3));
				obj.presentFileDatameters = presentm;
				
			}
		}
		if (regex_search(line, sm, expre2)) {
			cout << endl << line;


		}
		else if (regex_search(line, sm, expre)) {
			cout << endl << sm.str(0) << endl;
			string line2 = sm.str(0);
			regex nameofDataExtractor("(\\d+\\.\\s[A-Z]+\\s?[A-Z]+\\s?[A-Z]+?)");
			smatch namesm;
			regex_search(line2, namesm, nameofDataExtractor);
			obj12.DataExtractorname = namesm.str(1);
			regex weight1("\\d{2}$|\\d{2}\\s$|\\d{2}\\.\\d{1}\\s$|\\d{2}\\.\\d{1}\\s?");
			smatch w1;
			regex_search(line2, w1, weight1);
			obj.presentweight = stod(w1.str(0));
			//obj.recorddata(obj);

		}
		oldpos2 = x1.tellg();
		if (regex_search(line, sm, expre) || regex_search(line, sm, expre2)) {
			fin = "";
			if (regex_search(line, sm, expre2)) {

				getline(x1, line);
				cout << line << endl;
			}
			double presentm = obj.presentFileDatameters;
			double presentw = obj.presentweight;
			obj12.presentFileDatameters = presentm;
			obj12.presentweight = presentw;
			obj.recorddata(obj12, line, x1, DataExtractors, FileDatas);
			
			obj.presentweight = 0;

		}
		else {

		}
	}

}
void DataExtractor::display(vector<vector<pair<string, DataExtractor>>>& FileDatas2) {

	//vector<DataExtractor> results;
	//results.push_back(obj);

	if (DataExtractors.size() < 1) {
		cout << "Please enter a record and try again" << endl;
		return;
	}


	ofstream file;
	file.open("result.txt");
	//cout << "name" << "    " << "rating" << "   " << "weight" << endl;
	const char separator = ' ';
	//cout << std::setprecision(2);
	int nameWidth = 6;
	int numWidth = 6; 
	int ratingchangetotal = 0;
	double weightchangetotal = 0;
	int bpminuswptotal = 0;
	bool highbend = false;
	bool weight8andhalf = false;
	cout << endl << endl;
	for (int i = 0;i < FileDatas2.size();i++) {
		for (int j = 0;j < FileDatas2[i].size();j++) {
			ratingchangetotal = 0;
			weightchangetotal = 0;
			bpminuswptotal = 0;
			 highbend = false;
			 weight8andhalf = false;
			 cout << left << setw(nameWidth) << setfill(separator) << "FileDataNo" << i +1 << "  ";
			 file << left << setw(nameWidth) << setfill(separator) << "FileDataNo" << i +1 << "  ";
			cout << left << setw(nameWidth) << setfill(separator) << "DataExtractor No" << FileDatas2[i][j].first;
			file << left << setw(nameWidth) << setfill(separator) << "DataExtractor No" << FileDatas2[i][j].first;
			cout << left << setw(nameWidth) << setfill(separator) << "  Distance: " <<  FileDatas2[i][j].second.presentFileDatameters << endl;
			file << left << setw(nameWidth) << setfill(separator) << "  Distance: " <<  FileDatas2[i][j].second.presentFileDatameters << endl;

			cout << left << setw(nameWidth) << setfill(separator) << "Dist  ";
			file << left << setw(nameWidth) << setfill(separator) << "Dist  ";

			cout << left << setw(nameWidth) << setfill(separator) << "   bp-wp(b-w)";
			file << left << setw(nameWidth) << setfill(separator) << "   bp-wp(b-w)";

		//	cout << left << setw(nameWidth) << setfill(separator) << "wp";
		//	file << left << setw(nameWidth) << setfill(separator) << "wp";

		//	cout << left << setw(nameWidth) << setfill(separator) << "(b-w)";
		//	file << left << setw(nameWidth) << setfill(separator) << "(b-w)";

			cout << "   " <<left << setw(nameWidth) << setfill(separator) << " wintime";
			file << "   " << left << setw(nameWidth) << setfill(separator) << " wintime";

			cout << "   " << left << setw(nameWidth) << setfill(separator) << "lt-wt ";
			file << "   " << left << setw(nameWidth) << setfill(separator) << "lt-wt ";

			cout << "   " << left << setw(nameWidth) << setfill(separator) << " ratingc";
			file << "   " << left << setw(nameWidth) << setfill(separator) << " ratingc";

			cout << "   " << left << setw(nameWidth) << setfill(separator) << " weightc";
			file << "   " << left << setw(nameWidth) << setfill(separator) << " weightc";

			cout << "   " << left << setw(nameWidth) << setfill(separator) << " points";
			file << "   " << left << setw(nameWidth) << setfill(separator) << " points";
			cout << endl << endl;
			file << endl << endl;
			int tempkstartlocater = FileDatas2[i][j].second.bendpositions.size() - 3;
			
			if (tempkstartlocater < 0) {
				tempkstartlocater = 0;
			}
		//	int k = FileDatas2[i][j].second.bendpositions.size() - 3;
				for (int k = 0;k < FileDatas2[i][j].second.bendpositions.size();k++) {
					
					if (FileDatas2[i][j].second.pastratings[k] == 0) {
						ratingchangetotal = 0;
					}
					if (k > 0) {
						/*if (FileDatas2[i][j].second.pastratings[k - 1] != 0 && k != 0 && k!=tempkstartlocater) {
							ratingchangetotal += FileDatas2[i][j].second.pastratings[k] - FileDatas2[i][j].second.pastratings[k - 1];
						}
						*/
						if (FileDatas2[i][j].second.pastratings[k - 1] != 0 && k != 0) {
							ratingchangetotal += FileDatas2[i][j].second.pastratings[k] - FileDatas2[i][j].second.pastratings[k - 1];
						}
					}

					if (FileDatas2[i][j].second.pastweight[k] != 0 && k != 0) {
						weightchangetotal += FileDatas2[i][j].second.pastweight[k] - FileDatas2[i][j].second.pastweight[k - 1];
					}
					cout << setw(numWidth) << setfill(separator) << FileDatas2[i][j].second.pastFileDatameters[k];
					file << setw(numWidth) << setfill(separator) << FileDatas2[i][j].second.pastFileDatameters[k];

					cout << "    "  << FileDatas2[i][j].second.bendpositions[k];
					file << "    " << FileDatas2[i][j].second.bendpositions[k];
					
					cout << "-" << FileDatas2[i][j].second.winplace[k];
					file << "-"  << FileDatas2[i][j].second.winplace[k];

					double bpminuswp = FileDatas2[i][j].second.bendpositions[k] - FileDatas2[i][j].second.winplace[k];

					bpminuswptotal += bpminuswp;
					if ((FileDatas2[i][j].second.bendpositions[k]>9) && (FileDatas2[i][j].second.winplace[k] > 9)) {
						if (bpminuswp >= 0) {
							if (bpminuswp > 5) {
								highbend = true;
								
								cout << "(+" << bpminuswp << setw(nameWidth-1) << setfill(separator) << "*)";
								file << "(+" << bpminuswp << setw(nameWidth-1) << setfill(separator) << "*)";
							}
							else {
								cout << "(+" << bpminuswp << setw(nameWidth - 2) << setfill(separator) << ")";
								file << "(+" << bpminuswp << setw(nameWidth - 2) << setfill(separator) << ")";
							}

						}
						else {
							cout << "(" << bpminuswp << setw(nameWidth-2) << setfill(separator) << ")";
							file << "(" << bpminuswp << setw(nameWidth-2) << setfill(separator) << ")";

						}

					}
					else if ((FileDatas2[i][j].second.bendpositions[k] > 9) || (FileDatas2[i][j].second.winplace[k] > 9)) {
						if (bpminuswp >= 0) {
							if (bpminuswp > 5) {
								highbend = true;
								cout << "(+" << bpminuswp << setw(nameWidth-1) << setfill(separator) << "*)";
								file << "(+" << bpminuswp << setw(nameWidth-1) << setfill(separator) << "*)";
							}
							else {
								cout << "(+" << bpminuswp << setw(nameWidth - 1) << setfill(separator) << ")";
								file << "(+" << bpminuswp << setw(nameWidth - 1) << setfill(separator) << ")";
							}
						}
						else {
							cout << "(" << bpminuswp << setw(nameWidth-1) << setfill(separator) << ")";
							file << "(" << bpminuswp << setw(nameWidth-1) << setfill(separator) << ")";

						}
					}
					else {
						if (bpminuswp >= 0) {
							if (bpminuswp > 5) {
								highbend = true;
								cout << "(+" << bpminuswp << setw(nameWidth) << setfill(separator) << "*)";
								file << "(+" << bpminuswp << setw(nameWidth) << setfill(separator) << "*)";
							}
							else {
								cout << "(+" << bpminuswp << setw(nameWidth) << setfill(separator) << ")";
								file << "(+" << bpminuswp << setw(nameWidth) << setfill(separator) << ")";
							}
						}
						else {
							cout << "(" << bpminuswp << setw(nameWidth) << setfill(separator) << ")";
							file << "(" << bpminuswp << setw(nameWidth) << setfill(separator) << ")";

						}
					}
					


					std::cout << fixed << std::setprecision(2);
					file << fixed << setprecision(2);

					cout << "  " << setw(nameWidth-1) << setfill(separator) << FileDatas2[i][j].second.winnertime[k];
					file << "  " << setw(nameWidth-1) << setfill(separator) << FileDatas2[i][j].second.winnertime[k];

					double temp = FileDatas2[i][j].second.losertime[k] - FileDatas2[i][j].second.winnertime[k];
					
					//std::cout << fixed << std::setprecision(2);
					if (-temp == FileDatas2[i][j].second.winnertime[k])
					{
						cout << "    " << left << setw(nameWidth) << setfill(separator) << "NULL";
						file << "    " << left << setw(nameWidth) << setfill(separator) << "NULL";
					}
					else if (temp < 0) {
						cout << "    " << left << setw(nameWidth) << setfill(separator) << FileDatas2[i][j].second.winnertime[k] + temp;
						file << "    " << left << setw(nameWidth) << setfill(separator) << FileDatas2[i][j].second.winnertime[k]+ temp;
					}
					else {
						cout << "    " << left << setw(nameWidth) << setfill(separator) << temp;
						file << "    " << left << setw(nameWidth) << setfill(separator) << temp;
					}
					std::cout << fixed << std::setprecision(0);
					file << fixed << std::setprecision(0);

					if (k != FileDatas2[i][j].second.pastratings.size()-1) {
						int tempratingchange = FileDatas2[i][j].second.pastratings[k+1] - FileDatas2[i][j].second.pastratings[k];
						if ((tempratingchange >= 0)) {			//	+4
							if (tempratingchange > 9) {
								if (FileDatas2[i][j].second.pastratings[k] > 9) { //  11(+11)
									if (tempratingchange == 4) {
										cout << "    " << FileDatas2[i][j].second.pastratings[k] << "(+" << tempratingchange << left << setw(nameWidth) << setfill(separator) << "*)";
										file << "    " << FileDatas2[i][j].second.pastratings[k] << "(+" << tempratingchange << left << setw(nameWidth) << setfill(separator) << "*)";
									}
									else {
										cout << "    " << FileDatas2[i][j].second.pastratings[k] << "(+" << tempratingchange << left << setw(nameWidth - 1) << setfill(separator) << ")";
										file << "    " << FileDatas2[i][j].second.pastratings[k] << "(+" << tempratingchange << left << setw(nameWidth - 1) << setfill(separator) << ")";
									}
								}
								else {
									if (tempratingchange == 4) {
										cout << "    " << FileDatas2[i][j].second.pastratings[k] << "(+" << tempratingchange << left << setw(nameWidth) << setfill(separator) << "*)";
										file << "    " << FileDatas2[i][j].second.pastratings[k] << "(+" << tempratingchange << left << setw(nameWidth) << setfill(separator) << "*)";
									}
									else {
										cout << "    " << FileDatas2[i][j].second.pastratings[k] << "(+" << tempratingchange << left << setw(nameWidth) << setfill(separator) << ")";
										file << "    " << FileDatas2[i][j].second.pastratings[k] << "(+" << tempratingchange << left << setw(nameWidth) << setfill(separator) << ")";
									}
								}
							}
							else {
								if (FileDatas2[i][j].second.pastratings[k] > 9) {
									if (tempratingchange == 4) {
										cout << "    " << FileDatas2[i][j].second.pastratings[k] << "(+" << tempratingchange << left << setw(nameWidth) << setfill(separator) << "*)";
										file << "    " << FileDatas2[i][j].second.pastratings[k] << "(+" << tempratingchange << left << setw(nameWidth) << setfill(separator) << "*)";
									}
									else {
										cout << "    " << FileDatas2[i][j].second.pastratings[k] << "(+" << tempratingchange << left << setw(nameWidth) << setfill(separator) << ")";
										file << "    " << FileDatas2[i][j].second.pastratings[k] << "(+" << tempratingchange << left << setw(nameWidth) << setfill(separator) << ")";
									}
								}
								else {
									if (tempratingchange == 4) {
										cout << "    " << FileDatas2[i][j].second.pastratings[k] << "(+" << tempratingchange << left << setw(nameWidth) << setfill(separator) << "*)";
										file << "    " << FileDatas2[i][j].second.pastratings[k] << "(+" << tempratingchange << left << setw(nameWidth) << setfill(separator) << "*)";
									}
									else {
										cout << "    " << FileDatas2[i][j].second.pastratings[k] << "(+" << tempratingchange << left << setw(nameWidth + 1) << setfill(separator) << ")";
										file << "    " << FileDatas2[i][j].second.pastratings[k] << "(+" << tempratingchange << left << setw(nameWidth + 1) << setfill(separator) << ")";
									}
								}
								
							}
						}
						else {
							if (FileDatas2[i][j].second.pastratings[k] > 9) {
								cout << "    " << FileDatas2[i][j].second.pastratings[k] << "(" << tempratingchange << left << setw(nameWidth) << setfill(separator) << ")";
								file << "    " << FileDatas2[i][j].second.pastratings[k] << "(" << tempratingchange << left << setw(nameWidth) << setfill(separator) << ")";
							}
							else {
								cout << "    " << FileDatas2[i][j].second.pastratings[k] << "(" << tempratingchange << left << setw(nameWidth+1) << setfill(separator) << ")";
								file << "    " << FileDatas2[i][j].second.pastratings[k] << "(" << tempratingchange << left << setw(nameWidth+1) << setfill(separator) << ")";
							}
						}
					}
					else {
						int tempratingchange = FileDatas2[i][j].second.ratingh - FileDatas2[i][j].second.pastratings[k];
						if ((tempratingchange >= 0)) {
							if (tempratingchange > 9) {
								cout << "    " << FileDatas2[i][j].second.pastratings[k] << "(+" << tempratingchange << left << setw(nameWidth - 1) << setfill(separator) << ")";
								file << "    " << FileDatas2[i][j].second.pastratings[k] << "(+" << tempratingchange << left << setw(nameWidth - 1) << setfill(separator) << ")";
							}
							else {
								if (tempratingchange == 4) {
									cout << "    " << FileDatas2[i][j].second.pastratings[k] << "(+" << tempratingchange << left << setw(nameWidth-1) << setfill(separator) << "*)";
									file << "    " << FileDatas2[i][j].second.pastratings[k] << "(+" << tempratingchange << left << setw(nameWidth-1) << setfill(separator) << "*)";
								}
								else {
									cout << "    " << FileDatas2[i][j].second.pastratings[k] << "(+" << tempratingchange << left << setw(nameWidth) << setfill(separator) << ")";
									file << "    " << FileDatas2[i][j].second.pastratings[k] << "(+" << tempratingchange << left << setw(nameWidth) << setfill(separator) << ")";
								}
							}
						}
						else {
							if (FileDatas2[i][j].second.pastratings[k] > 9) {


								cout << "    " << FileDatas2[i][j].second.pastratings[k] << "(" << tempratingchange << left << setw(nameWidth) << setfill(separator) << ")";
								file << "    " << FileDatas2[i][j].second.pastratings[k] << "(" << tempratingchange << left << setw(nameWidth ) << setfill(separator) << ")";
							}
							else
							{

								cout << "    " << FileDatas2[i][j].second.pastratings[k] << "(" << tempratingchange << left << setw(nameWidth +1) << setfill(separator) << ")";
								file << "    " << FileDatas2[i][j].second.pastratings[k] << "(" << tempratingchange << left << setw(nameWidth +1) << setfill(separator) << ")";
							}
						}
						
					}
					file << fixed << setprecision(1);
						if (k != 0) {
							if ((FileDatas2[i][j].second.pastweight[k] - FileDatas2[i][j].second.pastweight[k - 1]) >= 0) {
								cout << FileDatas2[i][j].second.pastweight[k] << "(+" << FileDatas2[i][j].second.pastweight[k] - FileDatas2[i][j].second.pastweight[k - 1] << setw(nameWidth) << setfill(separator) << ")";
								file << FileDatas2[i][j].second.pastweight[k] << "(+" << FileDatas2[i][j].second.pastweight[k] - FileDatas2[i][j].second.pastweight[k - 1] << setw(nameWidth) << setfill(separator) << ")";
								double tempweight = FileDatas2[i][j].second.pastweight[k] - FileDatas2[i][j].second.pastweight[k - 1];
								if (tempweight == 8.5 || tempweight == -8.5) {
									weight8andhalf = true;
								}
							}
							else {
								cout << FileDatas2[i][j].second.pastweight[k] << "(" << FileDatas2[i][j].second.pastweight[k] - FileDatas2[i][j].second.pastweight[k - 1] << setw(nameWidth) << setfill(separator) << ")";
								file << FileDatas2[i][j].second.pastweight[k] << "(" << FileDatas2[i][j].second.pastweight[k] - FileDatas2[i][j].second.pastweight[k - 1] << setw(nameWidth) << setfill(separator) << ")";
								double tempweight = FileDatas2[i][j].second.pastweight[k] - FileDatas2[i][j].second.pastweight[k - 1];
								if (tempweight == 8.5 || tempweight == -8.5) {
									weight8andhalf = true;
								}
							}
						}
						else {
							cout << FileDatas2[i][j].second.pastweight[k] << "(+0.0)     ";
							file <<  FileDatas2[i][j].second.pastweight[k] << "(+0.0)     ";

						}
						file << fixed << setprecision(0);
						if (k != FileDatas2[i][j].second.bendpositions.size() - 1) {
							double bpminuswp1 = FileDatas2[i][j].second.bendpositions[k] - FileDatas2[i][j].second.winplace[k];

							double temp1 = FileDatas2[i][j].second.losertime[k] - FileDatas2[i][j].second.winnertime[k];

							//std::cout << fixed << std::setprecision(2);
							if (-temp1 == FileDatas2[i][j].second.winnertime[k])
							{
								temp1 = 1000;
							}
							else if (temp1 < 0) {
								
								temp1 =  FileDatas2[i][j].second.winnertime[k] + temp1;
							}
							else {
								
								
							}
							//(50 - 10 * bp) + (50 - 10 * wp) + 10 * ratingC
							double percent1 = (100 - (100 * temp1));
							double ratingc1 = FileDatas2[i][j].second.pastratings[k + 1] - FileDatas2[i][j].second.pastratings[k];
							double wc1 = (2 * (FileDatas2[i][j].second.pastweight[k + 1] - FileDatas2[i][j].second.pastweight[k]));
							double Points = (bpminuswp1*10) + percent1 + +(ratingc1 *10)+ wc1;
								
							if (Points >= 0) {
								cout << "+" << Points;
								file << "+" << Points;
							}
							else {
								cout << setw(nameWidth) << setfill(separator) << Points;
								file << setw(nameWidth) << setfill(separator) << Points;
							}
						}
						else {
							double bpminuswp1 = FileDatas2[i][j].second.bendpositions[k] - FileDatas2[i][j].second.winplace[k];

							double temp1 = FileDatas2[i][j].second.losertime[k] - FileDatas2[i][j].second.winnertime[k];

							//std::cout << fixed << std::setprecision(2);
							if (-temp1 == FileDatas2[i][j].second.winnertime[k])
							{
								temp1 = 1000;
							}
							else if (temp1 < 0) {

								temp1 = FileDatas2[i][j].second.winnertime[k] + temp1;
							}
							else {


							}

							double percent1 = (100 - (100 * temp1));
							double ratingc1 = FileDatas2[i][j].second.ratingh - FileDatas2[i][j].second.pastratings[k];
							double wc1 = (2 * (FileDatas2[i][j].second.presentweight - FileDatas2[i][j].second.pastweight[k]));
							double Points = (bpminuswp1 * 10) + percent1 + +(ratingc1 * 10) + wc1;
							if (Points >= 0) {
								cout << "+" << Points;
								file << "+" << Points;
							}
							else {
								cout << setw(nameWidth) << setfill(separator) << Points;
								file << setw(nameWidth) << setfill(separator) << Points;
							}
						}
					cout << endl << endl;
					file << endl;

				}
				if (FileDatas2[i][j].second.bendpositions.size() > 0) {
					ratingchangetotal += FileDatas2[i][j].second.ratingh - FileDatas2[i][j].second.pastratings[FileDatas2[i][j].second.pastratings.size() - 1];
					//weightchangetotal += FileDatas2[i][j].second.presentweight - FileDatas2[i][j].second.pastweight[FileDatas2[i][j].second.pastweight.size() - 1];
					cout << setw(nameWidth) << setfill(separator) << "  -" << left << setw(nameWidth) << setfill(separator) << "      -" \
						
						<< left << setw(nameWidth) << setfill(separator) << "       -" \
						<< left << setw(nameWidth) << setfill(separator) << "    -" \
						<< FileDatas2[i][j].second.ratingh;
					cout << "(" << FileDatas2[i][j].second.ratingh - FileDatas2[i][j].second.pastratings[FileDatas2[i][j].second.pastratings.size() - 1];
					cout << left << setw(12) << setfill(separator) << ")" << setw(nameWidth) << setfill(separator) << FileDatas2[i][j].second.presentweight;
					cout << endl;
				
					file << setw(numWidth) << setfill(separator) << "  -" << left << setw(nameWidth) << setfill(separator) << "      -" \
						
						<< left << setw(nameWidth) << setfill(separator) << "            -" \
						<< left << setw(nameWidth) << setfill(separator) << "         -" \
						<<"       " << left << setw(nameWidth+5) << setfill(separator) << FileDatas2[i][j].second.ratingh;
					
					file << fixed << setprecision(1);

					file << FileDatas2[i][j].second.presentweight;
					if ((FileDatas2[i][j].second.presentweight - FileDatas2[i][j].second.pastweight[FileDatas2[i][j].second.pastweight.size() - 1]) >= 0) {
						cout  << "(+" << FileDatas2[i][j].second.presentweight - FileDatas2[i][j].second.pastweight[FileDatas2[i][j].second.pastweight.size() - 1] << ")";
						file << "(+" << FileDatas2[i][j].second.presentweight - FileDatas2[i][j].second.pastweight[FileDatas2[i][j].second.pastweight.size() - 1] << ")";

					}
					else {
						cout << "(" << FileDatas2[i][j].second.presentweight - FileDatas2[i][j].second.pastweight[FileDatas2[i][j].second.pastweight.size() - 1] << ")";
						file << "(" << FileDatas2[i][j].second.presentweight - FileDatas2[i][j].second.pastweight[FileDatas2[i][j].second.pastweight.size() - 1] << ")";

					}
					file << fixed << setprecision(0);
					file << endl;

					file << setw(numWidth) << setfill(separator) << "Total";  
					if (bpminuswptotal >= 0) {
						if (bpminuswptotal > 9) {
							file << left << setw(nameWidth-1) << setfill(separator) << "     " << bpminuswptotal;
						}
						else {
							file << left << setw(nameWidth) << setfill(separator) << "     " << bpminuswptotal;

						}
					}
					else if (bpminuswptotal < 0) {
						if (bpminuswptotal < -9) {
							file << left << setw(nameWidth-2) << setfill(separator) << "    " << bpminuswptotal;

						}
						else {
							file << left << setw(nameWidth - 1) << setfill(separator) << "     " << bpminuswptotal;
						}
					}
					
					file	<< left << setw(nameWidth) << setfill(separator) << "            -" \
						<< left << setw(nameWidth) << setfill(separator) << "         -";

					if (ratingchangetotal >= 0) {
						file << "         +" << ratingchangetotal << " ";
					}
					else {
						file << "         " << ratingchangetotal << " ";

					}
					file << left << setw(nameWidth) << setfill(separator);
					file << fixed << setprecision(1);
					int finalweight = FileDatas2[i][j].second.presentweight - FileDatas2[i][j].second.pastweight[FileDatas2[i][j].second.pastweight.size() - 1];
					if (finalweight == 8.5 || finalweight == -8.5) {
						file << "This DataExtractor is" << weightchangetotal;
					}
					if (weightchangetotal >= 0) {
						file << "         (+" << weightchangetotal << ")";
					}
					else {
						file << "        (" << weightchangetotal << ")";

					}
					
					if (highbend) {
						cout << endl;
						cout << "Note: This has bend-final greater than 5" << endl << endl;
						file << endl;
						file << "Note: This has bend-final greater than 5" << endl << endl;
					}
					
					if (weight8andhalf) {
						cout << endl;
						cout << "Note: This has weight change of 8.5 in previous weights" << endl << endl;
						file << endl;
						file << "Note: This has weight change of 8.5 in previous weights" << endl << endl;

					}
					file << fixed << setprecision(0);
					file << endl << endl << endl;
				}
		}
	}

			cout << endl;
			file << endl;
			file.close();



		}
	
