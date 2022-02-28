/*minqueue.h*/

//
// Min queue that stores (key, value) pairs using a min-heap 
// implementation.  When pop is called, the key from the 
// (key, value) pair with the smallest value is returned; if 
// two pairs have the same value, the smaller key is returned.
// Push and pop have O(lgN) time complexity.
//
// << Kajimusugura Hoshino >>
//
// Original author: Prof. Joe Hummel
// U. of Illinois, Chicago
// CS 251: Fall 2019
// Project #07
//

#pragma once

#include <iostream>

#include <vector>

#include <exception>
#include <math.h>
#include <stdexcept>
#include <map>
using namespace std;

template < typename TKey, typename TValue >
  class minqueue {
    private:
      struct NODE {
        TKey Key;
        TValue Value;
      };
    
	
	vector <NODE> elements;
    map <TKey, int> keyMap;
    int heapSize;
    int Capacity;

    int getParentIndex(int i) { 
			
      return floor((i - 1) / 2);

    }

    int getLeftChildIndex(int i) { 
      return 2 * i + 1;

    }

    int getRightChildIndex(int i) {
      return 2 * i + 2;
    }

void siftUp(int nodeIndex) {

      int parentIndex;
      NODE tmp;

      if (nodeIndex != 0) { //making sure that the node has a parent
        parentIndex = getParentIndex(nodeIndex); //get the index of the parent node
		
		  //if a parent has a value greater than its child, swap with the child
        if (elements[parentIndex].Value > elements[nodeIndex].Value) { 
				
          tmp = elements[parentIndex];

          elements[parentIndex] = elements[nodeIndex];

          elements[nodeIndex] = tmp;

			//updating the map accordingly
          keyMap[elements[nodeIndex].Key] = nodeIndex;
			 keyMap[elements[parentIndex].Key] = parentIndex;
		
          siftUp(parentIndex);

        } 
		  //if parent has the same value as its child, then sort by key
		else if (elements[parentIndex].Value == elements[nodeIndex].Value) {
	
          //if the parent key is greater than its child's, swap
			if (elements[parentIndex].Key > elements[nodeIndex].Key) {
		
            tmp = elements[parentIndex];

            elements[parentIndex] = elements[nodeIndex];

            elements[nodeIndex] = tmp;

				//updating the map accordingly
            keyMap[elements[nodeIndex].Key] = nodeIndex;
				 keyMap[elements[parentIndex].Key] = parentIndex;

            siftUp(parentIndex);

          }
        }

      }

    }

void siftDown(int nodeIndex) {
	

      int leftChildIndex, rightChildIndex, minIndex;
      NODE tmp;
	//getting the index of the left child and the right child respectively
      leftChildIndex = getLeftChildIndex(nodeIndex);

      rightChildIndex = getRightChildIndex(nodeIndex);
//checking if the node has a child or not
      if (rightChildIndex >= heapSize) {

        if (leftChildIndex >= heapSize)

          return;

        else

          minIndex = leftChildIndex;

      } 
	else 
		{
//if the node has both the left and the right child, then get the minimum of the two
        if (elements[leftChildIndex].Value < elements[rightChildIndex].Value)
		

          minIndex = leftChildIndex;

         else if(elements[leftChildIndex].Value > elements[rightChildIndex].Value)

          minIndex = rightChildIndex;
		else{
			
		if (elements[leftChildIndex].Key <= elements[rightChildIndex].Key)
		

			  minIndex = leftChildIndex;

         else 

			  minIndex = rightChildIndex;
			
		}

      }

	//if the node has a value greater its either child, swap
   if (elements[nodeIndex].Value > elements[minIndex].Value) {

        tmp = elements[minIndex];

        elements[minIndex] = elements[nodeIndex];

        elements[nodeIndex] = tmp;
//updating the map accordingly
        keyMap[elements[nodeIndex].Key] = nodeIndex;
	   keyMap[elements[minIndex].Key] = minIndex;

        siftDown(minIndex);

      } 
	//if the value of the node is same as its either child, then sort by key
	else if (elements[nodeIndex].Value == elements[minIndex].Value) {

        if (elements[nodeIndex].Key > elements[minIndex].Key) {

          tmp = elements[minIndex];

          elements[minIndex] = elements[nodeIndex];

          elements[nodeIndex] = tmp;
//updating map accordingly
          keyMap[elements[nodeIndex].Key] = nodeIndex;
			 keyMap[elements[minIndex].Key] = minIndex;

          siftDown(minIndex);

        }
      }
	
    }

	//function to insert the (key,value) in heap and in the map
void insert(TKey key, TValue value) {
     

      heapSize++; //updating the heap size
      elements[heapSize - 1].Key = key;
      elements[heapSize - 1].Value = value;
      keyMap[key] = heapSize - 1;

      siftUp(heapSize - 1);
	
    }

 
void removeMin() {

      if (empty())

        throw string("Heap is empty");

      else {
        //removing the first element in the heap and in the map
        elements[0] = elements[heapSize - 1];
		keyMap[elements[0].Key] = 0;
        heapSize--; //updating the heap size after the removal

        if (heapSize > 0) 

          siftDown(0); //update the heap and the map

      }
	 
    }

public:
      //
      // default constructor:
      //
      // Queue has a max capacity for efficient implementation.
      // This max capacity must be specified at queue creation.
      //
minqueue(int capacity) { 
	elements.resize(capacity);
        heapSize = 0;
        Capacity = capacity;

      }

    //
    // fill constructor:
    //
    // This allows for the efficient O(N) construction of
    // a queue with an initial set of keys, all with the same
    // initial value.  The max capacity of the queue is                        
    // set to the # of keys provided for initialization;
    // it is assumed the keys are in ascending order.
    //
 minqueue(vector < TKey > keys, TValue initialValue) {
     
	 for (size_t i = 0; i < keys.size(); i++) {
        NODE pair;
		 
		 //filling heap
        pair.Key = keys.at(i);
        pair.Value = initialValue;
        elements.push_back(pair);
		 //filling map
		keyMap.emplace(elements[i].Key, i);
			
      }
      heapSize = keys.size(); //setting the size of the heap
    }

    //
    // destructor:
    //
 virtual~minqueue() {
	
    }

    //
    // empty:
    //
    // Returns true if empty, false if not.
    //
bool empty() {
      return (heapSize == 0);
    }

void delete_p(TKey key){
	
	int p = keyMap[key]; //get the index of the key and its corresponding value
	
	//if p is the last index, then just reduce the size of the heap and return
	if(p == heapSize-1){ 
		keyMap.erase(key);
		heapSize--;
		return;
	}

	else{
		elements[p] = elements[heapSize-1]; //move the last element to the position p 
		 
		heapSize--; //update the heap size
		keyMap[elements[p].Key] = p; //update map
		siftUp(p); //update the heap
		siftDown(p); //update the heap
		keyMap.erase(key); //erase the corresponding (key,value) in map
}
	

	
}

    //
    // push:
    //
    // Inserts the given (key, value) pair into the queue such that 
    // pop always returns the pair with the minimum value.  If the 
    // key is *already* in the queue, it's value is updated to the
    // given value and the queue reordered.  If the key is not in
    // the queue, the (key, value) pairs is added and the queue
    // reordered.
    //
    // NOTE: if two keys have the same value, i.e. (key1, value) and
    // (key2, value), then those pairs are ordered into ascending value
    // by their key.
    //
 void pushinorder(TKey key, TValue value) {
	  
	 
      if (heapSize == Capacity) //check if the heap can still be populated or not
        throw runtime_error("minqueue::pushinorder: queue full");
      else {
		 
		  if(keyMap.find(key) == keyMap.end()){ //if the key is not already in the map, insert the (key,value)
			insert(key, value);
		  }
		  else{ //if the key is already there, delete that (key,value), and insert the new (key,value)
			  delete_p(key);

			  insert(key,value);
			  
		  }
		  
      }
	 
    }

//
// front:
//
// Returns the key at the front of the queue; does *not* pop the 
// (key, value) pair.  Throws a logic_error exception if the queue
// is empty.
//
TKey minfront() {

  if (empty()) {
    throw logic_error("minqueue::minfront: queue empty");
  } 
    return elements[0].Key; //return the top element
  

}

//
// pop:
//
// Pops and discards the (key, value) pair at the front of the queue.
// Throws a logic_error exception if the queue is empty.
//
void minpop() {
	if (empty()) {
    throw logic_error("minqueue::minpop: queue empty");
  } else {
    removeMin();
  }
}
};

