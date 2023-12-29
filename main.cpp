#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#include "Participant.h"
#include "scoring_util.h"
#include "util.h"

using json = nlohmann::json;
using namespace std;



int main() {

    vector<Participant> participants;

    //存储各类性取向的参与者标号
    vector<int> boy_hetero;
    vector<int> girl_hetero;
    vector<int> boy_homo;
    vector<int> girl_homo;


    //边读取jsonl文件边计数
    int data_counter = 0;


    // 读取JSONL文件
    ifstream inputFile("/Users/yuan/PycharmProjects/lover_data_generation/testdata_matching.jsonl");

    if (!inputFile.is_open()) {
        cerr << "Error opening file." << endl;
        return 1;
    }

    // 逐行读取JSONL文件
    string line;
    while (getline(inputFile, line)) {
        // 解析JSON
        try {
            json jsonData = json::parse(line);
            Participant curr_part = Participant();
            //get the characteristics of the participant
            curr_part.age = jsonData["age"];
            curr_part.age = jsonData["age"];
            curr_part.gender = jsonData["gender"];
            curr_part.grade = jsonData["grade"];
            curr_part.school = jsonData["school"];
            curr_part.campus = jsonData["campus"];
            curr_part.major = jsonData["major"];
            curr_part.height = jsonData["height"];
            curr_part.weight = jsonData["weight"];
            curr_part.appearance = jsonData["appearance"];
            curr_part.mbti_flag = jsonData["mbti_flag"];
            curr_part.mbti = jsonData["mbti"];

            curr_part.num_hobbies = jsonData["num_hobbies"];
            // Parse hobbies array
            for (const auto &hobby: jsonData["hobbies"]) {
                curr_part.hobbies.push_back(hobby);
            }

            curr_part.num_characteristics = jsonData["num_characteristics"];

            // Parse characteristics array
            for (const auto &characteristic: jsonData["characteristic"]) {
                curr_part.characteristic.push_back(characteristic);
            }

            curr_part.hometown = jsonData["hometown"];
            curr_part.expect_gender = jsonData["expect_gender"];
            curr_part.expect_age = jsonData["expect_age"];
            curr_part.expect_grade = jsonData["expect_grade"];
            curr_part.expect_school = jsonData["expect_school"];
            curr_part.expect_campus = jsonData["expect_campus"];
            curr_part.expect_major = jsonData["expect_major"];

            // Parse expect_height array
            for (const auto &height: jsonData["expect_height"]) {
                curr_part.expect_height.push_back(height);
            }

            // Parse expect_weight array
            for (const auto &weight: jsonData["expect_weight"]) {
                curr_part.expect_weight.push_back(weight);
            }

            // Parse expect_appearance array
            for (const auto &appearance: jsonData["expect_appearance"]) {
                curr_part.expect_appearance.push_back(appearance);
            }

            curr_part.expect_mbti = jsonData["expect_mbti"];
            curr_part.expect_num_characteristics = jsonData["expect_num_characteristics"];

            // Parse expect_characteristic array
            for (const auto &expect_characteristic: jsonData["expect_characteristic"]) {
                curr_part.expect_characteristic.push_back(expect_characteristic);
            }

            curr_part.expect_hometown = jsonData["expect_hometown"];

            // Parse significance_score array
            for (const auto &score: jsonData["significance_score"]) {
                curr_part.significance_score.push_back(score);
            }

            // 将当前参与者添加到参与者向量
            participants.push_back(curr_part);

            // 输出一些数据以验证
            cout << "Participant " << data_counter << ":" << endl;
            cout << "Age: " << curr_part.age << endl;
            cout << "Gender: " << curr_part.gender << endl;
            cout << "mbti: " << curr_part.mbti << endl;
//            for (const auto& score : curr_part.significance_score) {
//                cout << score << " ";
//            }
//            cout << endl;

            // 输出其他字段...

            // 性取向归类
            if (curr_part.gender == 1 && curr_part.expect_gender == 2) boy_hetero.push_back(data_counter);
            if (curr_part.gender == 2 && curr_part.expect_gender == 1) girl_hetero.push_back(data_counter);
            if (curr_part.gender == 1 && curr_part.expect_gender == 1) boy_homo.push_back(data_counter);
            if (curr_part.gender == 2 && curr_part.expect_gender == 2) girl_homo.push_back(data_counter);
            // 增加计数
            data_counter++;
        } catch (const exception &e) {
            cerr << "Error parsing JSON: " << e.what() << endl;
        }
    }

    // 关闭文件
    inputFile.close();

    cout << participants.size() << endl;
//    for (const auto& idx : boy_hetero) {
//       cout << idx << " ";
//    }

    //  不同性取向的人数，便于后续构造矩阵
    int boy_hetero_cnt = boy_hetero.size();
    int girl_hetero_cnt = girl_hetero.size();
    int boy_homo_cnt = boy_homo.size();
    int girl_homo_cnt = girl_homo.size();


    int overall_num = participants.size();
    // 动态分配内存创建矩阵
    int **pairing_matrix = new int *[overall_num]; // 创建包含m个指针的数组

    for (int i = 0; i < overall_num; ++i) {
        pairing_matrix[i] = new int[overall_num]; // 为每一行创建一个包含n个整数的数组
    }

    // 将每个元素初始化为0
    for (int i = 0; i < overall_num; ++i) {
        for (int j = 0; j < overall_num; ++j) {
            pairing_matrix[i][j] = 0;
        }
    }

    // 动态分配内存创建矩阵
    double **attr_matrix = new double *[overall_num]; // 创建包含m个指针的数组

    for (int i = 0; i < overall_num; ++i) {
        attr_matrix[i] = new double[overall_num]; // 为每一行创建一个包含n个整数的数组
    }

    // 将每个元素初始化为0
    for (int i = 0; i < overall_num; ++i) {
        for (int j = 0; j < overall_num; ++j) {
            attr_matrix[i][j] = 0;
        }
    }



    //calculate attractiveness
    for (int idx1 = 0; idx1 < overall_num; idx1++) {
        for (int idx2 = 0; idx2 < overall_num; idx2++) {
            if (idx1 != idx2) {
                if (participants[idx1].gender != participants[idx2].expect_gender ||
                    participants[idx2].gender != participants[idx1].expect_gender) {
                    continue;
                }
                //年龄的匹配度
                double age_score = age_scoring(participants[idx1], participants[idx2]);
                if (age_score == -100) {
                    continue;
                }
                //年级的匹配度
                if (participants[idx2].grade != participants[idx1].expect_grade &&
                    participants[idx1].significance_score[1] == 10) {
                    continue;
                } else if (participants[idx2].grade == participants[idx1].expect_grade) {
                    age_score += 10 * 1.0 * participants[idx1].significance_score[1] / 10;
                } else {
                    age_score += (-3) * 1.0 * participants[idx1].significance_score[1] / 10;
                }

                //学校的匹配度
                double school_score = 0;
                if (participants[idx2].school != participants[idx1].expect_school &&
                    participants[idx1].significance_score[2] == 10) {
                    continue;
                } else if (participants[idx2].school == participants[idx1].expect_school) {
                    school_score += 10 * 1.0 * participants[idx1].significance_score[2] / 10;
                } else {
                    school_score += (-3) * 1.0 * participants[idx1].significance_score[2] / 10;
                }

                //校区的匹配度
                double campus_score = 0;
                if (participants[idx2].campus != participants[idx1].expect_campus &&
                    participants[idx1].significance_score[3] == 10) {
                    continue;
                } else if (participants[idx2].campus == participants[idx1].expect_campus) {
                    campus_score += 10 * 1.0 * participants[idx1].significance_score[3] / 10;
                } else {
                    campus_score += (-3) * 1.0 * participants[idx1].significance_score[3] / 10;
                }

                //专业的匹配度
                double major_score = 0;
                if (participants[idx2].major != participants[idx1].expect_major &&
                    participants[idx1].significance_score[4] == 10) {
                    continue;
                } else if (participants[idx2].major == participants[idx1].expect_major) {
                    major_score += 10 * 1.0 * participants[idx1].significance_score[4] / 10;
                } else {
                    major_score += (-3) * 1.0 * participants[idx1].significance_score[4] / 10;
                }

                //身高的匹配度
                double height_score = height_scoring(participants[idx1], participants[idx2]);
                if (height_score == -100) {
                    continue;
                }

                //体重的匹配度
                double weight_score = weight_scoring(participants[idx1], participants[idx2]);
                if (weight_score == -100) {
                    continue;
                }

                //外貌的匹配度
                double appearance_score = appearance_scoring(participants[idx1], participants[idx2]);
                if (appearance_score == -100) {
                    continue;
                }

                //MBTI的匹配度
                double mbti_score = mbti_scoring(participants[idx1], participants[idx2]);
                if (mbti_score == -100) {
                    continue;
                }

                //hobbies的匹配度
                double hobbies_score = hobbies_scoring(participants[idx1], participants[idx2]);
                if (hobbies_score == -100) {
                    continue;
                }

                //characteristics的匹配度
                double characteristics_score = characteristics_scoring(participants[idx1], participants[idx2]);
                if (characteristics_score == -100) {
                    continue;
                }

                //家乡的匹配度
                double hometown_score = 0;
                if (participants[idx2].hometown != participants[idx1].expect_hometown &&
                    participants[idx1].significance_score[11] == 10) {
                    continue;
                } else if (participants[idx2].hometown == participants[idx1].expect_hometown) {
                    hometown_score += 10 * 1.0 * participants[idx1].significance_score[11] / 10;
                } else {
                    hometown_score += (-3) * 1.0 * participants[idx1].significance_score[11] / 10;
                }

                //总分
                double total_score =
                        age_score + school_score + campus_score + major_score + height_score + weight_score +
                        appearance_score + mbti_score + hobbies_score + characteristics_score + hometown_score;

                //规范化：除以significance_score[10]的的L2范数
                double norm = 0;
                for (int i = 0; i < 10; i++) {
                    norm += participants[idx1].significance_score[i] * participants[idx1].significance_score[i];
                }
                norm = sqrt(norm);
                total_score = total_score / norm;
                //将总分存入attr_matrix
                attr_matrix[idx1][idx2] = total_score;
                //attr_matrix[idx1][idx2]存着的就是idx1对idx2的感觉如何（从idx1的视角看）
            }
        }
    }

//    //输出吸引力矩阵看一眼
//    for (int i = 0; i < overall_num; i++) {
//        for (int j = 0; j < overall_num; j++) {
//            cout << attr_matrix[i][j] << " ";
//        }
//        cout << endl;
//    }

    //pairing
    int *cnt1 = pairing(participants, boy_hetero, girl_hetero, attr_matrix, pairing_matrix, 0.5);

    //接下来处理同性恋的情况
    //男同随机均分成两组
    vector<int> boy_homo1;
    vector<int> boy_homo2;
    randomSplit(boy_homo, boy_homo1, boy_homo2);
    //print boy_homo1 and boy_homo2
    for(int num:boy_homo1){
        cout << num << " ";
    }
    cout << endl;
    for(int num:boy_homo2){
        cout << num << " ";
    }
    cout << endl;

    int *cnt2 = pairing(participants, boy_homo1, boy_homo2, attr_matrix, pairing_matrix, 0.3);


    //女同做一样的处理
    vector<int> girl_homo1;
    vector<int> girl_homo2;
    randomSplit(girl_homo, girl_homo1, girl_homo2);
    //print boy_homo1 and boy_homo2
    for(int num:girl_homo1){
        cout << num << " ";
    }
    cout << endl;
    for(int num:girl_homo2){
        cout << num << " ";
    }
    cout << endl;

    int *cnt3 = pairing(participants, girl_homo1, girl_homo2, attr_matrix, pairing_matrix, 0.3);

    int generation = 10;
    double score;
    //evolution
    double max_score = -100;
    for(int gen = 0; gen<generation; gen++){
        //先保存一下四个向量的拷贝
        vector<int> prev_boy_homo1 = boy_homo1;
        vector<int> prev_boy_homo2 = boy_homo2;
        vector<int> prev_girl_homo1 = girl_homo1;
        vector<int> prev_girl_homo2 = girl_homo2;


        cross(boy_homo1,boy_homo2,girl_homo1,girl_homo2);
        cnt2 = pairing(participants, boy_homo1, boy_homo2, attr_matrix, pairing_matrix, 0.3);
        cnt3 = pairing(participants, girl_homo1, girl_homo2, attr_matrix, pairing_matrix, 0.3);
        int nice_matching_cnt = cnt1[1] + cnt2[1] + cnt3[1];
        double nice_matching_rate = 1.00*nice_matching_cnt/(cnt1[2]+cnt2[2]+cnt3[2]);
        int paired_count = cnt1[0] + cnt2[0] + cnt3[0];
        double paired_rate = 1.00*paired_count/overall_num;

        double curr_score = 0.5*paired_rate + 0.5*nice_matching_rate;
        if(curr_score <= max_score){
            boy_homo1 = prev_boy_homo1;
            boy_homo2 = prev_boy_homo2;
            girl_homo1 = prev_girl_homo1;
            girl_homo2 = prev_girl_homo2;
            cout << "prev:" << max_score << endl;
            cout << "new:" << curr_score << endl;
            cout << "进化变差" << endl;

        }
        else {
            cout << "prev:" << max_score << endl;
            cout << "new:" << curr_score << endl;
            score = curr_score;
            max_score = curr_score;
            cout << "进化变优" <<endl;

        }
    }
    int nice_matching_cnt = cnt1[1] + cnt2[1] + cnt3[1];
    double nice_matching_rate = 1.00*nice_matching_cnt/(cnt1[2]+cnt2[2]+cnt3[2]);
    int paired_count = cnt1[0] + cnt2[0] + cnt3[0];
    double paired_rate = 1.00*paired_count/overall_num;

    score = 0.5*paired_rate + 0.5*nice_matching_rate;
    //print the rates and score
    cout << "paired:" << paired_count << " " << paired_rate << endl;
    cout << "nice matching" << nice_matching_rate << endl;
    cout << "score:" << score << endl;

    //检查一下匹配的组合中有没有不合理的




    //释放动态内存
    return 0;
}






//
//    struct participant {
//        string name;
//
//        int gender;
//
//        //学校
//        int school;
//        //校区
//        int campus;
//        //期待对方的学校和校区
//        int expect_school;
//
//        int grade;
//        int expect_grade_low;
//        int expect_grade_high;
//
//        int age;
//        int expect_age_low;
//        int expect_age_high;
//
//        int height;
//        int expect_height_low;
//        int expect_height_high;
//
//        int weight;
//        int *hobbies;
//        string MBTI;
//        string expect_MBTI;
//        string major;
//        string expect_major;
//        int appearance;
//        int expect_apperance_low;
//        int expect_apperance_high;
//
//        int significance_rate[10];
//    };
//
//    int n;
//    participant *participants;
//    vector<int> male_idx;
//    vector<int> female_idx;
//
//    void information_parsing();
//
//    //preprocess: divide the data to male and female
//    for (int i = 0;i < n;i ++){
//        participant p = participants[i];
//        if (p.gender == 0)  female_idx.push_back(i);
//        if (p.gender == 1)  male_idx.push_back(i);
//    }



