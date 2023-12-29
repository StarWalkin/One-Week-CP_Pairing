//
// Created by Yuan on 2023/12/28.
//

#ifndef SCORING_UTIL_H

#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include "Participant.h"
using namespace std;
double age_scoring(Participant p1, Participant p2);
//double grade_scoring(Participant p1, Participant p2);
//double school_scoring(Participant p1, Participant p2);
//double campus_scoring(Participant p1, Participant p2);
//double major_scoring(Participant p1, Participant p2);
double height_scoring(Participant p1, Participant p2);
double weight_scoring(Participant p1, Participant p2);
double appearance_scoring(Participant p1, Participant p2);
double mbti_scoring(Participant p1, Participant p2);
double hobbies_scoring(Participant p1, Participant p2);
double characteristics_scoring(Participant p1, Participant p2);
//double hometown_scoring(Participant p1, Participant p2);

double pairs_scoring(double **attr_matrix, int **pairing_matrix, int overall_num);
#define SCORING_UTIL_H

#endif //JSONL_TEST_SCORING_UTIL_H
