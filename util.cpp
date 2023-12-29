#include "util.h"
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include "Participant.h"
#include <algorithm>
#include <random>

using namespace std;



void randomSplit(std::vector<int>& input, std::vector<int>& group1, std::vector<int>& group2) {
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
    //sort the group1 and group2
    sort(group1.begin(), group1.end());
    sort(group2.begin(), group2.end());
}

void swapRandomElements(std::vector<int>& array1, std::vector<int>& array2) {
    // 使用随机设备和 Mersenne Twister 引擎生成随机索引
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist1(0, array1.size() - 1);
    std::uniform_int_distribution<> dist2(0, array2.size() - 1);

    // 从两个数组中随机选择索引
    int index1 = dist1(gen);
    int index2 = dist2(gen);

    // 交换选定的元素
    std::swap(array1[index1], array2[index2]);
}


void cross(vector<int> &boy_homo1, vector<int> &boy_homo2, vector<int> &girl_homo1, vector<int> &girl_homo2){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 2);
    int operation = dist(gen);
    if(operation == 0){
        swapRandomElements(boy_homo1,boy_homo2);
    }
    if(operation == 1){
        swapRandomElements(girl_homo1,girl_homo2);
    }
    if(operation == 2){
        swapRandomElements(boy_homo1,boy_homo2);
        swapRandomElements(girl_homo1,girl_homo2);
    }

}


