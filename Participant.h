//
// Created by Yuan on 2023/12/28.
//


#ifndef PARTICIPANT_H
#define PARTICIPANT_H

#include <iostream>
#include <string>
#include <cstring>
#include <vector>
using namespace std;
// Define the participant structure
struct Participant {
    int gender;
    int age;
    int grade;
    int school;
    int campus;
    int major;
    int height;
    int weight;
    int appearance;
    int mbti_flag;
    string mbti;
    int num_hobbies;
    vector<int> hobbies;
    int num_characteristics;
    vector<int> characteristic;
    string hometown;
    int expect_gender;
    int expect_age;
    int expect_grade;
    int expect_school;
    int expect_campus;
    int expect_major;

    int has_received = -1;
    bool has_been_received = false;
    bool nice_matching = false;

    vector<int> expect_height;
    vector<int> expect_weight;
    vector<int> expect_appearance;
    string expect_mbti;
    int expect_num_characteristics;
    vector<int> expect_characteristic;
    string expect_hometown;
    vector<int> significance_score;
};
#endif //JSONL_TEST_PARTICIPANT_H
