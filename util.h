//
// Created by Yuan on 2023/12/28.
//

#ifndef JSONL_TEST_UTIL_H
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include "Participant.h"
#include <algorithm>
double calculateAverage(double **attr_matrix, int rows, int cols);
double calculateMedian(double **attr_matrix, int rows, int cols);
void randomSplit(std::vector<int>& input, std::vector<int>& group1, std::vector<int>& group2);
int* pairing(vector<Participant> participants, vector<int> group1, vector<int> group2, double **attr_matrix, double threshold);
void swapRandomElements(std::vector<int>& array1, std::vector<int>& array2);
void cross(vector<int> &boy_homo1, vector<int> &boy_homo2, vector<int> &girl_homo1, vector<int> &girl_homo2);
#define JSONL_TEST_UTIL_H

#endif //JSONL_TEST_UTIL_H