int* pairing(vector<Participant> participants, vector<int> group1, vector<int> group2, double **attr_matrix, int **pairing_matrix, double threshold) {
    vector<int> proposer;
    vector<int> receiver;
    vector<int> receiver_accept;

    //pairing_matrix初始化 ，还要考虑转置我草


    //initialize the proposer and receiver
    //人数多的主动出击，竞争少数对象
    if (group1.size() <= group2.size()) {
        proposer = group1;
        receiver = group2;
        receiver_accept = group2;
    }
    else {
        proposer = group2;
        receiver = group1;
        receiver_accept = group1;

    }

    for(int i1 = 0;i1 < proposer.size();i1++){
        for(int i2 = 0;i2 < receiver.size();i2++){
            pairing_matrix[proposer[i1]][receiver[i2]] = 0;
            pairing_matrix[receiver[i2]][proposer[i1]] = 0;
        }
    }

    //initialize the receiver_accept with all -1
    for (int j = 0; j < receiver.size(); j++) {
        receiver_accept[j] = -1;
    }


    //GS algorithm
    //initialize the target_lists:存的是每个proposer的吸引度降序排列的receiver的下标
    vector<vector<int>> target_lists;
    for (int idx = 0; idx < proposer.size(); idx++) {
        //attractive sorting for proposer
        vector<int> target_sort;
        for (int j = 0; j < receiver.size(); j++) {
            target_sort.push_back(receiver[j]);
        }
        sort(target_sort.begin(), target_sort.end(), [&](int a, int b) {
            return attr_matrix[proposer[idx]][a] < attr_matrix[proposer[idx]][b];
        });
        //target_sort里面存的是从proposer视角看，吸引力从小到大排序的receiver的下标
        reverse(target_sort.begin(), target_sort.end());
        target_lists.push_back(target_sort);
    }

//    //output the target_lists
//    cout << "----------------------target list---------------------------";
//    for(int i = 0;i < target_lists.size();i++) {
//        cout << "proposer: " << proposer[i] << endl;
//        for (int j = 0; j < target_lists[i].size(); j++) {
//            cout << target_lists[i][j] << " ";
//        }
//    }
//        cout << "----------------------target list end---------------------------";

//    //implement GS algorithm
//    vector<int> curr_best;
//    //initialize curr_best
//    for (int i = 0; i < proposer.size(); i++) {
//        curr_best.push_back(0);
//    }
//
//    for (int j = 0; j < receiver.size();j ++) {
//        for (int idx = 0; idx < proposer.size(); idx++) {
//            if (participants[proposer[idx]].has_been_received) {
//                continue;
//            }
//            //每个proposer向自己list上的第j个目标发出propose
//            int target = target_lists[idx][curr_best[idx]];
//            //如果这个目标还没有接受过任何人，那么就接受这个proposer
//            if (participants[target].has_received == -1 && attr_matrix[target][proposer[idx]] >= threshold) {
////                pairing_matrix[proposer[j]][target] = 1;
////                pairing_matrix[target][proposer[j]] = 1;
//                participants[target].has_received = proposer[idx];
//                //judge if is nice matching
//                if (j <= 0.30 * receiver.size()) {
//                    participants[proposer[idx]].nice_matching = true;
//                }
//                participants[proposer[idx]].has_been_received = true;
//
//                curr_best[idx] ++;
//
//                //pairing_matrix
//                pairing_matrix[proposer[idx]][target] = 1;
//                pairing_matrix[target][proposer[idx]] = 1;
//                break;
//            }
////如果这个目标接受过别人，那么就比较一下这个proposer和别人的吸引力，如果这个proposer的吸引力更大，那么就接受这个proposer
//            else if (participants[target].has_received != -1 &&
//                     attr_matrix[target][proposer[idx]] > attr_matrix[target][participants[target].has_received]) {
////                pairing_matrix[proposer[j]][target] = 1;
////                pairing_matrix[target][proposer[j]] = 1;
//                participants[target].has_received = proposer[idx];
//                participants[proposer[idx]].has_been_received = true;
//                participants[participants[target].has_received].has_been_received = false;
//                //pairing matrix相应元素重置
//                pairing_matrix[target][participants[target].has_received] = 0;
//                pairing_matrix[participants[target].has_received][target] = 0;
//                //nice_matching重置
//                participants[participants[target].has_received].nice_matching = false;
//                //judge if is nice matching
//                if (j <= 0.30 * receiver.size()) {
//                    participants[proposer[idx]].nice_matching = true;
//                }
//
//                //pairing_matrix
//                pairing_matrix[proposer[idx]][target] = 1;
//                pairing_matrix[target][proposer[idx]] = 1;
//                break;
//            }
//
//        }
//    }





    //核心算法
    //implement stable matching algorithm
    //max_times是最多循环次数，防止死循环,即每个proposer最多向每个receiver发出一次propose
    vector<int> latest_propose;
    for(int i = 0;i < proposer.size();i++){
        latest_propose.push_back(-1);
    }
    int max_times = proposer.size()*receiver.size();
    for(int time=0;time < max_times;time++){
        //找到第一个没对象的proposer
        int idx;
//        cout << (participants[proposer[0]].has_been_received==false) << endl;
//        cout << latest_propose[0] << endl;
//        cout << receiver.size() << endl;
//        cout << (latest_propose[0] < int(receiver.size())-1) << endl;
        for(idx = 0;idx < proposer.size();idx++){
            if(participants[proposer[idx]].has_been_received==false && latest_propose[idx] < int(receiver.size()-1)){
                cout << "break here" << endl;
                break;
            }
        }
        cout << "idx: " << idx << endl;
        if(idx == proposer.size()){
            cout << "no one need to propose" << endl;
            break;
        }

        //向latest_propose+1的receiver发出propose
        latest_propose[idx]++;
        int target = target_lists[idx][latest_propose[idx]];
        cout << "target: " << target << endl;
        //如果这个目标还没有接受过任何人，那么就接受这个proposer
        if (participants[target].has_received == -1 && attr_matrix[target][proposer[idx]] >= threshold) {
            participants[target].has_received = proposer[idx];
            //judge if is nice matching
            if (latest_propose[idx] <= 0.30 * receiver.size()) {
                participants[proposer[idx]].nice_matching = true;
            }
            participants[proposer[idx]].has_been_received = true;

            //pairing_matrix
            pairing_matrix[proposer[idx]][target] = 1;
            pairing_matrix[target][proposer[idx]] = 1;
            continue;
        }
//如果这个目标接受过别人，那么就比较一下这个proposer和别人的吸引力，如果这个proposer的吸引力更大，那么就接受这个proposer
        else if (participants[target].has_received != -1 &&
                 attr_matrix[target][proposer[idx]] > attr_matrix[target][participants[target].has_received]) {
            participants[target].has_received = proposer[idx];
            participants[proposer[idx]].has_been_received = true;
            participants[participants[target].has_received].has_been_received = false;
            //pairing matrix相应元素重置
            pairing_matrix[target][participants[target].has_received] = 0;
            pairing_matrix[participants[target].has_received][target] = 0;
            //nice_matching重置
            participants[participants[target].has_received].nice_matching = false;
            //judge if is nice matching
            if (latest_propose[idx] <= 0.30 * receiver.size()) {
                participants[proposer[idx]].nice_matching = true;
            }

            //pairing_matrix
            pairing_matrix[proposer[idx]][target] = 1;
            pairing_matrix[target][proposer[idx]] = 1;
            continue;
        }

    }
//    for (int idx = 0; idx < proposer.size(); idx++) {
//        if(participants[proposer[idx]].has_received!=-1){
//            continue;
//        }
//
//        //find the first one who accept the proposer
//        int first_accept = -1;
//        for (int j = 0; j < receiver.size(); j++) {
////            if (pairing_matrix[proposer[idx]][target_sort[j]] == 0 && attr_matrix[target_sort[j]][proposer[idx]]>=threshold) {
//              //==-1就是这个receiver还没有接受过任何人
//
//              if (participants[target_lists[idx][j]].has_received==-1 && attr_matrix[target_lists[idx][j]][proposer[idx]]>=threshold) {
////                cout << "第一次接受" << endl;
//                first_accept = target_lists[idx][j];
//
//                participants[target_lists[idx][j]].has_received = proposer[idx];
//
//                //judge if is nice matching
//                if(j <= 0.30*receiver.size()){
//                    participants[proposer[idx]].nice_matching = true;
//                }
//
//
//                break;
//            }
//
////            if(pairing_matrix[proposer[idx]][target_sort[j]] == 1 && attr_matrix[target_sort[j]][proposer[idx]]>attr_matrix[target_sort[j]][receiver_accept[j]]){
//            else if(participants[target_lists[idx][j]].has_received!=-1 && attr_matrix[target_lists[idx][j]][proposer[idx]]>attr_matrix[target_lists[idx][j]][participants[target_lists[idx][j]].has_received]){
////                cout << "横刀夺爱后" << endl;
//                first_accept = target_lists[idx][j];
//                //pairing_matrix相应元素重置
//                pairing_matrix[target_sort[j]][participants[target_sort[j]].has_received] = 0;
//                pairing_matrix[participants[target_sort[j]].has_received][target_sort[j]] = 0;
//
//                participants[target_sort[j]].has_received = proposer[idx];
//
//                //nice_matching重置
//                participants[participants[target_sort[j]].has_received].nice_matching = false;
//
//
//                //judge if is nice matching
//                if(j <= 0.30*target_sort.size()){
//                    participants[proposer[idx]].nice_matching = true;
//                }
//                break;
//            }
//
//        }
//
////        //print the result
////        cout << "proposer: " << proposer[idx] << endl;
////        cout << "receiver: " << first_accept << endl;
//
//
//        //if no one accept the proposer, then the proposer will be single
//        if (first_accept == -1) {
//            cout << "no one accept the proposer" << endl;
//            continue;
//        }
//        //if someone accept the proposer, then the proposer will be paired with the first one who accept him
//        else {
////            receiver_accept[first_accept] = idx;
////            cout << "enter" << endl;
//
//            pairing_matrix[proposer[idx]][first_accept] = 1;
//            pairing_matrix[first_accept][proposer[idx]] = 1;
//            //if the first one who accept the proposer is not the most attractive one, then the most attractive one will be single
////            if (target_sort[0] != first_accept) {
////                receiver_accept[target_sort[0]] = -1;
////            }
//            //if the first one who accept the proposer is the most attractive one, then the second most attractive one will be single
////            else {
////                receiver_accept[target_sort[1]] = -1;
////            }
//
//        }
//
//
////        cout << "receiver_accept: ";
////            for (int j = 0; j < 100; j++) {
////                cout << pairing_matrix[idx][j] << " ";
////            }
////        cout << endl;
//
//    }

    //count the nice matching
    int nice_matching_count = 0;
    for(int i = 0;i < proposer.size();i++){
        if(participants[proposer[i]].nice_matching){
            nice_matching_count++;
        }
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
    cout << "--------------------------------------------" << endl;
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

//    //找到所有配对的proposer和receiver并输出
//    cout << "pairing result: " << endl;
//    for (int i = 0; i < proposer.size(); i++) {
//        for (int j = 0; j < receiver.size(); j++) {
//            if (pairing_matrix[proposer[i]][receiver[j]] == 1) {
//                cout << proposer[i] << " " << receiver[j] << endl;
//            }
//        }
//    }

//    return nice_matching_count;
    int *return_value = new int [3];
    //第一个：所有参与者中匹配成功的人数
    return_value[0] = proposer.size() + receiver.size() - single_count - single_count2;
    cout << "return_value[0]: " << return_value[0] << endl;
    //nice matching的人数
    return_value[1] = nice_matching_count;
    //proposer总人数
    return_value[2] = proposer.size();

//    cout << "-----------------" << endl << return_value[0] << endl << "-----------------" << endl;

    return return_value;




}//
// Created by Yuan on 2023/12/28.
//
