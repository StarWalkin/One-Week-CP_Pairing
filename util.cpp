//#include "util.h"
//#include <iostream>
//#include <string>
//#include <cstring>
//#include <vector>
//#include "Participant.h"
//#include <algorithm>
//#include <random>
//
//using namespace std;
//
//
//
//void randomSplit(std::vector<int>& input, std::vector<int>& group1, std::vector<int>& group2) {
//    // 创建一个副本，用于随机打乱
//    std::vector<int> shuffled = input;
//    std::random_device rd;
//    std::mt19937 g(rd());
//
//    // 随机打乱数组
//    std::shuffle(shuffled.begin(), shuffled.end(), g);
//
//    // 将打乱后的数组均分到两组
//    size_t halfSize = shuffled.size() / 2;
//    group1.assign(shuffled.begin(), shuffled.begin() + halfSize);
//    group2.assign(shuffled.begin() + halfSize, shuffled.end());
//    //sort the group1 and group2
//    sort(group1.begin(), group1.end());
//    sort(group2.begin(), group2.end());
//}
//
//void swapRandomElements(std::vector<int>& array1, std::vector<int>& array2) {
//    // 使用随机设备和 Mersenne Twister 引擎生成随机索引
//    std::random_device rd;
//    std::mt19937 gen(rd());
//    std::uniform_int_distribution<> dist1(0, array1.size() - 1);
//    std::uniform_int_distribution<> dist2(0, array2.size() - 1);
//
//    // 从两个数组中随机选择索引
//    int index1 = dist1(gen);
//    int index2 = dist2(gen);
//
//    // 交换选定的元素
//    std::swap(array1[index1], array2[index2]);
//}
//
//
//void cross(vector<int> &boy_homo1, vector<int> &boy_homo2, vector<int> &girl_homo1, vector<int> &girl_homo2){
//    std::random_device rd;
//    std::mt19937 gen(rd());
//    std::uniform_int_distribution<> dist(0, 2);
//    int operation = dist(gen);
//    if(operation == 0){
//        swapRandomElements(boy_homo1,boy_homo2);
//    }
//    if(operation == 1){
//        swapRandomElements(girl_homo1,girl_homo2);
//    }
//    if(operation == 2){
//        swapRandomElements(boy_homo1,boy_homo2);
//        swapRandomElements(girl_homo1,girl_homo2);
//    }
//
//}
//
//
////int* pairing(vector<Participant> participants, vector<int> group1, vector<int> group2, double **attr_matrix, int **pairing_matrix, double threshold) {
////    vector<int> proposer;
////    vector<int> receiver;
////    vector<int> receiver_accept;
////
////    //pairing_matrix初始化 ，还要考虑转置我草
////
////
////    //initialize the proposer and receiver
////    //人数多的主动出击，竞争少数对象
////    if (group1.size() >= group2.size()) {
////        proposer = group1;
////        receiver = group2;
////        receiver_accept = group2;
////    }
////    else {
////        proposer = group2;
////        receiver = group1;
////        receiver_accept = group1;
////
////    }
////
////    for(int i1 = 0;i1 < proposer.size();i1++){
////        for(int i2 = 0;i2 < receiver.size();i2++){
////            pairing_matrix[proposer[i1]][receiver[i2]] = 0;
////            pairing_matrix[receiver[i2]][proposer[i1]] = 0;
////        }
////    }
////
////    //initialize the receiver_accept with all -1
////    for (int j = 0; j < receiver.size(); j++) {
////        receiver_accept[j] = -1;
////    }
////
////
////    //GS algorithm
////    //initialize the target_lists:存的是每个proposer的吸引度降序排列的receiver的下标
////    vector<vector<int>> target_lists;
////    for (int idx = 0; idx < proposer.size(); idx++) {
////        //attractive sorting for proposer
////        vector<int> target_sort;
////        for (int j = 0; j < receiver.size(); j++) {
////            target_sort.push_back(receiver[j]);
////        }
////        sort(target_sort.begin(), target_sort.end(), [&](int a, int b) {
////            return attr_matrix[proposer[idx]][a] < attr_matrix[proposer[idx]][b];
////        });
////        //target_sort里面存的是从proposer视角看，吸引力从小到大排序的receiver的下标
////        reverse(target_sort.begin(), target_sort.end());
////        target_lists.push_back(target_sort);
////        //输出一部分数据check一下有没有正确地排好序
////
////       //输出target_lists的形状
//////         cout << "target_lists.size(): " << target_lists.size() << endl;
//////            cout << "target_lists[0].size(): " << target_lists[0].size() << endl;
////
////
////
////    }
////
//////    cout << "idx=108" << endl;
//////    for(int i = 0;i < 100;i++){
//////        cout << "排名第" << i << "的吸引度" <<  attr_matrix[proposer[108]][target_lists[108][i]] << endl;
//////    }
////
////    //排序没问题的
////    //核心算法
////    //implement stable matching algorithm
////    //max_times是最多循环次数，防止死循环,即每个proposer最多向每个receiver发出一次propose
////    vector<int> latest_propose;
////    for(int i = 0;i < proposer.size();i++){
////        latest_propose.push_back(-1);
////    }
////    int max_times = proposer.size()*receiver.size();
////    for(int time=0;time < 10*max_times;time++){
////        //找到第一个没对象的proposer
////        int idx;
//////        cout << (participants[proposer[0]].has_been_received==false) << endl;
//////        cout << latest_propose[0] << endl;
//////        cout << receiver.size() << endl;
//////        cout << (latest_propose[0] < int(receiver.size())-1) << endl;
////        for(idx = 0;idx < proposer.size();idx++){
////            if(participants[proposer[idx]].has_been_received==false && latest_propose[idx] < int(receiver.size()-1)){
//////                cout << "break here" << endl;
////                break;
////            }
////        }
//////        cout << "idx: " << idx << endl;
////        if(idx == proposer.size()){
//////            cout << "no one need to propose" << endl;
////            break;
////        }
////
////        //向latest_propose+1的receiver发出propose
////        latest_propose[idx]++;
////
////        int target = target_lists[idx][latest_propose[idx]];
//////        cout << "target: " << target << endl;
////        //如果这个目标还没有接受过任何人，那么就接受这个proposer
////        if (participants[target].has_received == -1 && attr_matrix[target][proposer[idx]] >= threshold && attr_matrix[proposer[idx]][target] >= threshold) {
////            participants[target].has_received = proposer[idx];
////            participants[proposer[idx]].has_been_received = true;
////            //judge if is nice matching
////            if (1.00*latest_propose[idx] <= 0.30 * receiver.size()) {
//////                cout << "nice matching" << endl;
//////                cout << latest_propose[idx] << endl;
//////                cout << receiver.size() << endl;
////                participants[proposer[idx]].nice_matching = true;
////            }
////
////
//////           cout << "idx" << idx << "成功匹配" << proposer[idx] << endl;
//////            cout << "这一次对象的排名：" << latest_propose[idx] << "序号：" << target << endl;
//////            //check一下吸引度
//////            cout << "与阈值比较的吸引度：" << attr_matrix[target][proposer[idx]] << endl;
//////            cout << "吸引度：" << attr_matrix[proposer[idx]][target] << endl;
//////            cout << "排名第一的吸引度" <<  attr_matrix[proposer[idx]][target_lists[idx][0]] << endl;
////////
//////            //当前对应的吸引度排名前一百列一下
//////            for(int i = 0;i < 100;i++){
//////                cout << "排名第" << i << "的吸引度" <<  attr_matrix[proposer[idx]][target_lists[idx][i]] << endl;
//////            }
//////            cout << "idx=108" << endl;
//////            for(int i = 0;i < 100;i++){
//////                cout << "排名第" << i << "的吸引度" <<  attr_matrix[proposer[108]][target_lists[108][i]] << endl;
//////            }
////
////            if(participants[proposer[idx]].has_been_received == false){
////                cout << "error" << endl;
////            }
////
////            //pairing_matrix
////            pairing_matrix[proposer[idx]][target] = 1;
////            pairing_matrix[target][proposer[idx]] = 1;
////            continue;
////        }
//////如果这个目标接受过别人，那么就比较一下这个proposer和别人的吸引力，如果这个proposer的吸引力更大，那么就接受这个proposer
////        else if (participants[target].has_received != -1 &&
////                 attr_matrix[target][proposer[idx]] > attr_matrix[target][participants[target].has_received] && attr_matrix[target][proposer[idx]] >= threshold && attr_matrix[proposer[idx]][target] >= threshold) {
////            participants[participants[target].has_received].nice_matching = false;
////            participants[participants[target].has_received].has_been_received = false;
////            //pairing matrix相应元素重置
////            pairing_matrix[target][participants[target].has_received] = 0;
////            pairing_matrix[participants[target].has_received][target] = 0;
////
////            participants[target].has_received = proposer[idx];
//////            cout << "idx" << idx << "成功匹配"  << proposer[idx] << endl;
//////            cout << "idx的状态：" << proposer[idx] << "  " <<participants[proposer[idx]].has_been_received << endl;
//////            cout << "这一次对象的排名：" << latest_propose[idx] << "序号：" << target << endl;
//////            participants[proposer[idx]].has_been_received = true;
//////            cout << "设置后，idx的状态：" << proposer[idx] << "  " << participants[proposer[idx]].has_been_received << endl;
////
////
////            //nice_matching重置
//////            participants[participants[target].has_received].nice_matching = false;
////            //judge if is nice matching
////            if (latest_propose[idx] <= 0.30 * receiver.size()) {
////                participants[proposer[idx]].nice_matching = true;
//////                cout << "nice matching" << endl;
//////                cout << latest_propose[idx] << endl;
//////                cout << receiver.size() << endl;
////            }
////
////            participants[proposer[idx]].has_been_received = true;
////
////            if(participants[proposer[idx]].has_been_received == false){
////                cout << "error" << endl;
////            }
////            //pairing_matrix
////            pairing_matrix[proposer[idx]][target] = 1;
////            pairing_matrix[target][proposer[idx]] = 1;
//////            cout << "开始下一轮循环前，idx的状态：" << proposer[idx] << "  " << participants[proposer[idx]].has_been_received << endl;
////            continue;
////        }
//////
////
////
////    }
////
////
////    //count the nice matching
////    int nice_matching_count = 0;
////    for(int i = 0;i < proposer.size();i++){
////        if(participants[proposer[i]].nice_matching){
////            nice_matching_count++;
////        }
////    }
////
////
////    cout << "--------------------------------------------" << endl;
////    //找到没对象的proposer并输出序号和总数
////    int single_count = 0;
////    cout << "single proposer: ";
////    for (int i = 0; i < proposer.size(); i++) {
////        int flag = 0;
////        for (int j = 0; j < receiver.size(); j++) {
////            if (pairing_matrix[proposer[i]][receiver[j]] == 1) {
////                flag = 1;
////                break;
////            }
////        }
////        if (flag == 0) {
////            cout << proposer[i] << " ";
////            single_count++;
////        }
////    }
////    cout << endl;
////    cout << "single proposer count: " << single_count << endl;
////
////    //找到没对象的receiver并输出序号和总数
////    int single_count2 = 0;
////    cout << "single receiver: ";
////    for (int i = 0; i < receiver.size(); i++) {
////        int flag = 0;
////        for (int j = 0; j < proposer.size(); j++) {
////            if (pairing_matrix[receiver[i]][proposer[j]] == 1) {
////                flag = 1;
////                break;
////            }
////        }
////        if (flag == 0) {
////            cout << receiver[i] << " ";
////            single_count2++;
////        }
////    }
//////    cout << single_count2;
////    cout << endl;
////    cout << "single receiver count: " << single_count2 << endl;
////
//////    //找到所有配对的proposer和receiver并输出
//////    cout << "pairing result: " << endl;
//////    for (int i = 0; i < proposer.size(); i++) {
//////        for (int j = 0; j < receiver.size(); j++) {
//////            if (pairing_matrix[proposer[i]][receiver[j]] == 1) {
//////                cout << proposer[i] << " " << receiver[j] << endl;
//////            }
//////        }
//////    }
////
//////    return nice_matching_count;
////    int *return_value = new int [3];
////    //第一个：所有参与者中匹配成功的人数
////    return_value[0] = proposer.size() + receiver.size() - single_count - single_count2;
////    cout << "return_value[0]: " << return_value[0] << endl;
////    if(return_value[0]%2 == 1){
////        //打印出匹配情况 检测异常
////        cout << "pairing result: " << endl;
////        for (int i = 0; i < proposer.size(); i++) {
////            for (int j = 0; j < receiver.size(); j++) {
////                if (pairing_matrix[proposer[i]][receiver[j]] == 1) {
////                    cout << proposer[i] << " " << receiver[j] << endl;
////                }
////            }
////        }
////        //输出proposer和receiver
////        cout << "proposer: ";
////        for (int i = 0; i < proposer.size(); i++) {
////            cout << proposer[i] << " ";
////        }
////        cout << endl;
////        cout << "receiver: ";
////        for (int i = 0; i < receiver.size(); i++) {
////            cout << receiver[i] << " ";
////        }
////        cout << endl;
////    }
////    cout << "pairing result: " << endl;
////    for (int i = 0; i < proposer.size(); i++) {
////        for (int j = 0; j < receiver.size(); j++) {
////            if (pairing_matrix[proposer[i]][receiver[j]] == 1) {
////                cout << proposer[i] << " " << receiver[j] << endl;
////            }
////        }
////    }
////    //输出proposer和receiver
////    cout << "proposer: ";
////    for (int i = 0; i < proposer.size(); i++) {
////        cout << proposer[i] << " ";
////    }
////    cout << endl;
////    cout << "receiver: ";
////    for (int i = 0; i < receiver.size(); i++) {
////        cout << receiver[i] << " ";
////    }
////    cout << endl;
////    //nice matching的人数
////    return_value[1] = nice_matching_count;
////    //proposer总人数
////    return_value[2] = proposer.size();
////    cout << "nice_matching_count: " << nice_matching_count << endl;
////    cout << "proposer.size(): " << proposer.size() << endl;
////
//////    cout << "-----------------" << endl << return_value[0] << endl << "-----------------" << endl;
////
////    return return_value;
////
////
////
////
////}//
//// Created by Yuan on 2023/12/28.
////
//
//
//
//
//
//
//int* pairing(vector<Participant> participants, vector<int> group1, vector<int> group2, double **attr_matrix, int **pairing_matrix, double threshold) {
//    vector<int> proposer;
//    vector<int> receiver;
//    vector<int> receiver_accept;
//
//    //pairing_matrix初始化 ，还要考虑转置我草
//
//
//    //initialize the proposer and receiver
//    //人数多的主动出击，竞争少数对象
//    if (group1.size() >= group2.size()) {
//        proposer = group1;
//        receiver = group2;
//        receiver_accept = group2;
//    }
//    else {
//        proposer = group2;
//        receiver = group1;
//        receiver_accept = group1;
//
//    }
//
//    //求出每个proposer对于receiver的吸引力的中位数
//    vector<double> median_attr;
//    for(int i = 0;i < proposer.size();i++){
//        vector<double> attr;
//        for(int j = 0;j < receiver.size();j++){
//            attr.push_back(attr_matrix[receiver[j]][proposer[i]]);
//        }
//        sort(attr.begin(),attr.end());
//        median_attr.push_back(attr[int(receiver.size()/2)]);
//    }
//
//    //将proposer以median_attr从大到小排序
//    vector<int> proposer_new;
//    for(int i = 0;i < proposer.size();i++){
//        proposer_new.push_back(proposer[i]);
//    }
//    sort(proposer_new.begin(),proposer_new.end(),[&](int a,int b){
//        return median_attr[a] > median_attr[b];
//    });
//    //取前receiver.size()个proposer
//    proposer_new.erase(proposer_new.begin()+receiver.size(),proposer_new.end());
//
//
//    proposer = proposer_new;
//
//    cout << "proposer.size(): " << proposer.size() << endl;
//    cout << "receiver.size(): " << receiver.size() << endl;
//
//    //GS algorithm
//    //initialize the target_lists:存的是每个proposer的吸引度降序排列的receiver的下标
//    vector<vector<int>> target_lists;
//    for (int idx = 0; idx < proposer.size(); idx++) {
//        //attractive sorting for proposer
//        vector<int> target_sort;
//        for (int j = 0; j < receiver.size(); j++) {
//            target_sort.push_back(receiver[j]);
//        }
//        sort(target_sort.begin(), target_sort.end(), [&](int a, int b) {
//            return attr_matrix[proposer[idx]][a] < attr_matrix[proposer[idx]][b];
//        });
//        //target_sort里面存的是从proposer视角看，吸引力从小到大排序的receiver的下标
//        reverse(target_sort.begin(), target_sort.end());
//        target_lists.push_back(target_sort);
//        //输出一部分数据check一下有没有正确地排好序
//    }
//
//    //排序没问题的
//    //核心算法
//    //implement stable matching algorithm
//    vector<int> latest_propose;
//    for(int i = 0;i < proposer.size();i++){
//        latest_propose.push_back(-1);
//    }
//    //判断proposer是否表白完
//    int latest_sum_check = 0;
//    //判断receiver是否接受完
//    int receiver_accept_sum_check = 0;
//    //GS算法
//    while (1) {
//        //所有没有对象的proposer都向自己的最喜欢的receiver发出propose
//        for (int i = 0; i < proposer.size(); i++) {
//            if (participants[proposer[i]].has_been_received == false) {
//                latest_propose[i]++;
//                int target = target_lists[i][latest_propose[i]];
//                //如果这个目标还没有接受过任何人，那么就接受这个proposer
//                if (participants[target].has_received == -1 && attr_matrix[target][proposer[i]] >= threshold &&
//                    attr_matrix[proposer[i]][target] >= threshold) {
//                    participants[target].has_received = proposer[i];
//                    participants[proposer[i]].has_been_received = true;
//                    //judge if is nice matching
//                    if (1.00 * latest_propose[i] <= 0.30 * receiver.size()) {
//                        participants[proposer[i]].nice_matching = true;
//                    }
//                    //pairing_matrix
//                    pairing_matrix[proposer[i]][target] = 1;
//                    pairing_matrix[target][proposer[i]] = 1;
//                    continue;
//                }
//                    //如果这个目标接受过别人，那么就比较一下这个proposer和别人的吸引力，如果这个proposer的吸引力更大，那么就接受这个proposer
//                else if (participants[target].has_received != -1 &&
//                         attr_matrix[target][proposer[i]] > attr_matrix[target][participants[target].has_received] &&
//                         attr_matrix[target][proposer[i]] >= threshold &&
//                         attr_matrix[proposer[i]][target] >= threshold) {
//                    participants[participants[target].has_received].nice_matching = false;
//                    participants[participants[target].has_received].has_been_received = false;
//                    //pairing matrix相应元素重置
//                    pairing_matrix[target][participants[target].has_received] = 0;
//                    pairing_matrix[participants[target].has_received][target] = 0;
//
//                    participants[target].has_received = proposer[i];
//                    //nice_matching重置
//                    if (latest_propose[i] <= 0.30 * receiver.size()) {
//                        participants[proposer[i]].nice_matching = true;
//                    }
//                    participants[proposer[i]].has_been_received = true;
//                    //pairing_matrix
//                    pairing_matrix[proposer[i]][target] = 1;
//                    pairing_matrix[target][proposer[i]] = 1;
//                    continue;
//                }
//
//                else{
//                    //打印相关信息来了解不能配对原因
//                   cout << "proposer: " << proposer[i] << endl;
//                    cout << "target: " << target << endl;
//                    cout << "attr_matrix[target][proposer[i]]: " << attr_matrix[target][proposer[i]] << endl;
//                    cout << "attr_matrix[proposer[i]][target]: " << attr_matrix[proposer[i]][target] << endl;
//                    cout << "participants[proposer[i]].has_been_received: " << participants[proposer[i]].has_been_received << endl;
//                    cout << "participants[target].has_received: " << participants[target].has_received << endl;
//                    cout << "attr_matrix[target][participants[target].has_received]: " << attr_matrix[target][participants[target].has_received] << endl;
//
//
//                }
//
//            }
//
//
//        }
//        //判断proposer是否表白完
//        int latest_sum = 0;
//        for(int i = 0;i < proposer.size();i++){
//            latest_sum += latest_propose[i];
//        }
//        if(latest_sum == latest_sum_check){
//            break;
//        }
//        else{
//            latest_sum_check = latest_sum;
//        }
//        //判断receiver是否接受完
//        int receiver_accept_sum = 0;
//        for(int i = 0;i < receiver.size();i++){
//            if(participants[receiver[i]].has_received != -1){
//                receiver_accept_sum++;
//            }
//        }
//        if(receiver_accept_sum == receiver_accept_sum_check){
//            break;
//        }
//        else{
//            receiver_accept_sum_check = receiver_accept_sum;
//        }
//
//    }
//
//
//
//
//
//
//
//    //count the nice matching
//    int nice_matching_count = 0;
//    for(int i = 0;i < proposer.size();i++){
//        if(participants[proposer[i]].nice_matching){
//            nice_matching_count++;
//        }
//    }
//
//
//    cout << "--------------------------------------------" << endl;
//    //找到没对象的proposer并输出序号和总数
//    int single_count = 0;
//    cout << "single proposer: ";
//    for (int i = 0; i < proposer.size(); i++) {
//        int flag = 0;
//        for (int j = 0; j < receiver.size(); j++) {
//            if (pairing_matrix[proposer[i]][receiver[j]] == 1) {
//                flag = 1;
//                break;
//            }
//        }
//        if (flag == 0) {
//            cout << proposer[i] << " ";
//            single_count++;
//        }
//    }
//    cout << endl;
//    cout << "single proposer count: " << single_count << endl;
//
//    //找到没对象的receiver并输出序号和总数
//    int single_count2 = 0;
//    cout << "single receiver: ";
//    for (int i = 0; i < receiver.size(); i++) {
//        int flag = 0;
//        for (int j = 0; j < proposer.size(); j++) {
//            if (pairing_matrix[receiver[i]][proposer[j]] == 1) {
//                flag = 1;
//                break;
//            }
//        }
//        if (flag == 0) {
//            cout << receiver[i] << " ";
//            single_count2++;
//        }
//    }
////    cout << single_count2;
//    cout << endl;
//    cout << "single receiver count: " << single_count2 << endl;
//
////    //找到所有配对的proposer和receiver并输出
////    cout << "pairing result: " << endl;
////    for (int i = 0; i < proposer.size(); i++) {
////        for (int j = 0; j < receiver.size(); j++) {
////            if (pairing_matrix[proposer[i]][receiver[j]] == 1) {
////                cout << proposer[i] << " " << receiver[j] << endl;
////            }
////        }
////    }
//
////    return nice_matching_count;
//    int *return_value = new int [3];
//    //第一个：所有参与者中匹配成功的人数
//    return_value[0] = proposer.size() + receiver.size() - single_count - single_count2;
//    cout << "return_value[0]: " << return_value[0] << endl;
//    if(return_value[0]%2 == 1){
//        //打印出匹配情况 检测异常
//        cout << "pairing result: " << endl;
//        for (int i = 0; i < proposer.size(); i++) {
//            for (int j = 0; j < receiver.size(); j++) {
//                if (pairing_matrix[proposer[i]][receiver[j]] == 1) {
//                    cout << proposer[i] << " " << receiver[j] << endl;
//                }
//            }
//        }
//        //输出proposer和receiver
//        cout << "proposer: ";
//        for (int i = 0; i < proposer.size(); i++) {
//            cout << proposer[i] << " ";
//        }
//        cout << endl;
//        cout << "receiver: ";
//        for (int i = 0; i < receiver.size(); i++) {
//            cout << receiver[i] << " ";
//        }
//        cout << endl;
//    }
//    cout << "pairing result: " << endl;
//    for (int i = 0; i < proposer.size(); i++) {
//        for (int j = 0; j < receiver.size(); j++) {
//            if (pairing_matrix[proposer[i]][receiver[j]] == 1) {
//                cout << proposer[i] << " " << receiver[j] << endl;
//            }
//        }
//    }
//    //输出proposer和receiver
//    cout << "proposer: ";
//    for (int i = 0; i < proposer.size(); i++) {
//        cout << proposer[i] << " ";
//    }
//    cout << endl;
//    cout << "receiver: ";
//    for (int i = 0; i < receiver.size(); i++) {
//        cout << receiver[i] << " ";
//    }
//    cout << endl;
//    //nice matching的人数
//    return_value[1] = nice_matching_count;
//    //proposer总人数
//    return_value[2] = proposer.size();
//    cout << "nice_matching_count: " << nice_matching_count << endl;
//    cout << "proposer.size(): " << proposer.size() << endl;
//
////    cout << "-----------------" << endl << return_value[0] << endl << "-----------------" << endl;
//
//    return return_value;
//
//
//
//
//}//