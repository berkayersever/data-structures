#include <iostream>									// Berkay Ersever
#include <fstream>									// 19626
#include <string>
#include "LZWBinaryTree.hpp"

using namespace std;

int main()
{
	char ch;										// Initialization
	string name;
	string P = "";
	string C = "";
	string X = "";
	string echo = "";
	int i = 256;
	BinarySearchTree<int> BST;						// BST Initialization
				
	ifstream input("compin.txt");
	ofstream output("compout.txt");
	while(!input.eof())								// eof returns true if next character is eof
	{
		input.get(ch);								// Reads the next character
		C = ch;
		X = P + C;
		
		if(BST.search(X) == nullptr)				// Checks whether X exists in the BST
		{
			if(P.length() == 1) {
				if(i < 4096) {
					echo += to_string(int(P[0])) + " ";
					if(X.length() > 1) {
						BST.insert(i, X);
						i++;
					}
				}
				else {
					echo += to_string(int(P[0])) + " ";
				}
			}
			else if(P.length() > 1) {
				if(i < 4096) {
					echo += to_string(BST.keyValue(P)) + " ";
					BST.insert(i, X);
					i++;
				}
				else {
					echo += to_string(BST.keyValue(P)) + " ";
				}
			}	
			P = C;
		}
		else
		{
			P = X;
		}
	}
	if(input.eof() && P == X)						// Check if we are at the end of file and there exists a character which is not processed 
		echo += to_string(int(C[0]));

	cout << echo << endl;
	output << echo;	
	input.close();
	output.close();									// Outputs the file

	return 0;
}