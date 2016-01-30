#ifndef __STUDENT_H__
#define __STUDENT_H__

#include <string>
using namespace std;


class Student {

 public:

//constructors
  Student();                                                                                                                                                                                                                                         
  Student(string name, double GPA);                                                                                                              

  void setName(const string &name);
  void setGPA(const double &gpa);
  string getName() const;
  double getGPA() const;

 private:

  string name;
  double GPA;

};

#endif


