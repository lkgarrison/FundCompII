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
		NDVector(int initSize = 10);	// constructor, fallback of 10 elements
		NDVector(const NDVector<T> &); 	// copy constructor
		~NDVector();					// deconstructor
		const NDVector<T> & operator=(const NDVector<T> &); // set NDVector equal to the other NDVector
		T& operator[](int index) const;	// random access operator
		int size() const;				// returns size of array (different from capacity)
		int capacity() const;					// returns capacity of the NDVector
		void reallocate();				// allocate 2x the capacity of the previous array
		void push_back(T element); 		// append element to the end of the NDVector
		void push_front(T element);		// place element at the front of the array (copy all elements to new array required)
		void pop_back();				// remove the last element from the array
		T getFirst();					// return the first element in the array
		T getLast();					// return the last element in the array
		void clear();					// clear the vector (doesn't clear its memory)
		void swap(int index1, int index2);	// swap values at two indicies in the array

	private:
		T* ptr;					// pointer to first element of array of type T which is the basic data structure of the class4
		int vecSize;
		int vecCapacity;
};

#endif

/* Constructor
 * Allocates space for the array
 * Will allocate 2 * the required space for the number of desired elements in the array
*/
template <typename T>
NDVector<T>::NDVector(int initSize) {
	vecCapacity = 2 * initSize;	// set capactiy data member
	ptr = new T[vecCapacity];	// allocate space for the
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
	if(index < 0 || index > vecSize) cout << "Error: Index " << index << " of NDVector is an invalid index." << endl;
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

