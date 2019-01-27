#include <fstream>			// Berkay Ersever
#include <iostream>			// 19626
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;

int hashFunction (const int & key, int tableSize)
		{
			int hashVal = 0;
			hashVal = key % tableSize;
			
			if (hashVal < 0) {
				hashVal = hashVal + tableSize;
			}
			/*cout << "Hash Value: " << hashVal << endl;*/
			return hashVal;
			
			/*int hashVal = 0;

			for (unsigned int i = 0; i < key.length(); i++) {
				hashVal = 37 * hashVal + key[i];
				cout << "Hash Value: " << hashVal << endl;
				cout << "key[" << i << "] Value: " << key[i] << endl;
			}
			
			hashVal = hashVal % tableSize;
			
			if (hashVal < 0)
				hashVal = hashVal + tableSize;
			
			cout << "Hash Value: " << hashVal << endl;
			return(hashVal);*/
		}

template <class HashedObj>
        class HashTable
        {
		  public:
            explicit HashTable(const HashedObj & notFound, int size);
            HashTable(const HashTable & rhs) : ITEM_NOT_FOUND(rhs.ITEM_NOT_FOUND), array(rhs.array), currentSize(rhs.currentSize) {}

            const HashedObj & find(const HashedObj & x) const;
			/*int findPos(const HashedObj & x) const;*/
			const string parse(const HashedObj & x) const;

			/*int currentSize;*/
			//static int count;	// Number of entries in the hash table

            void makeEmpty();
            int insert(const HashedObj & x, int dec);
            int remove(const HashedObj & x);
			void generate(/*const HashedObj & x, */int i, int d, int f, int** & iS, int** & iF, int** & dS, int** & dF, int** & fS, int** & fF);
			void increaseProbes(const HashedObj & x);
			int getProbes(const HashedObj & x);

            const HashTable & operator=(const HashTable & rhs);

            enum EntryType {ACTIVE, EMPTY, DELETED};
			
		
		  private:
            struct HashEntry
			{
				HashedObj element;
				EntryType info;
				int dec;		// ASCII
				int probes;
				HashEntry(const HashedObj & e = HashedObj(), EntryType i = EMPTY, int dec = 0, int probes = 0) : element(e), info(i) , dec(dec), probes(probes) {}
			};
            
			/*int HashTable::count = 0;*/

            vector<HashEntry> array;
            int currentSize;
            const HashedObj ITEM_NOT_FOUND;

            bool isActive(int currentPos) const;
			bool isDeleted(int currentPos) const;
			bool isEmpty(int currentPos) const;
			bool isFull(/*int currentPos*/) const;
            int findPos(const HashedObj & x) const;
            void rehash();
        };

		/**
         * Construct the hash table.
         */
        template <class HashedObj>
        HashTable<HashedObj>::HashTable(const HashedObj & notFound, int size)
          : ITEM_NOT_FOUND(notFound), array(nextPrime(size))
        {
            makeEmpty( );
        }

		/**
         * Internal method to test if a positive number is prime.
         * Not an efficient algorithm.
         */
		bool isPrime( int n )
        {
            if( n == 2 || n == 3 )
                return true;

            if( n == 1 || n % 2 == 0 )
                return false;

            for( int i = 3; i * i <= n; i += 2 )
                if( n % i == 0 )
                    return false;

            return true;
        }

		/**
         * Internal method to return a prime number at least as large as n.
         * Assumes n > 0.
         */
        int nextPrime(int n)
        {
            if( n % 2 == 0 )
                n++;

            for( ; !isPrime( n ); n += 2 )
                ;

            return n;
        }


		/**
         * Make the hash table logically empty.
         */
        template <class HashedObj>
        void HashTable<HashedObj>::makeEmpty()
        {
            currentSize = 0;
			for(unsigned int i = 0; i < array.size(); i++)
                array[i].info = EMPTY;  // destroy the lists but not the vector!
        }

		
		
		/**
         * Method that performs linear probing resolution.
         * Return the position where the search for x terminates.
         */
		template <class HashedObj>
		int HashTable<HashedObj>::findPos(const HashedObj & x) const
		{
			int probes = 0;
			unsigned int currentPos = hashFunction(x, array.size());
			for(unsigned int i = 0; i < array.size() && !(array[currentPos].info == ACTIVE && array[currentPos].element == x); i++) {
				currentPos++;									// Add the difference
				probes++;
				if(currentPos >= array.size())					// Perform the mod
					currentPos = currentPos - array.size();		// If necessary
			}

            if(probes == array.size())
				return -probes;
            
			return probes;
		}

		/**
         * Return true if currentPos exists and is active.
         */
        template <class HashedObj>
        bool HashTable<HashedObj>::isActive(int currentPos) const
        {
            return array[currentPos].info == ACTIVE;
        }

		/**
         * Return true if currentPos exists and is deleted.
         */
        template <class HashedObj>
        bool HashTable<HashedObj>::isDeleted(int currentPos) const
        {
            return array[currentPos].info == DELETED;
        }

		/**
         * Return true if currentPos exists and is empty.
         */
        template <class HashedObj>
        bool HashTable<HashedObj>::isEmpty(int currentPos) const
        {
            return array[currentPos].info == EMPTY;
        }

		/**
         * Return true if the hash table is full.
         */
        template <class HashedObj>
        bool HashTable<HashedObj>::isFull(/*int currentPos*/) const
        {
            if(currentSize == array.size()) {
				cout << "HASH TABLE IS FULL!!!" << endl;
				return true;
			}
			else {
				return false;
			}
			
			//bool result = true;
			//for(unsigned int i = 0; i < array.size(); i++) {
			//	//if(currentPos + i >= array.size())						// Perform the mod
			//	//	currentPos + i = currentPos + i - array.size();		// If necessary
			//	if(array[/*currentPos + */i].info == EMPTY || array[i].info == DELETED)
			//		return false;
			//}
			//return result;
        }

		/**
         * Remove item x from the hash table.
         *  x has to be in the table
         */
        template <class HashedObj>
        int HashTable<HashedObj>::remove(const HashedObj & x)
        {
            int probes = 0;
			unsigned int currentPos = hashFunction(x, array.size());
			for(unsigned int i = 0; i < array.size() && !(array[currentPos].info == ACTIVE && array[currentPos].element == x); i++) {
				currentPos++;									// Add the difference
				probes++;
				if(currentPos >= array.size())					// Perform the mod
					currentPos = currentPos - array.size();		// If necessary
			}

            if(probes == array.size())
				return -probes;
            if(isActive(currentPos)) {
				array[currentPos].info = DELETED;
				currentSize--;
			}
			return probes;
        }

		/**
         * Find item x in the hash table.
         * Return the matching item, or ITEM_NOT_FOUND, if not found.
         */
        template <class HashedObj>
        const HashedObj & HashTable<HashedObj>::find( const HashedObj & x ) const
        {
            int currentPos = findPos( x );
            if (isActive( currentPos )) 
               return array[ currentPos ].element; 
 
            return   ITEM_NOT_FOUND;
        }

		/*template <class HashedObj>
		int HashTable<HashedObj>::findPos(const HashedObj & x) const
		{
			int collisionNum = 0;
			int currentPos = hash(x, array.size());
			while(array[currentPos].info != EMPTY && array[currentPos].element != x) {
				currentPos++;
				if(currentPos >= array.size())
					currentPos = currentPos - array.size();
			}
			return currentPos;
		}*/

