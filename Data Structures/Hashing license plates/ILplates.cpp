/*ILplates.cpp*/

//
// Hashing functions to store (license plate, amount) pairs
// using linear probing.
//
// << Kajimusugura Hoshino >>
// U. of Illinois, Chicago
// CS 251: Fall 2019
// Project 05
//

#include <iostream>
#include <string>
#include <math.h>

#include "ILplates.h"

using namespace std;


//
// Hash:
//
// Given a specialized Illinois license plate, returns an index into
// the underyling hash table.  If the given plate does not follow the
// formatting rules given below, -1 is returned.
//
// Personalized:
//   letters and numbers, with a space between the letters 
//   and numbers.  Format: 1-5 letters plus 1..99 *OR* 
//   6 letters plus 1..9
//
//   Examples: A 1, B 99, ZZZZZ 1, ABCDEF 3
//
// Vanity:
//   Format: 1-3 numbers *OR* 1-7 letters
// 
//   Examples: 007, 1, 42, X, AAA, ZZZEFGH
//
bool isCap(char letter){ //function to check if the alphabet is a capital letter or not
	
	if(letter >= 'A' && letter <= 'Z'){
		return true;
    }
	
	return false;
}

//function that checks the validity of the personalized number plate
bool isPersonalized(string plate){
    
	int space = -1;
	bool check1 = false;
	bool check2 = true;
	bool check3 = true;
	bool check4 = false;
	
	int len = plate.length();
	for(int i = 0; i < len; i++){ //getting the index where we find the space
		
		if(isspace(plate[i])){
			space = i;
			break;
		}
		
	}

	
	if(space == -1){ //if there is no space in the plate number entered by the user
		return false;
	}

	if((len >= 3) && (len <=8)){ 
		check1 = true;
	} 
	string pre = plate.substr(0,space); //string before the space
	string post = plate.substr(space+1, len); //string after the space
	
	if((pre.length() >= 1) && (pre.length() <= 5) && (post.length() >= 1) && (post.length() <= 2)){
		check4 = true;
	}
	
	else if((pre.length() == 6) && (post.length() == 1)){
		check4 = true;
	}
	
	
	//checking if the characters before the space are capital alphabets or not
	for(int i = 0; i <= space-1; i++){
		if((!isalpha(pre[i])) || (!isCap(pre[i]))) {
			check2 = false;
			break;
		}
	}
	//checking if the characters after the space are digits or not
	for(size_t i = 0; i < post.length(); i++){
		if(!isdigit(post[i])){
			check3 = false;
			break;
		}
	}

	if((check1 == true) && (check2 == true) && (check3 == true) && (check4 == true)){
		return true;
	}
	
	return false;
}

//function to check the validity of the vanity type number plate
bool isVanity(string plate){
	
	
	int len = plate.length();
	

	bool check1 = true;
	bool check2 = true;
	 //checking if the plate number is all digits
		for(int i = 0; i < len; i++){
			
			if(!isdigit(plate[i])){
		check1 = false;
				break;
		}}
	if((check1 == true ) && (len >= 1) && (len <= 3)){
		return true;
	}
	
	//checkinng if the plate number is all alphabets
		
		for(int i = 0; i < len; i++){
			if((!isalpha(plate[i])) || (!isCap(plate[i]))){
				check2 = false;
				break;
			}}
		if((check2 == true) && (len >= 1) && (len <= 7)){
			return true;
		}

	

	return false;
}
		

int ILplates::Hash(string plate)
{ 
  long long int index = 0;
  int len = plate.length(); //gettting the length of the plate

  if((isPersonalized(plate)) || (isVanity(plate))){ //checking the validity of the plate number
	  
	  for(int i = 0; i < len; i++){ //removing the space from the plate number
		  if(isspace(plate[i])){
			  plate.erase(plate.begin() + i);
			  break;
		  }
	  }
	  for(int i = len-1; i >= 0 ; i--){ //hashing the index of a digit 
	  
		  if(isdigit(plate[i])){
			  index += (plate[i] - 46) * pow(36, i+1); 
		  }
	  }
	  
	  for(int i = len-1; i >= 0 ; i--){ //hashing the index of a letter
	  
		  if(isalpha(plate[i])){
			  index += (plate[i] - 64) * pow(36, i); 
		  }
	  }
	  
	  
	  return index % HT.Size();
  }

	 
  return -1; //returns -1 if the plate is not valid
}


//
// Search
// 
// Hashes and searches for the given license plate; returns the 
// associated value for this plate if found, or -1 if not found.
//
int ILplates::Search(string plate)
{
 
 
  int index = Hash(plate); //hashing the plate number to get an index
	
	bool check;
	string plateName;
	int fine;
  
   
    int found = -1;
	
	HT.Get(index, check, plateName, fine); //Getting the data from the given index of the hash table
   while(check == false) //while the spot is not empty 
    {  
	       
	   if((plateName == plate)){ //if the plate number we are looking for is found
          found= fine;
           return found;
       }
	index = index + 1;
	 if(index == HT.Size()){ //setting the index back to zero if the program falls out of the hash table
		 index = 0;
	 }
	 
	   HT.Get(index, check, plateName, fine);
    }
	 
	return found;

}


//
// Insert
//
// Inserts the given (plate, newValue) into the hash table,
// overwriting an existing value if there.
//
void ILplates::Insert(string plate, int newValue)
{ 

	int index = -1;
	index = Hash(plate);
	
	bool check;
	string plateName;
	int fine;
   HT.Get(index, check, plateName, fine);
 while(check == false){ //while the spot is not empty
	 if(plateName == plate){ 
		 break;
	 }
	 index = index + 1;
	 if(index == HT.Size()){ //setting the index back to zero if the program falls out of the hash table
		 index = 0;
	 }
	 HT.Get(index, check, plateName, fine);
	 
 }
	  HT.Set(index, plate, newValue); // Sets the location of the hash table to contain the given key and value
	


}

