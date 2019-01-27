#ifndef LIST_H
#define LIST_H
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template <class itemType>
struct node
    {
        itemType data;
        node *next;
        node<int> *document;
        node(itemType data) : data(data) {
            next = nullptr;
            document = nullptr;
        }
        
};

template <class itemType>
class List
{
private:    
    node<string> *getNode(string keyword) {
        node<string> *iter = head;
        for (iter; iter != nullptr && iter -> data != keyword; iter = iter -> next) {}
        return iter;													// It will return null pointer if the search DNE
    }
    node<itemType> *head;
    node<itemType> *tail;
public:
    List() {
        head = tail = nullptr;
    }
    ~List() {
        node<string> *pre = head, *cur = head -> next;
        while (cur != nullptr) {
            delete pre;
            pre = nullptr;
            pre = cur;
            cur = cur -> next;
        }
        delete pre;
        pre = nullptr;
    }
    void addKeyword(string keyword, int docID) {
        node<string> *currentNode = getNode(keyword);
        if (currentNode == nullptr)
		{																// If the keyword is not in the list
            node<string> *nn = new node<string>(keyword);
            nn -> document = new node<int>(docID);
            if (head == nullptr) {
                head = nn;
                tail = head;
            }
            else {
                tail -> next = nn;
                tail = nn;
            }
        }
        else {															// If the keyword exists in the list, add a new document node
            addDocument(currentNode, docID);
        }
    }
    void addDocument(node<string> *keywordOfInterst, int docID) {
        node<int> *headOfDocumentList = keywordOfInterst -> document;
        node<int> *nn = new node<int>(docID);
        
        if (headOfDocumentList -> data > docID)							// Compare with head node first
		{
            nn -> next = headOfDocumentList;
            keywordOfInterst -> document = nn;
        }
		else if (headOfDocumentList -> data < docID)
		{
			node<int> *iter = headOfDocumentList;
			for (iter; iter -> next != nullptr && iter -> next -> data < docID; iter = iter -> next) {}
			iter -> next = nn;
		}
		else {
			cout << "Duplicate Entry Detected!" << endl;
		}
    }
    void search(string arr[], int arrSize, vector<int> &matchDocuments) {
		node<int> **documentPointers = new node<int>*[arrSize];
		int maxDocID = 0;												// Keep the greatest document number
		node<string> *keywordPointer;
		for (int i = 0; i < arrSize; i++) {
			keywordPointer = getNode(arr[i]);
			if (keywordPointer == nullptr) {
				return;
			}
			documentPointers[i] = keywordPointer -> document;
			if (keywordPointer -> document -> data > maxDocID) {
				maxDocID = keywordPointer -> document -> data;
			}
		}

		bool aListHasEnded = false;

		while (! aListHasEnded) {
			bool matchOccured = true;
			int currentDocID;
			for (int i = 1; i < arrSize; i++) {
				currentDocID = documentPointers[i] -> data;
				if (currentDocID != maxDocID) {
					matchOccured = false;
					documentPointers[i] = documentPointers[i] -> next;	// Proceed to the next node in the list
					if (documentPointers[i] == nullptr) {
						aListHasEnded = true;
					}
					else if (currentDocID > maxDocID) {
						maxDocID = currentDocID;
					}
				}
			}
			if (matchOccured) {											// If there is a match
				for (int i = 0; i < arrSize; i++) {
					currentDocID = documentPointers[i] -> data;
					vector<int>::iterator it = find(matchDocuments.begin(), matchDocuments.end(), currentDocID);

					if (currentDocID >= maxDocID && it == matchDocuments.end()) {
						matchDocuments.push_back(currentDocID);
						maxDocID = currentDocID;
					}
					
					documentPointers[i] = documentPointers[i] -> next;
					if (documentPointers[i] == nullptr) {
						aListHasEnded = true;
					}
				}
			}
		}
	}
};
#endif