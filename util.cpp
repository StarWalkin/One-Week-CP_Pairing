#include "util.h"
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include "Participant.h"
#include <algorithm>
#include <random>

using namespace std;



void randomSplit(const std::vector<int>& input, std::vector<int>& group1, std::vector<int>& group2) {
    // 创建一个副本，用于随机打乱
    std::vector<int> shuffled = input;
    std::random_device rd;
    std::mt19937 g(rd());

    // 随机打乱数组
    std::shuffle(shuffled.begin(), shuffled.end(), g);

    // 将打乱后的数组均分到两组
    size_t halfSize = shuffled.size() / 2;
    group1.assign(shuffled.begin(), shuffled.begin() + halfSize);
    group2.assign(shuffled.begin() + halfSize, shuffled.end());
}




void pairing(vector<Participant> participants, vector<int> group1, vector<int> group2, double **attr_matrix, int **pairing_matrix, double threshold) {
    vector<int> proposer;
    vector<int> receiver;
    vector<int> receiver_accept;

    //initialize the proposer and receiver
    //人数多的主动出击，竞争少数对象
    if (group1.size() >= group2.size()) {
        proposer = group1;
        receiver = group2;
        receiver_accept = group2;
    }
    else {
        proposer = group2;
        receiver = group1;
        receiver_accept = group1;


    }

    //initialize the receiver_accept with all -1
    for (int j = 0; j < receiver.size(); j++) {
        receiver_accept[j] = -1;
    }

    //核心算法
    //implement stable matching algorithm
    for (int idx = 0; idx < proposer.size(); idx++) {
        //attractive sorting for proposer
        vector<int> target_sort;
        for (int j = 0; j < receiver.size(); j++) {
            target_sort.push_back(receiver[j]);
        }

//        if(idx == 0){
//            cout << endl << endl << endl;
//            for(int i = 0;i < target_sort.size();i++){
//                cout << attr_matrix[idx][i] << " ";
//            }
//            cout << endl;
//        }
//        if(idx==5){
//            cout << endl << endl << endl;
//            for(int i = 0;i < target_sort.size();i++){
//                cout << target_sort[i] << " " << attr_matrix[idx][target_sort[i]] << endl;
//            }
//            cout << endl;
//        }


        sort(target_sort.begin(), target_sort.end(), [&](int a, int b) {
            return attr_matrix[proposer[idx]][a] < attr_matrix[proposer[idx]][b];
        });
        //target_sort里面存的是从proposer视角看，吸引力从小到大排序的receiver的下标
        reverse(target_sort.begin(), target_sort.end());
//        if(idx==5){
//            cout << endl << endl << endl;
//            for(int i = 0;i < target_sort.size();i++){
//                cout << target_sort[i] << " " << attr_matrix[proposer[idx]][target_sort[i]] << endl;
//            }
//            cout << endl;
//        }

        //find the first one who accept the proposer
        int first_accept = -1;
        for (int j = 0; j < target_sort.size(); j++) {
//            if (pairing_matrix[proposer[idx]][target_sort[j]] == 0 && attr_matrix[target_sort[j]][proposer[idx]]>=threshold) {
              //==-1就是这个receiver还没有接受过任何人

              if (participants[target_sort[j]].has_received==-1 && attr_matrix[target_sort[j]][proposer[idx]]>=threshold) {
                cout << "第一次接受" << endl;
                first_accept = target_sort[j];

                participants[target_sort[j]].has_received = proposer[idx];

                break;
            }

//            if(pairing_matrix[proposer[idx]][target_sort[j]] == 1 && attr_matrix[target_sort[j]][proposer[idx]]>attr_matrix[target_sort[j]][receiver_accept[j]]){
            else if(participants[target_sort[j]].has_received!=-1 && attr_matrix[target_sort[j]][proposer[idx]]>attr_matrix[target_sort[j]][participants[target_sort[j]].has_received]){
                cout << "横刀夺爱后" << endl;
                first_accept = target_sort[j];
                //pairing_matrix相应元素重置
                pairing_matrix[target_sort[j]][participants[target_sort[j]].has_received] = 0;
                pairing_matrix[participants[target_sort[j]].has_received][target_sort[j]] = 0;

                participants[target_sort[j]].has_received = proposer[idx];
                break;
            }

        }

        //print the result
        cout << "proposer: " << proposer[idx] << endl;
        cout << "receiver: " << first_accept << endl;


        //if no one accept the proposer, then the proposer will be single
        if (first_accept == -1) {
            cout << "no one accept the proposer" << endl;
            continue;
        }
        //if someone accept the proposer, then the proposer will be paired with the first one who accept him
        else {
//            receiver_accept[first_accept] = idx;
//            cout << "enter" << endl;

            pairing_matrix[proposer[idx]][first_accept] = 1;
            pairing_matrix[first_accept][proposer[idx]] = 1;
            //if the first one who accept the proposer is not the most attractive one, then the most attractive one will be single
//            if (target_sort[0] != first_accept) {
//                receiver_accept[target_sort[0]] = -1;
//            }
            //if the first one who accept the proposer is the most attractive one, then the second most attractive one will be single
//            else {
//                receiver_accept[target_sort[1]] = -1;
//            }

        }


//        cout << "receiver_accept: ";
//            for (int j = 0; j < 100; j++) {
//                cout << pairing_matrix[idx][j] << " ";
//            }
        cout << endl;

    }

//    print the result
//    cout << "pairing_matrix: " << endl;
//    for (int i = 0; i < 400; i++) {
//        cout << i << ": ";
//        for (int j = 0; j < 400; j++) {
//            cout << pairing_matrix[i][j] << " ";
//        }
//        cout << endl;
//    }
    cout << "--------------------------------------------";
    //找到没对象的proposer并输出序号和总数
    int single_count = 0;
    cout << "single proposer: ";
    for (int i = 0; i < proposer.size(); i++) {
        int flag = 0;
        for (int j = 0; j < receiver.size(); j++) {
            if (pairing_matrix[proposer[i]][receiver[j]] == 1) {
                flag = 1;
                break;
            }
        }
        if (flag == 0) {
            cout << proposer[i] << " ";
            single_count++;
        }
    }
    cout << endl;
    cout << "single proposer count: " << single_count << endl;

    //找到没对象的receiver并输出序号和总数
    int single_count2 = 0;
    cout << "single receiver: ";
    for (int i = 0; i < receiver.size(); i++) {
        int flag = 0;
        for (int j = 0; j < proposer.size(); j++) {
            if (pairing_matrix[receiver[i]][proposer[j]] == 1) {
                flag = 1;
                break;
            }
        }
        if (flag == 0) {
            cout << receiver[i] << " ";
            single_count2++;
        }
    }
//    cout << single_count2;
    cout << endl;
    cout << "single receiver count: " << single_count2 << endl;

    //找到所有配对的proposer和receiver并输出
    cout << "pairing result: " << endl;
    for (int i = 0; i < proposer.size(); i++) {
        for (int j = 0; j < receiver.size(); j++) {
            if (pairing_matrix[proposer[i]][receiver[j]] == 1) {
                cout << proposer[i] << " " << receiver[j] << endl;
            }
        }
    }

}//
// Created by Yuan on 2023/12/28.
//
