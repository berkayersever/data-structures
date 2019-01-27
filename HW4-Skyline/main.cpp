#include <iostream>
#include <string>
#include <fstream>
#include "MPQ.hpp"

using namespace std;

struct building {
	int xVal;
	int label;
};

void merge(vector<building> & a, vector<building> & temp, int leftPos, int rightPos, int rightEnd)
{
	int leftEnd = rightPos - 1;
	int tempPos = leftPos;
	int numElements = rightEnd - leftPos + 1;

	while (leftPos <= leftEnd && rightPos <= rightEnd)
	{
		if (a[leftPos].xVal <= a[rightPos].xVal)
			temp[tempPos++] = a[leftPos++];
		else
			temp[tempPos++] = a[rightPos++];
	}
	while (leftPos <= leftEnd)
	{
		temp[tempPos++] = a[leftPos++];
	}
	while (rightPos <= rightEnd)
	{
		temp[tempPos++] = a[rightPos++];
	}
	for (int i = 0; i < numElements; i++, rightEnd--)
	{
		a[rightEnd] = temp[rightEnd];
	}
}
void mergeSort(vector<building> & a, vector<building> & temp, int left, int right)
{
	if (left < right)
	{
		int center = (left + right) / 2;
		mergeSort(a, temp, left, center);
		mergeSort(a, temp, center + 1, right);
		merge(a, temp, left, center + 1, right);
	}
}

void mergeSort(vector<building> & a)
{
	vector<building> temp(a.size());
	mergeSort(a, temp, 0, a.size() - 1);
}
int main()
{
	string fileName;
	int numBuild;
	int xright;
	int xleft;
	int y;
	fileName = "input.txt";
	
	ifstream stream;
	stream.open(fileName.c_str());
	stream >> numBuild;
	MPQ<int> mpq(numBuild);
	vector <building> xArr(numBuild * 2);
	vector <int> yArr(numBuild+1);
	int labelcount = 1;
	int xcount = 0;
	
	while (!stream.eof())
	{
		stream >> xArr[xcount].xVal;
		xArr[xcount].label = labelcount;
		xcount++;
		stream >> yArr[labelcount];
		stream >> xArr[xcount].xVal;
		xArr[xcount].label = labelcount;
		labelcount++;
		xcount++;
	}

	mergeSort(xArr);

	int prevVal = -1;
	if (xArr[0].xVal != 0)
	{
		cout << 0 << " " << 0 << endl;
		prevVal = 0;
	}
	for (int i = 0; i < xArr.size(); i++)
	{
		if (i != xArr.size() - 1 && xArr[i].xVal == xArr[i + 1].xVal)
		{
			if(mpq.returnLocation(xArr[i].label) == -1)
			mpq.insert(yArr[xArr[i].label], xArr[i].label);
			else
				mpq.remove(xArr[i].label);
			while (i != xArr.size() - 1 && xArr[i].xVal == xArr[i + 1].xVal)
			{
				if (mpq.returnLocation(xArr[i+1].label) == -1)
				{
					mpq.insert(yArr[xArr[i+1].label], xArr[i+1].label);
					i++;
				}
				else
				{
					mpq.remove(xArr[i+1].label);
					i++;
				}
			}
		}

		else
		{
			if (mpq.returnLocation(xArr[i].label) == -1)
			{
				mpq.insert(yArr[xArr[i].label], xArr[i].label);
			}
			else
			{
				mpq.remove(xArr[i].label);
			}
		}
		if (!mpq.isEmpty() && mpq.getMax() != prevVal)
		{
			cout << xArr[i].xVal << " " << mpq.getMax() << endl;
			prevVal = mpq.getMax();
		}
		else if (mpq.isEmpty() && prevVal != 0)
		{
			cout << xArr[i].xVal << " " << 0 << endl;
			prevVal = 0;
		}
	}


	cin.get();
	cin.ignore();

	return 0;
}



