// Description: 打分函数实现
#include "scoring_util.h"
#include "Participant.h"
#include <vector>

using namespace std;
double age_scoring(Participant p1, Participant p2){
    int a1 = p1.age;
    int a2 = p2.age;
    bool match=false;
    //p2相对于p1的年龄得分
    if ((p1.expect_age==1 && a2-a1>=1 && a2-a1<=3)||(p1.expect_age==2&&a2-a1>=3 && a2-a1<=5)||(p1.expect_age==3&&a2-a1>=5)||(p1.expect_age==4&&a1-a2>=1 && a1-a2<=3)||(p1.expect_age==10&&a1-a2>=3 && a1-a2<=5)||(p1.expect_age==6&&a1-a2>=5)||(p1.expect_age==7&&a1==a2)){
        match=true;
    }
    if(p1.significance_score[0]==10 && !match){
        return -100;
    }
    else{
        if(match){
            return 15*1.0*p1.significance_score[0]/10;
        }
        else{
            return (-5)*1.0*p1.significance_score[0]/10;
        }
    }
//        else if ((p1.expect_age==1 && a2-a1>=3 && a2-a1<=5)||(p1.expect_age==2&&a2-a1>=5 && a2-a1<=7)||(p1.expect_age==3&&a2-a1>=7)||(p1.expect_age==4&&a1-a2>=3 && a1-a2<=5)||(p1.expect_age==10&&a1-a2>=5 && a1-a2<=7)||(p1.expect_age==6&&a1-a2>=7)){
//            return 0.8;
//        }
//        else if ((p1.expect_age==1 && a2-a1>=5)||(p1.expect_age==2&&a2-a1>=7)||(p1.expect_age==3&&a2-a1>=9)||(p1.expect_age==4&&a1-a2>=5)||(p1.expect_age==10&&a1-a2>=7)||(p1.expect_age==6&&a1-a2>=9)){
//            return 0.6;
//        }
//        else if ((p1.expect_age==1 && a2-a1<=1)||(p1.expect_age==2&&a2-a1<=3)||(p1.expect_age==3&&a2-a1<=5)||(p1.expect_age==4&&a1-a2<=1)||(p1.expect_age==10&&a1-a2<=3)||(p1.expect_age==6&&a1-a2<=5)){
//            return 0.4;
//        }
//        else if ((p1.expect_age==1 && a2-a1<=3)||(p1.expect_age==2&&a2-a1<=5)||(p1.expect_age==3&&a2-a1<=7)||(p1.expect_age==4&&a1-a2<=3)||(p1.expect_age==10&&a1-a2<=5)||(p1.expect_age==6&&a1-a2<=7)){
//            return 0.2;
//        }
//        else{
//            return 0;
}

double height_scoring(Participant p1, Participant p2){
    bool match_low = true;
    bool match_high = true;
    double score = 0;
    //set match_low and match_high
    if(p2.height < p1.expect_height[0]){
        match_low = false;
    }
    if(p2.height > p1.expect_height[1]){
        match_high = false;
    }
    if((match_low == false||match_high==false) && p1.significance_score[5]==10){
        return -100;
    }
    if(match_low == true){
        score += 5*1.0*p1.significance_score[5]/10;
    }
    else{
        score += (-2)*1.0*p1.significance_score[5]/10;
    }
    if(match_high == true){
        score += 5*1.0*p1.significance_score[5]/10;
    }
    else{
        score += (-2)*1.0*p1.significance_score[5]/10;
    }

    return score;
}

double weight_scoring(Participant p1, Participant p2){
    bool match_low = true;
    bool match_high = true;
    double score = 0;
    //set match_low and match_high
    if(p2.weight < p1.expect_weight[0]){
        match_low = false;
    }
    if(p2.weight > p1.expect_weight[1]){
        match_high = false;
    }
    if((match_low == false||match_high==false) && p1.significance_score[6]==10){
        return -100;
    }
    if(match_low == true){
        score += 5*1.0*p1.significance_score[6]/10;
    }
    else{
        score += (-2)*1.0*p1.significance_score[6]/10;
    }
    if(match_high == true){
        score += 5*1.0*p1.significance_score[6]/10;
    }
    else{
        score += (-2)*1.0*p1.significance_score[6]/10;
    }

    return score;
}

