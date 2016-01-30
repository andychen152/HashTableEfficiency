#include "Hashtable.h"
#include <iomanip>

using namespace std;


// Constructor
Hashtable::Hashtable(){
  this->currentElements=0;
  this->TABLE_SIZE=5;
  this->linearMode = this->printSuccess = this->printSuccessSecond=true;
  this->myHashTable = new pair<int, Student*>[TABLE_SIZE];
  for(int i=0; i<TABLE_SIZE; i++){
    myHashTable[i].first=-1;
    myHashTable[i].second=NULL;
  }
}

void Hashtable::insert(const int &perm, Student *newStudent){
  printSuccessSecond=false;
  bool addItem = lookup(perm);
  printSuccessSecond=true;

  // item is not in hash and we need to add
  if(!addItem){
    // linear hashing algorithm
    if(((double)this->currentElements+1)/(double)this->TABLE_SIZE > 0.7 && printSuccess){
      reSize();
      cout << "table doubled" << endl;
    }
    int hash = hash1(perm);
    if(this->linearMode){
      while(myHashTable[hash].first>-1 && myHashTable[hash].first != perm)
        hash = (hash+1)%TABLE_SIZE;
      myHashTable[hash].first = perm;
      myHashTable[hash].second = newStudent;
      if(printSuccess)
        cout << "item successfully inserted" << endl;
    }
    // double hasing
    else {
      int origHash = hash;
      int i=1;
      while(myHashTable[hash].first>-1 && myHashTable[hash].first != perm){
        hash = (origHash + hash2(perm)*i)%TABLE_SIZE;
        i++;
      }
      myHashTable[hash].first = perm;
      myHashTable[hash].second = newStudent;
      if(printSuccess)
        cout << "item successfully inserted" << endl;
    }
    this->currentElements++;
  }
  else
    cout << "item already present" << endl;
}

bool Hashtable::lookup(const int &perm) {
  bool result;
  int hash = hash1(perm);
  int origHash = hash;
  int counter=0;
  while(counter < TABLE_SIZE && !(myHashTable[hash].first == -1 ^ myHashTable[hash].first == perm)){   
    counter++;
    if (this->linearMode)
      hash=(hash+1)%TABLE_SIZE;
    else
      hash = (origHash + hash2(perm)*counter) % TABLE_SIZE;
  }
  if(counter>=TABLE_SIZE || myHashTable[hash].first==-1){
    if(printSuccessSecond)
      cout << "item not found" << endl;
    result = false;
    }
   else {
      if(printSuccessSecond)
        cout << "item found; " << myHashTable[hash].second->getName() << " " << hash << endl;    
      result = true;
    }
  return result;
}

void Hashtable::print() const{
  for(int i=0; i<TABLE_SIZE; i++){
    if(myHashTable[i].first>-1){
      cout <<"("<<myHashTable[i].first<<","
           << myHashTable[i].second->getName() << ","; 
      cout << fixed << setprecision(1) << myHashTable[i].second->getGPA();
      cout << ")"; 
    }
  }
  cout << endl;
}

bool Hashtable::isPrime(const int &x) {
  for(int i=2; i<x; ++i){
    if(x%i==0)
      return false;
  }
  return true;
}

void Hashtable::remove(int perm){
  int hash = hash1(perm);
  int origHash = hash;
  int counter = 0;
  // if removing in linear probling
  while(counter < TABLE_SIZE && myHashTable[hash].first!=-1 && myHashTable[hash].first!=perm) { 
    if(linearMode)
      hash = (hash+1)%TABLE_SIZE;
    //double hash alrgorithm
    else
      hash = (origHash+(counter+1)*hash2(perm))%TABLE_SIZE;
    counter++;   
  }
  //item not present as counter looped through whole table or hits -1
  if (counter>=TABLE_SIZE || myHashTable[hash].first==-1)
    cout << "item not present in the table" << endl;
  // item found
  else {
    delete myHashTable[hash].second;
    myHashTable[hash].second = NULL;
    myHashTable[hash].first = -10;
    cout << "item successfully deleted" << endl;
    currentElements--;
  }
}

void Hashtable::primeAfter(){
  int newTableSize = this->TABLE_SIZE*2+1;
  while(!isPrime(newTableSize))
    newTableSize+=2;
  this->TABLE_SIZE=newTableSize;
}

void Hashtable::reSize(){
  int oldTableSize = this->TABLE_SIZE;
  primeAfter();
  pair<int, Student*> * newHashTable = new pair<int, Student*>[TABLE_SIZE];
  pair<int, Student*> * oldHashTable = myHashTable;
  this->myHashTable = newHashTable;
  currentElements=0;
  for(int i=0; i<TABLE_SIZE; i++){
    myHashTable[i].first=-1;
    myHashTable[i].second=NULL;
  }
  for(int i=0; i<oldTableSize; i++){
    if (oldHashTable[i].first>-1){
      printSuccess=false;
      insert(oldHashTable[i].first, oldHashTable[i].second);
      printSuccess=true;
    }
  }
  delete[] oldHashTable;
}











