
#include <iostream>
#include "Student.h"

using namespace std;

Student::Student(){
  this->name = "null";
  this->GPA = 0.0;
}

Student::Student(string name, double GPA){
  this->name = name;
  this->GPA = GPA;
} 

void Student::setName(const string &name) {
  this->name = name;
}

void Student::setGPA(const double &GPA) {
  this->GPA = GPA;
}

string Student::getName() const {
  return this->name;
}

double Student::getGPA() const {
  return this->GPA;
}



