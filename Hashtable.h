#ifndef __HASHTABLE_H__
#define __HASHTABLE_H__

#include <utility>
#include <string>
#include <iostream>
#include <iomanip>
#include "Student.h"

using namespace std;

class Hashtable {
 private:

  pair<int, Student*> * myHashTable;
  bool printSuccess;
  bool printSuccessSecond;
  int TABLE_SIZE;
  bool linearMode;
  int currentElements;


 public:

  //constructor                                                                                                                                              
  Hashtable();                                                                                                                                             
  void insert(const int &perm, Student *newStudent);
  bool lookup(const int &perm);
  void remove(int perm);
  void reSize();
  void print() const;
  bool isPrime(const int &x);
  void primeAfter();
  void setLinearMode(bool mode){this->linearMode=mode;}
  int getTableSize(){return this->TABLE_SIZE;}
  int hash1(const int &num){return (num%492113)%this->TABLE_SIZE;}
  int hash2(const int &num){
    int x = (num%392113)%this->TABLE_SIZE;
    if (x==0)
      return 1;
    else
      return x;
  }
};

#endif