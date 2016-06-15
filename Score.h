#ifndef SCORE_H_INCLUDED
#define SCORE_H_INCLUDED

#include "Course.h"
#include "Student.h"
#include <cstdio>

class Score{
public:
	Course course;
	Student student;
	float score;

	Score(Course _course, Student _student, float _score)
	:course(_course),
	 student(_student),
	 score(_score)
	{}
};

#endif // SCORE_H_INCLUDED