//		int findPos(const HashedObj & x) const
//	{
//		int offset = 1;
//		int positionCurrent = myhash(x);
//
//		//to check for collisions
//		if(array[positionCurrent].entryInfo != EMPTY)
//		{
//			cout << "There was a collision at index " << positionCurrent << endl;
//		}
//		while(array[positionCurrent].entryInfo != EMPTY)
//		{
//			positionCurrent++;
//			if(positionCurrent >= array.size())
//			{
//				positionCurrent -= array.size();
//			}
//		}
//		return positionCurrent;
//}

		/**
         * Find item x in the hash table.
         * Return the matching item's code, or ITEM_NOT_FOUND, if not found.
         */
        template <class HashedObj>
        const string HashTable<HashedObj>::parse( const HashedObj & x ) const
        {
            int currentPos = findPos( x );
            if (isActive( currentPos )) 
               return to_string(array[ currentPos ].dec); 
 
            return   ITEM_NOT_FOUND;
        }
		
		/**
         * Insert item x into the hash table. If the item is
         * already present, then do nothing.
         */
        template <class HashedObj>
        int HashTable<HashedObj>::insert(const HashedObj & x, int dec)
        {
            int probes = 0;
			unsigned int currentPos = hashFunction(x, array.size());
			/*cout << "Array Size: " << array.size() << endl;*/
			/*for(unsigned int i = 0; i < array.size() && ((array[currentPos].info != EMPTY && array[currentPos].element != x) || (array[currentPos].info == DELETED)); i++) {*/
			for(unsigned int i = 0; i < array.size() && (array[currentPos].info == ACTIVE && array[currentPos].element != x); i++) {
			/*while((array[currentPos].info != EMPTY && array[currentPos].element != x) || (array[currentPos].info == DELETED)) {*/
				currentPos++;									// Add the difference
				probes++;
				if(currentPos >= array.size())					// Perform the mod
					currentPos = currentPos - array.size();		// If necessary
			}
			
			// Insert x as active
            /*int currentPos = findPos(x);*/
            if(isActive(currentPos))
				return -probes;
            if(isEmpty(currentPos) || isDeleted(currentPos)) {
				array[currentPos] = HashEntry(x, ACTIVE, dec);
				currentSize++;
				/*count++;*/
				/*cout << "Count: " << count << endl;*/
			}
			return probes;
		}

		/*template <class HashedObj>
		int HashTable<HashedObj>::count = 0;*/

		template <class HashedObj>
		int HashTable<HashedObj>::getProbes(const HashedObj & x)
		{
			int currentPos = findPos(x);
			return array[currentPos].probes;
		}

		template <class HashedObj>
		void HashTable<HashedObj>::increaseProbes(const HashedObj & x)
		{
			cout << "Before increasing: " << array[currentPos].probes << endl;
			int currentPos = findPos(x);
			array[currentPos].probes++;
			cout << "After increasing: " << array[currentPos].probes << endl;
		}

		template <class HashedObj>
		void HashTable<HashedObj>::generate(/*const HashedObj & x, */int i, int d, int f, int** & insertSuccess, int** & insertFailed, int** & deleteSuccess, int** & deleteFailed, int** & findSuccess, int** & findFailed)
		/*void generate(HashTable<int> h, int i, int d, int f)*/
		{
			/*cout << "Current Size: " << array[currentSize] << endl;*/
			
			int M = array.size();
			int insertCounter = 0;
			int deleteCounter = 0;
			int findCounter = 0;
			//srand(4);		// Make the hash table full
			srand(1);;

			for(int w = 0; w < M + 1; w++) {
				for(int j = 0; j < 2; j++) {
					insertSuccess[w][j] = 0;
					insertFailed[w][j] = 0;
					deleteSuccess[w][j] = 0;
					deleteFailed[w][j] = 0;
					findSuccess	[w][j] = 0;
					findFailed[w][j] = 0;
				}
			}

			for(int j = 0; (j < 1000000 && !isFull()); j++) {
				int r = (rand() % (10 * M));
				int t = rand();
				int m = t % 8;
				if (m < i) {
					// Insert
					int x = insert(r,r);
					/*cout << "Current Size: " << currentSize << endl;*/
					/*cout << "r: " << r << endl;
					cout << "M: " << M << endl;*/
					r = hashFunction(r, M);
					if(x < 0) {
						insertFailed[currentSize][0] -= x;
						insertFailed[currentSize][1] += 1;
					}
					else {
						insertSuccess[currentSize - 1][0] += x;
						insertSuccess[currentSize - 1][1] += 1;
					}
					insertCounter++;
				}
				else if (m < i + d) {
					// Delete
					int x = remove(r);
					if(x < 0) {
						deleteFailed[currentSize][0] -= x;
						deleteFailed[currentSize][1] += 1;
					}
					else {
						deleteSuccess[currentSize + 1][0] += x;
						deleteSuccess[currentSize + 1][1] += 1;
					}
					deleteCounter++;
				}
				else {
					// Find
					int x = findPos(r);
					if(x < 0) {
						findFailed[currentSize][0] -= x;
						findFailed[currentSize][1] += 1;
					}
					else {
						findSuccess[currentSize][0] += x;
						findSuccess[currentSize][1] += 1;
					}
					findCounter++;
				}
			}

			ofstream output1("insertSuccess.csv");
			output1 << "sep=;" << endl;
			for(int i = 0; i < M + 1; i++) {
				for(int j = 0; j < 2; j++) {
					output1 << insertSuccess[i][j];
					if(j == 0) {
						output1 << ";";
					}
				}
				if(i != M) {
					output1 << "\n";
				}
			}
			output1.close();

			ofstream output2("insertFailed.csv");
			output2 << "sep=;" << endl;
			for(int i = 0; i < M + 1; i++) {
				for(int j = 0; j < 2; j++) {
					output2 << insertFailed[i][j];
					if(j == 0) {
						output2 << ";";
					}
				}
				if(i != M) {
					output2 << "\n";
				}
			}
			output2.close();

			ofstream output3("deleteSuccess.csv");
			output3 << "sep=;" << endl;
			for(int i = 0; i < M + 1; i++) {
				for(int j = 0; j < 2; j++) {
					output3 << deleteSuccess[i][j];
					if(j == 0) {
						output3 << ";";
					}
				}
				if(i != M) {
					output3 << "\n";
				}
			}
			output3.close();

			ofstream output4("deleteFailed.csv");
			output4 << "sep=;" << endl;
			for(int i = 0; i < M + 1; i++) {
				for(int j = 0; j < 2; j++) {
					output4 << deleteFailed[i][j];
					if(j == 0) {
						output4 << ";";
					}
				}
				if(i != M) {
					output4 << "\n";
				}
			}
			output4.close();

			ofstream output5("findSuccess.csv");
			output5 << "sep=;" << endl;
			for(int i = 0; i < M + 1; i++) {
				for(int j = 0; j < 2; j++) {
					output5 << findSuccess[i][j];
					if(j == 0) {
						output5 << ";";
					}
				}
				if(i != M) {
					output5 << "\n";
				}
			}
			output5.close();

			ofstream output6("findFailed.csv");
			output6 << "sep=;" << endl;
			for(int i = 0; i < M + 1; i++) {
				for(int j = 0; j < 2; j++) {
					output6 << findFailed[i][j];
					if(j == 0) {
						output6 << ";";
					}
				}
				if(i != M) {
					output6 << "\n";
				}
			}
			output6.close();
			
			//while(!input.eof())								// eof returns true if next character is eof
			//{
			//	input.get(ch);								// Reads the next character
			//	C = ch;
			//	X = P + C;

			//	if(hashTable.find(X) == "")					// Checks whether X exists in the Hash Table
			//	{
			//		echo += hashTable.parse(P) + " ";
			//		hashTable.insert(X, i);
			//		P = C;
			//		i++;
			//	}
			//	else
			//	{
			//		P = X;
			//	}
			//}
			//output << echo;	
			//input.close();
			//output.close();									// Outputs the file

			cout << "Insert Counter: " << insertCounter << endl;
			cout << "Delete Counter: " << deleteCounter << endl;
			cout << "Find Counter: " << findCounter << endl;

			/*cout << "# of Probes" << "\t" << "# of Transactions" << endl;
			for(int i = 0; i < M + 1; i++) {
				for(int j = 0; j < 2; j++) {
					cout << insertSuccess[i][j] << "\t";
				}
				cout << "\n";
			}

			for(int i = 0; i < M + 1; i++) {
				for(int j = 0; j < 2; j++) {
					cout << insertFailed[i][j] << " ";
				}
				cout << "\n";
			}*/
		}

		int main()
		{
			
			
			/*for(int i = 0; i < 5; i++) {
				cout << rand() << " ";
			}*/
			
			//char ch;										// Initialization
			string name;
			string P = "";
			string C = "";
			string X = "";
			string echo = "";
			int i = 0;
			int M;											// Hash Table Size
			cout << "Enter hash table size: ";
			cin >> M;
			M = nextPrime(M);
			int rowCount = M + 1;
			int colCount = 2;

			HashTable <int> hashTable     (NULL, M);			// Hash Table Initialization
			
			int** insertSuccess	= new int*[rowCount];
			int** insertFailed	= new int*[rowCount];
			int** deleteSuccess	= new int*[rowCount];
			int** deleteFailed	= new int*[rowCount];
			int** findSuccess	= new int*[rowCount];
			int** findFailed	= new int*[rowCount];
			for(int i = 0; i < rowCount; i++) {
				insertSuccess[i]	= new int[colCount];
				insertFailed[i]		= new int[colCount];
				deleteSuccess[i]	= new int[colCount];
				deleteFailed[i]		= new int[colCount];
				findSuccess[i]		= new int[colCount];
				findFailed[i]		= new int[colCount];
			}

			/*insertSuccess[1000][1] = 0;*/
			/*cout << insertSuccess[1000][1] << endl;*/
			
			/*for (int n = 0; n < t; n++) {
				for (int m=0; m < 2; m++) {
					insertSuccess[n][m] = 0;
				}
			}*/

			/*unsigned char charToBeStored;*/

			/*hashTable.find(0);*/
			
			hashTable.generate(2, 1, 5, insertSuccess, insertFailed, deleteSuccess, deleteFailed, findSuccess, findFailed);

			//while(i<17)									// Adding characters in the Hash Table
			//{
			//	// string stringToBeStored = "";
			//	// stringToBeStored += charToBeStored;
			//	hashTable.insert(i, i);
			//	i++;
			//}

			//for(int w = 0; w < 32; w++)
			//{
			//	// string stringToBeStored = "";
			//	// stringToBeStored += charToBeStored;
			//	hashTable.remove(w);
			//}
			
			//ifstream input("compin.txt");
			//ofstream output("compout.txt");
			//while(!input.eof())								// eof returns true if next character is eof
			//{
			//	input.get(ch);								// Reads the next character
			//	C = ch;
			//	X = P + C;

			//	if(hashTable.find(X) == "")					// Checks whether X exists in the Hash Table
			//	{
			//		echo += hashTable.parse(P) + " ";
			//		hashTable.insert(X, i);
			//		P = C;
			//		i++;
			//	}
			//	else
			//	{
			//		P = X;
			//	}
			//}
			//output << echo;	
			//input.close();
			//output.close();									// Outputs the file


			return 0;
		}