#ifndef MPQ_hpp
#define MPQ_hpp

#include <stdexcept>
#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

struct myStackException : public exception
{
   const char *what() const throw() { return "Underflow"; }
};

template <typename Comparable>
class MPQ
{
	public:
		MPQ(int size = 100) : Heap(size + 1), Location(size + 1, -1)	{ currentSize = 0; }
		~MPQ()															{ currentSize = 0; }
		
		void insert(Comparable value, int label)
		{
			Comparable hole = ++currentSize;
			while(hole > 1 && value > Heap[hole / 2].value)
			{
				Location[Heap[hole / 2].label] = hole;
				Heap[hole] = Heap[hole / 2];
				hole /= 2;
			}
			Heap[hole].value = value;
			Heap[hole].label = label;
			Location[label] = hole;
		}
		Comparable remove(int label)
		{
			if(isEmpty()) {
				throw myStackException();
			}
			else if(doesNotExist(label)) {
				return -1;
			}
			else {
				Comparable returnValue = Heap[Location[label]].value;
				int hole = Location[label];
				Heap[hole] = Heap[currentSize--];

				int child;
				int tempLabel = Heap[hole].label;
				int tempValue = Heap[hole].value;
				/*Comparable tempValue = Heap[hole].value;*/

				while(hole * 2 <= currentSize)
				{
					child = hole * 2;
					if(child != currentSize && Heap[child + 1].value > Heap[child].value) {
						child++;
					}
					if(Heap[child].value > tempValue) {
						Location[Heap[child].label] = hole;
						Heap[hole] = Heap[child];
					}
					else {
						break;
					}
					hole = child;
				}
				Heap[hole].value = tempValue;
				Heap[hole].label = tempLabel;
				Location[Heap[hole].label] = hole;
				Location[label] = -1;
				return returnValue;
			}
		}
		int returnLocation(int label)
		{
			return Location[label];
		}
		bool isEmpty() const
		{
			return currentSize == 0;
		}
		bool doesNotExist(int label) const
		{
			return Location[label] == -1;
		}
		Comparable getMax()
		{
			return Heap[1].value;
		}
		/*Comparable Remove(int label);*/
		/*Comparable GetMax();
		Comparable GetByLabel(int label);
		Comparable Pop();
		int GetMaxLabel();*/
		
		/*void Print();*/

	private:
		struct HeapNode{
			Comparable value;
			int label;
			HeapNode(const Comparable & v = Comparable(), int l = 0) : value(v), label(l) {}
		};

		vector<HeapNode> Heap;
		vector<int> Location;
		int currentSize;

		//// Useful Functions for Heap
		//int getLeftChildIndex(int parentIndex)		{ return parentIndex * 2; }
		//int getRightChildIndex(int parentIndex)		{ return parentIndex * 2 + 1; }
		//int getParentIndex(int childIndex)			{ return childIndex / 2; }

		//bool hasLeftChild(int index)				{ return getLeftChildIndex(index) < size; }
		//bool hasRightChild(int index)				{ return getRightChildIndex(index) < size; }
		//bool hasParent(int index)					{ return getParentIndex > 0; }

		///*void swap(int x, int y);*/
		//void percolateUp(int index);	// Percolate Up
		//void percolateDown(int index);	// Percolate Down
		//void heapify();

		//void swap(int x, int y)
		//{
		//	HeapNode temp = Heap[x];
		//	int xLabel = Heap[x].label;
		//	int yLabel = Heap[y].label;
		//	
		//	Location[xLabel] = y;
		//	Location[yLabel] = x;
		//	
		//	Heap[x] = Heap[y];
		//	Heap[y] = temp;
		//}
};


