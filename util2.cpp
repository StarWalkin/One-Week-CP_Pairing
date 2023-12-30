#include "util.h"
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include "Participant.h"
#include <algorithm>
#include <random>

using namespace std;

double calculateAverage(double **attr_matrix, int rows, int cols) {
    double sum = 0.0;
    int count = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            sum += attr_matrix[i][j];
            count++;
        }
    }

    return sum / count;
}

double calculateMedian(double **attr_matrix, int rows, int cols) {
    std::vector<double> values;

    // Collect all values in the matrix into a vector
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            values.push_back(attr_matrix[i][j]);
        }
    }

}
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


int* pairing(vector<Participant> participants, vector<int> group1, vector<int> group2, double **attr_matrix, double threshold){
    vector<int> proposer;
    vector<int> receiver;

    //人数多的为proposer，竞争少数对象
    if (group1.size() >= group2.size()) {
        proposer = group1;
        receiver = group2;
    }
    else {
        proposer = group2;
        receiver = group1;
    }

    //保留原proposer副本
    vector<int> proposer_copy;
    for(int i = 0;i < proposer.size();i++){
        proposer_copy.push_back(proposer[i]);
    }


    int p_size = int(proposer.size());
    int r_size = int(receiver.size());

    //淘汰完毕多余的proposer--------------------------------------------------------
    //写出每个proposer的preference list
    vector<vector<int>> target_lists;
    for (int idx = 0; idx < p_size; idx++) {
        //attractive sorting for proposer
        vector<int> target_sort;
        for (int j = 0; j < r_size; j++) {
            target_sort.push_back(receiver[j]);
        }
        sort(target_sort.begin(), target_sort.end(), [&](int a, int b) {
            return attr_matrix[proposer[idx]][a] < attr_matrix[proposer[idx]][b];
        });
        //target_sort里面存的是从proposer视角看，吸引力从小到大排序的receiver的下标
        reverse(target_sort.begin(), target_sort.end());
        target_lists.push_back(target_sort);
    }

//    //输出target_lists
//    for(int i = 0;i < target_lists.size();i++) {
//        cout << "proposer " << proposer[i] << " : ";
//        for (int j = 0; j < target_lists[i].size(); j++) {
//            cout << target_lists[i][j] << " ";
//        }
//
//        cout << endl;
//    }

//    vector <int> latest_pointer;
//    for(int i = 0;i < proposer.size();i++){
//        latest_pointer.push_back(-1);
//    }
    int *latest_pointer = new int [p_size];
    for(int i = 0;i < p_size;i++){
        latest_pointer[i] = -1;
    }

//    int cnt = 0;

    while(1){
        //存储各个receiver收到的表白者列表
        //遍历proposer，将表白者加入receiver的表白者列表
        for(int idx=0; idx<proposer.size(); idx++){
            if (participants[proposer[idx]].paired == -1 && latest_pointer[idx] < r_size-1){
                latest_pointer[idx] = latest_pointer[idx] + 1;
                //向目前的最喜欢的人表白，并加入该人的表白者列表
                int target = target_lists[idx][latest_pointer[idx]];
                participants[target].proposers_to_select.push_back(idx);
            }
        }
        //遍历receiver，如果有多个表白者，选择最喜欢的
        for (int idx2=0;idx2<receiver.size();idx2++){
            if (participants[receiver[idx2]].paired == -1 && participants[receiver[idx2]].proposers_to_select.size() > 0 ){
                //遍历列表，选择最喜欢的
                int best = proposer[participants[receiver[idx2]].proposers_to_select[0]];
                int best_idx = 0;
                for(int i = 0;i < participants[receiver[idx2]].proposers_to_select.size();i++){
                    if(attr_matrix[receiver[idx2]][proposer[participants[receiver[idx2]].proposers_to_select[i]]] >= attr_matrix[receiver[idx2]][best]){
                        best = proposer[participants[receiver[idx2]].proposers_to_select[i]];
                        best_idx = participants[receiver[idx2]].proposers_to_select[i];
                    }
                }
                if(attr_matrix[receiver[idx2]][best] > threshold&&attr_matrix[best][receiver[idx2]]>threshold){
                    if((latest_pointer[best_idx]+1) < 0.30*r_size){
                        participants[best].nice_matching = true;
                    }
//                    将receiver和best配对
                    participants[receiver[idx2]].paired = best;
                    participants[best].paired = receiver[idx2];
                    //将receiver的表白者列表清空
                    participants[receiver[idx2]].proposers_to_select.clear();
                }
                else {
                    //将receiver的表白者列表清空
                    participants[receiver[idx2]].proposers_to_select.clear();
                }

                }


            //已被表白过：如果更喜欢，则更新配对情况
            else if(participants[receiver[idx2]].paired != -1 && participants[receiver[idx2]].proposers_to_select.size() > 0){
                //遍历列表，选择最喜欢的
                int best = proposer[participants[receiver[idx2]].proposers_to_select[0]];
                int best_idx;
                for(int i = 0;i < participants[receiver[idx2]].proposers_to_select.size();i++){
                    if(attr_matrix[receiver[idx2]][proposer[participants[receiver[idx2]].proposers_to_select[i]]] > attr_matrix[receiver[idx2]][best]){
                        best = proposer[participants[receiver[idx2]].proposers_to_select[i]];
                        best_idx = participants[receiver[idx2]].proposers_to_select[i];
                    }
                }
                //如果更喜欢，则更新配对情况
                if(attr_matrix[receiver[idx2]][best] > attr_matrix[receiver[idx2]][participants[receiver[idx2]].paired]&&attr_matrix[receiver[idx2]][best]>threshold&&attr_matrix[best][receiver[idx2]]>threshold){
                    //将原来的nice_matching清空
                    participants[participants[receiver[idx2]].paired].nice_matching = false;
                    if((latest_pointer[best_idx]+1) < 0.30*r_size){
                        participants[best].nice_matching = true;
                    }
                    //将原来的配对情况清空
                    participants[participants[receiver[idx2]].paired].paired = -1;
                    participants[receiver[idx2]].paired = -1;
                    //将receiver和best配对
                    participants[receiver[idx2]].paired = best;
                    participants[best].paired = receiver[idx2];
                    //将receiver的表白者列表清空
                    participants[receiver[idx2]].proposers_to_select.clear();
                }
                //如果不更喜欢，则不更新配对情况
                else{
                    //将receiver的表白者列表清空
                    participants[receiver[idx2]].proposers_to_select.clear();
                }
            }
        }
        //检查是否proposer都表白了
        int flag = 1;
        for(int i = 0;i < p_size;i++){
            if((latest_pointer[i] < r_size-1)&&(participants[proposer[i]].paired == -1)){
//                cout << "proposer " << proposer[i] << " has not proposed to all the receiver" << endl;
                flag = 0;
                break;
            }
        }

        int pro_single = 0;
        int rec_single = 0;
//        cout << "proposer_copy size" << proposer_copy.size() << endl;
        for(int i=0;i<p_size;i++){
            if(participants[proposer[i]].paired == -1){
                pro_single++;
            }
        }
        for(int i=0;i<r_size;i++){
            if(participants[receiver[i]].paired == -1){
                rec_single++;
            }
        }

        if(flag == 1){
            break;
        }

//        cout << "cnt: " << cnt << endl;
//        cnt++;
    }
//输出proposer和receiver的配对情况
    int pro_single = 0;
    int rec_single = 0;
    for(int i=0;i<proposer_copy.size();i++){
        if(participants[proposer_copy[i]].paired == -1){
            pro_single++;
        }
    }
    for(int i=0;i<receiver.size();i++){
        if(participants[receiver[i]].paired == -1){
            rec_single++;
        }
    }

    //计算nice_matching的数目
    int nice_matching = 0;
    for(int i = 0;i < p_size;i++){
        if(participants[proposer[i]].nice_matching == true){
            nice_matching++;
        }
    }
//    cout << "pro_single: " << pro_single << endl;
//    cout << "rec_single: " << rec_single << endl;

    int *return_value = new int [3];

    int paired_num = p_size - pro_single + r_size - rec_single;

    return_value[0] = paired_num;
    return_value[1] = nice_matching;
    return_value[2] = r_size;

//    //输出所有配对情况
//    for(int i = 0;i < p_size;i++){
//        cout << "proposer " << proposer_copy[i] << " is paired with " << participants[proposer_copy[i]].paired << endl;
//    }

    return return_value;


}