//enum side {RIGHT, LEFT};
//struct xCoordinate {
//    int x; // X coordinate
//    side s; // which side of the building
//    int b; // building ID. it is all odd number: 1 3 5 ...
//    
//    xCoordinate(int value, int building) : x(value), b(building) {
//        if (b%2 == 0){
//            b--;
//            s = RIGHT;
//        }
//        else{
//            s = LEFT;
//        }
//    }
//};
//
//
//// Takes priorityQueue object and a vector. Put the piority queue into xSorted in sorted order.
//void heapSort(priorityQueue<int> &heapForSort, vector<xCoordinate> &xSorted){
//    vector<xCoordinate> xRevSorted;
//    
//	for(bool j = heapForSort.IsEmpty(); j == false; j = heapForSort.IsEmpty()) {
//		j = heapForSort.IsEmpty();
//		xCoordinate xCoord(heapForSort.pop(), heapForSort.GetMaxLabel());
//        xRevSorted.push_back(xCoord);
//	}
//
//
//
//    /*while (!heapForSort.IsEmpty()){
//        xCoordinate xCoord(heapForSort.GetMaxLabel(), heapForSort.pop());
//        xRevSorted.push_back(xCoord);
//    }*/
//    for (int i = int(xRevSorted.size()-1) ; i >= 0 ; i--)
//        xSorted.push_back(xRevSorted[i]);
//}
//
//
//int main(){
//    
//    //  Open file ...
//    ifstream inputFile;
//    inputFile.open("input.txt");
//    
//    int numBuilding, x1, x2, y;
//    
//    inputFile >> numBuilding;
//    priorityQueue<int> heapForSort(numBuilding*2); // takes x coordinates. used fot sorting
//    priorityQueue<int> heightHeap(numBuilding); // stores the y values in heap with building ID(1 3 5 ...)
//    int i = 0;
//    while (inputFile >> x1 >> y >> x2){
//        // so each pair of labels 1,2 or 3,4 are x coordinate of same building.
//        // Building numbers are odd 1 3 5 7 ...
//        heapForSort.insert(x1,++i); // odd numbers are left x coordinates
//        heightHeap.insert(y,i);
//        heapForSort.insert(x2,++i); // Even numbers are right x coordinates
//        
//    }
//    
//    // Sorting X coordinates...
//    
//    
//    vector <xCoordinate> xSorted;
//    heapSort(heapForSort, xSorted);
//    /*
//    cout << "ordered list is ready!" << endl;
//    
//    for (int j = 0; j < xSorted.size(); j++){
//        cout << xSorted[j].x << " building num: " << xSorted[j].b << endl;
//    }
//    cout << endl;
//    */
//    
//    priorityQueue<int> currentHeightHeap(numBuilding); // Height of the current buildings corresponding x coordinate.
//    
//
//    // For each x coordinate(in ascending order) get the height of the building(s) above and decide the highest one.
//    for (int i = 0; i < xSorted.size(); i++){
//        int x = xSorted[i].x;
//        int b = xSorted[i].b;
//        int s = xSorted[i].s;
//        int y = heightHeap.GetByLabel(b);
//        
//        // If no building starts form x = 0, print "0 0"
//        if (i == 0 && x != 0)
//            cout << 0 << " " << 0 << endl;
//        
//        // Check the x coordinate if it is left or right side
//        if (s == LEFT){
//            // if left insert and check if it is bigger than the previous height.
//            // if it is print it out.
//            currentHeightHeap.insert(y, b);
//            if (y == currentHeightHeap.GetMax()){
//                cout << x << " " << currentHeightHeap.GetMax() << endl;
//            }
//        }
//
//        else if (s == RIGHT){
//            // if right, check if it is the highest building in that range?
//            // if it is update the skyline
//            if (b == currentHeightHeap.GetMaxLabel()){
//                currentHeightHeap.pop();
//                if (currentHeightHeap.IsEmpty())
//                    cout << x  << " " << 0 << endl;
//                else
//                    cout << x << " " << currentHeightHeap.GetMax() << endl;
//            }
//            // If it is not the skyline remove it from the heap.
//            else{
//                currentHeightHeap.Remove(b);
//            }
//        }
//        
//    }
//    
//    return 0;
//}