#include <iostream>									// Berkay Ersever
#include <fstream>									// 19626
#include <vector>
#include <string>
#include "LZWBinaryTree.hpp"

using namespace std;

int main()
{
	int i = 0;										// Initialization
	char ch;
	string w[4096];
	int pW = 0;
	int cW = 0;
	string P = "";
	string C = "";
	string X = "";
	string word = "";
	string echo = "";
	while(i<256)									// Adding ASCII characters to the dictionary
	{
		ch = i;
		w[i] = ch;
		i++;
	}

	ifstream input;
	ofstream output("decompout.txt");
	input.open("compout.txt");
	if(input >> word)								// Tries to read input
	{
		cW = stoi(word);
		echo += w[cW];
		pW = cW;
	}
	else											// Failed to read
	{
		cout << "Couldn't opened the file" << endl;
	}	
	

	while(input >> word)							// Reads input as there are more words to read from the txt file
	{
		cW = stoi(word);
		if(w[cW] != "")								// Checks whether w[cW] exists in the dictionary or not
		{
			echo += w[cW];
			P = w[pW];
			C = w[cW].substr(0,1);
			X = P + C;
			if(i < 4095) {
				w[i] = X;
				i++;					
			}
		}
		else										// If w[cW] doesn't exist in the dictionary
		{
			P = w[pW];
			C = w[pW].substr(0,1);
			X = P + C;
			echo += X;
			if(i < 4095) {
				w[i] = X;
				i++;					
			}
		}
		pW = cW;
	}
	output << echo;	
	input.close();
	output.close();

	return 0;
}