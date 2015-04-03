#ifndef NDVector_H
#define NDVector_H

/* Luke Garrison, NDVector.h
 * Templated Vector class

 */

#include <iostream>
using namespace std;

template <typename T>
class NDVector {
	public:
		NDVector(long initSize = 10);	// constructor, fallback of 10 elements
		NDVector(const NDVector<T> &); 	// copy constructor
		~NDVector();					// deconstructor
		const NDVector<T> & operator=(const NDVector<T> &); // set NDVector equal to the other NDVector
		T& operator[](int index) const;	// random access operator
		int size() const;				// returns size of array (different from capacity)
		int capacity() const;			// returns capacity of the NDVector
		void reallocate();				// allocate 2x the capacity of the previous array
		void push_back(T element); 		// append element to the end of the NDVector
		void push_front(T element);		// place element at the front of the array (copy all elements to new array required)
		void pop_back();				// remove the last element from the array
		T getFirst();					// return the first element in the array
		T getLast();					// return the last element in the array
		void clear();					// clear the vector (doesn't clear its memory)
		void swap(int index1, int index2);		// swap values at two indicies in the array
		void erase(int index);			// erase element at specified index
		void operator+=(const NDVector<T> &);	// append a NDVector to this NDVector
		bool operator==(const NDVector<T> &);	// returns true if every element in the NDVectors are equal
		void sort();					// use bubble sort to sort NDVector
	
	private:
		// private member functions
		void manageBadAllocException(exception &e, long initSize);	// manage bad alloc exception from allocating space for array		

		// private data members
		T* ptr;					// pointer to first element of array of type T which is the basic data structure of the class
		long vecSize;			// number of elements in the vector
		long vecCapacity;		// capacity of the vector, always >= vecSize
};

#endif

/* Constructor
 * Allocates space for the array
 * Will allocate the required space for the number of desired elements in the array
*/
template <typename T>
NDVector<T>::NDVector(long initSize) {
	int defaultSize = 10;	// default fallback value for array size, in case initSize allocation fails
	vecCapacity = initSize;	// set capactiy data member

	try{
		ptr = new T[vecCapacity];	// allocate space for the
	}
	catch (exception &e) {
		vecCapacity = defaultSize;	// allocate the default size instead
		cerr << "Error: " << e.what() << ": There is not enough memory to allocate an NDVector of size " << initSize << endl;
		cerr << "Error: " << e.what() << ": Allocated an NDVector of size " << defaultSize << " instead" << endl;
		ptr = new T[vecCapacity];		
	}

	vecSize = 0;				// NDVector initially has no elements in it
}

/* Copy constructor
*/
template<typename T>
NDVector<T>::NDVector( const NDVector<T> &arrayToCopy )  : vecSize( arrayToCopy.vecSize )  {
  	ptr = new T[vecSize]; // create space for pointer-based array

	// copy every element from original array to this array
  	for( int i = 0; i < vecSize; i++ )
    	ptr[i] = arrayToCopy.ptr[i]; // copy into new object
}

/* Deconstructor
 * Release all memory allocated to the array
*/
template <typename T>
NDVector<T>::~NDVector() {
	delete [] ptr;	// release pointer-based array space
}

/* Operator=, sets NDVector equal to another NDVector
*/
template <typename T>
const NDVector<T> & NDVector<T>::operator=(const NDVector<T> &vecToCopy) {
	if(&vecToCopy != this) {	// don't set a vector equal to itself
		if(vecToCopy.size() != vecSize) {	// check if new array needs to be created for proper sizing
			delete [] ptr;	// delete current array
			vecSize = vecToCopy.size();
			vecCapacity = vecToCopy.capacity();
			ptr = new T[vecCapacity];
		}

		// copy each element from vecToCopy
		for(int i = 0; i < vecSize; i++) {
			ptr[i] = vecToCopy[i];
		}
	}	

	return (*this);	// enables cascading, ie x = y = z
}


/* Random access operator
*/
template <typename T>
T& NDVector<T>::operator[](int index) const {
	// throw an expection if bad index is provided
	if(index < 0) {
		throw "Cannot access a negative index of an NDVector";
	} else if (index > vecSize) {
		throw "Specified NDVector access index does not exist";
	}
	
	return ptr[index];
}

/* Returns the size (number of elements) of the NDVector
*/
template <typename T>
 int NDVector<T>::size() const {
	return vecSize;
}

/* Returns the vecCapacity (maximum number of elements that could currently fit in the NDVector
*/
template <typename T>
int NDVector<T>::capacity() const {
	return vecCapacity;
}

/* Allocate 2X the capacity for the array
*/
template <typename T>
void NDVector<T>::reallocate() {
	vecCapacity*= 2;
	T* oldVecPointer = ptr;		// set oldVecPointer to point at the current array data so it doesn't get lost
	ptr = new T[vecCapacity];
	// copy all elements to the new, larger capacity array
	for(int i = 0; i < vecSize; i++) {
		ptr[i] = oldVecPointer[i];
	}
	delete [] oldVecPointer;		// free memory of old array after reallocating
//	cout << "\\ Reallocation Successful. Capacity=" << vecCapacity << " /";
}