double appearance_scoring(Participant p1, Participant p2){
    bool match_low = true;
    bool match_high = true;
    double score = 0;
    //set match_low and match_high
    if(p2.appearance < p1.expect_appearance[0]){
        match_low = false;
    }
    if(p2.appearance > p1.expect_appearance[1]){
        match_high = false;
    }
    if((match_low == false||match_high==false) && p1.significance_score[7]==10){
        return -100;
    }
    if(match_low == true){
        score += 5*1.0*p1.significance_score[7]/10;
    }
    else{
        score += (-3)*1.0*p1.significance_score[7]/10;
    }
    if(match_high == true){
        score += 5*1.0*p1.significance_score[7]/10;
    }
    else{
        score += (-3)*1.0*p1.significance_score[7]/10;
    }

    return score;
}

//mbti逐个要素打分,奖励2分，惩罚1分,同样考虑significance_score
double mbti_scoring(Participant p1, Participant p2){
    double score = 0;
    if(p2.mbti_flag == 0){
        return 0;
    }
    if(p1.expect_mbti[0] == p2.mbti[0]){
        score += 2*1.0*p1.significance_score[8]/10;
    }
    else{
        score += (-1)*1.0*p1.significance_score[8]/10;
    }
    if(p1.expect_mbti[1] == p2.mbti[1]){
        score += 2*1.0*p1.significance_score[8]/10;
    }
    else{
        score += (-1)*1.0*p1.significance_score[8]/10;
    }
    if(p1.expect_mbti[2] == p2.mbti[2]){
        score += 2*1.0*p1.significance_score[8]/10;
    }
    else{
        score += (-1)*1.0*p1.significance_score[8]/10;
    }
    if(p1.expect_mbti[3] == p2.mbti[3]){
        score += 2*1.0*p1.significance_score[8]/10;
    }
    else{
        score += (-1)*1.0*p1.significance_score[8]/10;
    }

    return score;
}

//hobbies匹配度打分，全匹配上+10，全匹配不上-3，部分匹配上按比例加减分
double hobbies_scoring(Participant p1, Participant p2){
    double score = 0;
    int match_num = 0;
    for(int idx1 = 0;idx1 < p1.num_hobbies;idx1++){
        for(int idx2 = 0;idx2 < p2.num_hobbies;idx2++){
            if(p1.hobbies[idx1] == p2.hobbies[idx2]){
                match_num++;
            }
        }
    }
    if(match_num == p1.num_hobbies){
        score += 10*1.0*p1.significance_score[9]/10;
    }
    else if(match_num == 0){
        if(p1.significance_score[9]==10){
            return -100;
        }
        else{
            score += (-3)*1.0*p1.significance_score[9]/10;
        }
    }
    else{
        score += (match_num*1.0/p1.num_hobbies)*1.0*p1.significance_score[9]/10;
    }
    return score;
}

//characteristics匹配度打分，全匹配上+10，全匹配不上-3，部分匹配上按比例加减分
double characteristics_scoring(Participant p1, Participant p2){
    double score = 0;
    int match_num = 0;
    for(int idx1 = 0;idx1 < p1.num_characteristics;idx1++){
        for(int idx2 = 0;idx2 < p2.num_characteristics;idx2++){
            if(p1.characteristic[idx1] == p2.characteristic[idx2]){
                match_num++;
            }
        }
    }
    if(match_num == p1.num_characteristics){
        score += 10*1.0*p1.significance_score[10]/10;
    }
    else if(match_num == 0){
        if(p1.significance_score[10]==10){
            return -100;
        }
        else{
            score += (-3)*1.0*p1.significance_score[10]/10;
        }
    }
    else{
        score += (match_num*1.0/p1.num_characteristics)*1.0*p1.significance_score[10]/10;
    }

    return score;
}