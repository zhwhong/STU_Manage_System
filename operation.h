#ifndef OPERATION_H_INCLUDED
#define OPERATION_H_INCLUDED

#include "Course.h"
#include "Score.h"
#include "Student.h"
#include <vector>
#include <fstream>
#include <cstdlib>
#include <cstdio>

using namespace std;

class Operation{
private:
	vector<Course> cvec;	//课程列表
	vector<Student> svec;	//学生列表
	vector<Score> scvec;	//成绩列表

public:
	Operation();
	~Operation() {}

	//管理功能
	void Search_stu(string sno);    //查询学生信息
    void add();
    void update();
    void del();
    void save();

    //查询功能
	void Search_sno(string sno);    //按学号查询学生成绩和学分信息
	void Search_cno(string cno);    //按课程查询某门课程的所有学生成绩

	//统计功能
	void Stat1();   //按课程统计不及格学生
	void Stat2();   //按课程将某门课的成绩排序
	void Stat3();   //按所有课程的总分排序
};

#endif // OPERATION_H_INCLUDED
