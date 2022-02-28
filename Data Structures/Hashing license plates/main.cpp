/*main.cpp*/

//
// Hashing program for specialized Illinois license plates,
// which processes an input file of license plates and fines.
// The output is the total fines per license plate, in 
// sorted order.
//
// Original author: Prof. Joe Hummel
// Modified by:     << Kajimusugura Hoshino >>
//
// U. of Illinois, Chicago
// CS 251: Fall 2019
// Project 05
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <cassert>

#include "ILplates.h"

using namespace std;


//
// hashInput:
//
//function to sort the plates
void plateSort(vector<string> &keys, vector<int> &values){
	string tempk = "";
	int tempv = 0;
	for (size_t i = 0; i < keys.size(); ++i) {
    
   // Find index of smallest remaining element
   int indexSmallest = i;
   for (size_t j = i + 1; j < keys.size(); ++j) {
        
      if (keys.at(j).compare(keys.at(indexSmallest)) < 0) {
         indexSmallest = j;
      }
   }
    
   // Swapping keys
   tempk = keys.at(i);
   keys.at(i) = keys.at(indexSmallest);
   keys.at(indexSmallest) = tempk;
	//swapping values 	
  tempv = values.at(i);
  values.at(i) = values.at(indexSmallest);
  values.at(indexSmallest) = tempv;
}
	} 


void hashInput(string basename, ILplates& hashplates)
{
  string infilename = basename + ".txt";
  ifstream infile(infilename);

	//checking if the file can be openend or not 
  if (!infile.good())
  {
    cout << endl;
    cout << "**Error: unable to open input file '" << infilename << "', exiting." << endl;
    cout << endl;
    exit(-1);
  }

	
  //
  // input the plates and fines:
  //
  cout << "Reading '" << infilename << "'..." << endl;

  string fine;
  string plate;
  

  getline(infile, fine);
	
  

  //
  // for each pair (fine, license plate), hash and store/update fine:
  //
  while (!infile.eof())
  {
    getline(infile, plate);
	
	

    // 
    // is plate valid?  Only process valid plates:
    //
    
    if (hashplates.Hash(plate) >= 0)  // yes:
    { 
      int amount = hashplates.Search(plate);

      if (amount < 0)  // not found:
      { 
        hashplates.Insert(plate, stoi(fine));
      }
      else  // we found it, so update total in hash table:
      { 
        amount += stoi(fine);
        hashplates.Insert(plate, amount);
      }
   
    }
	  getline(infile, fine);//valid


  }
}


int main()
{
  int    N;        // = 10000;
  string basename; // = "tickets1";

  cout << "Enter hashtable size> ";
  cin >> N;

  hashtable<string, int>  ht(N);
  ILplates                hashplates(ht);

  cout << "Enter base filename> ";
  cin >> basename;
  cout << endl;

  //
  // process input file of fines and license plates:
  //
  hashInput(basename, hashplates);

  //
  // debugging:
  //
  vector<string> plates = ht.Keys();
  vector<int> amounts = ht.Values();
   
	
	plateSort(plates, amounts); //calling the sorting function

 //printing the data on the output file 
ofstream outfile(basename+"-output.txt"); 
 for (size_t i = 0; i < plates.size(); ++i)
  {
    outfile << "\"" << plates[i] << "\""<< " $" << amounts[i] << endl;
	 }

  return 0;
}