//template <typename comparable>
//class priorityQueue {
//public:
//    explicit priorityQueue(int capacity): Heap(capacity+1), location(500), size(0) {}
//    
//    // location i da doldurmayi unutma
//    
//	
//	void insert(comparable value, int label){
//        heapEntry obj;
//        obj.value = value;
//        obj.label = label;
//        Heap[++size] = obj;
//        location[label] = size;
//        bubble_up(size);
//        heapify();
//    }
//    
//    // Pops the head
//    comparable pop(){
//        if  (size > 0)
//            return Remove(Heap[1].label);
//        else 
//        	throw "Array is empty";
//    }
//
//    // removes and returns the head (max)
//    comparable Remove(int label){
//        int loc_on_heap = location[label];
//        if (loc_on_heap == -1)
//            throw "No item exists with that label!\n" ;
//        comparable output = Heap[loc_on_heap].value;
//        
//        swap(loc_on_heap, size);
//        location[label] = -1;
//        --size;
//        bubble_down(loc_on_heap);
//        heapify();
//        return output;
//        
//    }
//    
//    // returns the max value
//    comparable GetMax(){
//        if (IsEmpty())
//            throw "IsEmpty!\n";
//        else
//            return Heap[1].value;
//    }
//    
//    // Get the max of label 
//    int GetMaxLabel(){
//        if (IsEmpty())
//            throw "IsEmpty!\n";
//        else
//            return Heap[1].label;
//    }
//    
//    comparable GetByLabel(int label){
//        int loc = location[label];
//        if (loc == -1)
//            throw "No item exists with that label!\n" ;
//        return Heap[loc].value;
//    }
//    
//    bool IsEmpty(){
//        if (size == 0)
//            return 1;
//        return 0;
//    }
//    
//    void print(){
//        cout << "Heap: ";
//        for (int i = 1 ; i <= size ; i++){
//            cout << Heap[i].value << " ";
//        }
//        cout << endl;
//       /*
//        cout << "location: " << endl;
//        for (int i = 0 ; i < location.size(); i++){
//            cout << "(" << i << ")" << location[i] << endl;
//        }
//        cout << endl;
//        */
//    }
//    
//    
//    
//private:
//    struct heapEntry{
//        comparable value;
//        int label;
//        heapEntry(const comparable & val = comparable(), int lab = 0)
//        : value(val), label(lab)
//        {}
//    };
//    
//    vector<heapEntry> Heap;
//    vector<int> location;
//    int size;
//    
//    // useful functions
//    int getLeftChildIndex(int parentIndex) { return parentIndex*2; }
//    int getRightChildIndex(int parentIndex) { return parentIndex*2 + 1; }
//    int getParentIndex(int childIndex) { return childIndex / 2; }
//    
//    bool hasLeftChild(int index) { return getLeftChildIndex(index) < size; }
//    bool hasRightChild(int index) { return getRightChildIndex(index) < size; }
//    bool hasParent(int index) { return getParentIndex(index) > 0; }
//    
//
//    // Swaps the given indexes in Heap. Also organize the location array
//    void swap(int indexOne, int indexTwo){
//        auto temp = Heap[indexOne];
//        int labelOne = Heap[indexOne].label;
//        int labelTwo = Heap[indexTwo].label;
//        
//        location[labelOne] = indexTwo;
//        location[labelTwo] = indexOne;
//        
//        Heap[indexOne] = Heap[indexTwo];
//        Heap[indexTwo] = temp;
//    }
//    
//
//    // Percolate up
//    void bubble_up(int index){
//        while (hasParent(index) && Heap[getParentIndex(index)].value < Heap[index].value){
//            swap(getParentIndex(index), index);
//            index = getParentIndex(index);
//        }
//    }
//    
//    //  Percolate down
//    void bubble_down(int index){
//        if (hasLeftChild(index) && hasRightChild(index)){
//            int rightChildIndex = getRightChildIndex(index);
//            int leftChildIndex = getLeftChildIndex(index);
//
//            if (Heap[rightChildIndex].value > Heap[leftChildIndex].value){
//                if (Heap[rightChildIndex].value > Heap[index].value)
//                	swap(rightChildIndex, index);
//            }
//            else{
//                if (Heap[leftChildIndex].value > Heap[index].value)
//                	swap(leftChildIndex, index);
//            }
//
//            
//        }
//        else if (hasRightChild(index)){
//            int rightChildIndex = getRightChildIndex(index);
//            if (Heap[rightChildIndex].value > Heap[index].value)
//                	swap(rightChildIndex, index);
//        }
//        else if (hasLeftChild(index)){
//            int leftChildIndex = getLeftChildIndex(index);
//            if (Heap[leftChildIndex].value > Heap[index].value)
//                	swap(leftChildIndex, index);
//        }
//        
//    }
//
//    /* Starts with size/2 and goes up one by one. 
//    for each index check if the index is bigger than the 
//    child node(s). if not swap
//    */
//    void heapify(){
//        int index = size/2;
//        if (size > 3){
//            for (; index > 0; index--)
//                bubble_down(index);
//        }
//        // if size is 3 or less the algorithm above does not work.
//        // So do it manually :) 
//        else if (size == 3){
//            heapEntry obj1 = Heap[1];
//            heapEntry obj2 = Heap[2];
//            heapEntry obj3 = Heap[3];
//            
//            if (obj2.value > obj3.value && obj1.value < obj2.value)
//                swap(1, 2);
//            else if (obj3.value > obj2.value && obj1.value < obj3.value)
//                swap(1,3);
//        }
//        else if (size == 2){
//            heapEntry obj1 = Heap[1];
//            heapEntry obj2 = Heap[2];
//            
//            if (obj1.value < obj2.value)
//                swap(1,2);
//        }
//    }
//    
//    
//};


#endif /* MPQ_hpp */