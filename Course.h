#ifndef COURSE_H_INCLUDED
#define COURSE_H_INCLUDED

#include <iostream>
#include <string>

using namespace std;

class Course{
public:
	string cno;		//课程号
	string cname;	//课程名
	float ccredit;	//学分

	Course(string _cno, string _cname, float _ccredit)
	:cno(_cno),
	 cname(_cname),
	 ccredit(_ccredit)
	{}
};

#endif // COURSE_H_INCLUDED
