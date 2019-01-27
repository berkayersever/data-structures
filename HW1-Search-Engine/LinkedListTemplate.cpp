#include "LinkedListTemplate.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

int main()
{
    const string filename = "docdb.txt";
    string line;
    ifstream input(filename);
    List<string> DB;
    
    if (!input.is_open())
    {
        cout << "Couldn't open docdb.txt";
        exit(1);
    }
    
	int documentCounter = 0;
    while (getline(input, line)) {
        int docID;
        string keyword;
        istringstream iss(line);
        iss >> keyword;
        iss >> docID;
        DB.addKeyword(keyword, docID);
		documentCounter++;
    }
	cout << documentCounter << " documents have been added" << endl;
	cout << "Enter your search query in the <# of queries> <search query> format: " << endl;
	
	int inputSize;
	cout << "Enter your search query: ";
		if (cin >> inputSize && inputSize != 0) {
			string *searchQuery = new string[inputSize];
			for (int i = 0; i < inputSize; i++) {
				cin >> searchQuery[i];
			}
			vector<int> matchData;
			DB.search(searchQuery, inputSize, matchData);
			for (int i = 0; i < inputSize; i++) {
				cout << searchQuery[i] << ' ';
			}
			cout << matchData.size() << ' ';
			for (int i = 0; i < matchData.size(); i++) {
				cout << matchData[i] << ' ';
			}
			cout << endl;
		}
		else if (cin.fail()) {
			cout << "Invalid input" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize> ::max(), '\n');
		}

    while(inputSize != 0) {
		cout << "Enter your search query: ";
		if (cin >> inputSize && inputSize != 0) {
			string *searchQuery = new string[inputSize];
			for (int i = 0; i < inputSize; i++) {
				cin >> searchQuery[i];
			}
			vector<int> matchData;
			DB.search(searchQuery, inputSize, matchData);
			for (int i = 0; i < inputSize; i++) {
				cout << searchQuery[i] << ' ';
			}
			cout << matchData.size() << ' ';
			for (int i = 0; i < matchData.size(); i++) {
				cout << matchData[i] << ' ';
			}
			cout << endl;
		}
		else if (cin.fail()) {
			cout << "Invalid input" << endl;
			cin.clear();
			cin.ignore();
		}
	}
    return 0;
}