/* push_front function modeled after STL's Vector method.
 * Allocates a new array with the same capacity, places the new element at the first
 * index, and then copies all of the previous array's data to the new one
*/
template <typename T>
void NDVector<T>::push_front(T element) {
	if(vecSize >= vecCapacity) {
		reallocate();			// increase capacity of array
	}
	T* oldVecPointer = ptr;		// point to the current array data so it doesn't get lost
	ptr = new T[vecCapacity];	// allocate a new array with the same capacity
	ptr[0] = element;			// place element at the front of the new array;
	vecSize++;					// track that another element was successfully added
	// copy all elements to the new array, after the index of the first element	
	//cout << "vecSize=" << vecSize << endl;
	for(int i = 0; i < vecSize; i++) {
		ptr[i + 1] = oldVecPointer[i];
	}

	delete [] oldVecPointer;	// free memory of the old array
}		

/* push_back function, places the element in the next available space at the end of the array
*/
template <typename T>
void NDVector<T>::push_back(T element) {
	if(vecSize >= vecCapacity) {
		reallocate();			// increase capacity of array
	}
	ptr[vecSize] = element;		// set the current end of the array (with contents) to the element
	vecSize++;					// track that another element was added
}

/* pop_back function modeled after STL vector's pop_back method
 * Effectively removes the last item
 * By subtracting 1 from the vecSize variable, the client can no longer access the last element. 
 * It doesn't have to be wiped, just made no longer accessible. If the user does a push_back or 
 * a pop_back, it will simply overwrite this last value. 
*/
template <typename T>
void NDVector<T>::pop_back() {
	if(vecSize == 0) throw "Pop_back cannot be used on an empty NDVector";	// throw an exception for accessing an element that doesn't exist
	vecSize--;
}

/* Return the first element of the NDVector
 * No way to return a generic value if vecSize == 0
 */
template <typename T>
T NDVector<T>::getFirst() {
	return ptr[0];
}

/* Return the last element of the NDVector
 */
template <typename T>
T NDVector<T>::getLast() {
	return ptr[vecSize];
}

/* Clear the vector (from the user's perspective)
 * This method will set the size of the NDVector to 0, so that
 * the previously stored data can no longer be accessed. The array
 * will eventually fill up again as push_back is used, overwriting previous data
 */
template <typename T>
void NDVector<T>::clear() {
	vecSize = 0;
}

/* swap elements at two specified indicies in the NDVector
 */
template <typename T>
void NDVector<T>::swap(int index1, int index2) {
	T temp = ptr[index1];	// store value at index1 so the value isn't lost
	ptr[index1] = ptr[index2];
	ptr[index2] = temp;
}

/* remove the selected index from the array.
 * requires copying entire array, excluding the selected index
 */
template <typename T>
void NDVector<T>::erase(int indexToRemove) {
	// check for exceptions
	if(indexToRemove < 0) {
		throw "Cannot access a negative index of an NDVector";
	} else if (indexToRemove > vecSize) {
		throw "Specified index of NDVector does not exist";
	}

	T* oldVecPointer = ptr;		// point to the current array data so it doesn't get lost
	ptr = new T[vecCapacity];	// allocate a new array with the same capacity
	// copy over elements, excluding the indexToRemove
	for(int i = 0; i < vecSize; i++) {
		if(i < indexToRemove) ptr[i] = oldVecPointer[i];
		else if(i > indexToRemove) ptr[i -1] = oldVecPointer[i];
	}
	vecSize--;					// track that an element was successfully removed
	delete [] oldVecPointer;
}

/* operator+, used to concatenates two NDVectors, the current NDVector + a second NDVector
 * utilizes the push_back() method, which is sufficiently efficient, except in the case
 * where a very large second vector is added to a short vector, in which case multiple
 * reallocations would occur
*/
template <typename T>
void NDVector<T>::operator+=(const NDVector<T> &vec2) {
	// use push_back to append each element to the end of vec2 to this NDVector	
	for(int i = 0; i < vec2.size(); i++) {
		(*this).push_back(vec2[i]);
	}
}

/* opeator==, checks if two NDVectors are equavalent
*/
template <typename T>
bool NDVector<T>::operator==(const NDVector<T> &vec2) {
	if(vecSize != vec2.size()) return false;	// can't be equivalent if there are different numbers of elements
	for(int i = 0; i < vecSize; i++) {
		if(ptr[i] != vec2[i]) return false;
	}
	return true;
}

/* sort, implementing bubble sort algorithm
*/
template <typename T>
void NDVector<T>::sort() {
	for(int i = 0; i < vecSize; i++) {
		for(int j = 0; j < vecSize -1; j++) {
			if(ptr[j] > ptr[j+1]) {
				// swap elements
				T temp = ptr[j+1];
				ptr[j+1] = ptr[j];
				ptr[j] = temp;
			}
		}
	}
}
