#ifndef STUDENT_H_INCLUDED
#define STUDENT_H_INCLUDED

#include <iostream>
#include <string>

using namespace std;

enum Gender{
	MALE, FEMALE
};

class Student{
public:
	string sno;		//学号
	string sname;	//姓名
	Gender ssex;	//性别
	int sage;		//年龄

	float credit;
	float score;

	Student(string _sno, string _sname, Gender _ssex, int _sage)
	:sno(_sno),
	 sname(_sname),
	 ssex(_ssex),
	 sage(_sage)
	{
        credit = 0;
        score = 0;
	}
};

#endif // STUDENT_H_INCLUDED
