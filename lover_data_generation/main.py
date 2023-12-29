import json
import random
import os

#list all the provinces of China
province_list = ["河北", "山西", "辽宁", "吉林", "黑龙江", "江苏", "浙江", "安徽", "福建", "江西", "山东", "河南", "湖北", "湖南", "广东", "海南",
                 "四川", "贵州", "云南", "陕西", "甘肃", "青海", "台湾", "内蒙古", "广西", "西藏", "宁夏", "新疆", "北京", "天津", "上海", "重庆",
                 "香港", "澳门"]

class Participant:
    def __init__(self, gender: str, age: int, grade: str, school: str, campus: str, hometown: str, major: int,
                 height: int, weight: int, appearance: str, mbti_flag:bool, mbti: str, hobbies: list, characteristics: str,
                 expect_gender: str, expect_age: int, expect_grade: str, expect_school: str, expect_campus: str,
                 expect_hometown: str,expect_major: str, expect_height: int, expect_weight: int,
                 expect_appearance: str, expect_mbti: str, expect_hobbies: list, expect_characteristics: str,
                  significance_score: list):
        # 13 types of information in total
        self.gender = gender
        self.age = age
        self.grade = grade
        self.school = school
        self.campus = campus
        self.hometown = hometown
        self.major = major
        self.height = height
        self.weight = weight
        self.appearance = appearance
        self.mbti_flag = mbti_flag
        self.mbti = mbti
        self.hobbies = hobbies
        self.characteristics = characteristics
        self.expect_gender = expect_gender
        self.expect_age = expect_age
        self.expect_grade = expect_grade
        self.expect_school = expect_school
        self.expect_campus = expect_campus
        self.expect_hometown = expect_hometown
        self.expect_major = expect_major
        self.expect_height = expect_height
        self.expect_weight = expect_weight
        self.expect_appearance = expect_appearance
        self.expect_mbti = expect_mbti
        self.expect_hobbies = expect_hobbies
        self.expect_characteristics = expect_characteristics
        self.expect_hometown = expect_hometown
        self.significance_score = significance_score

    def __str__(self):
        return "Name: " + self.name + " ID: " + self.id + " Role: " + self.role + " Score: " + self.score



#randomly return a number r, 1<=r<=n
def random_n_generation(n):
    return random.randint(1, n)

def generate_significance_score():
    significance_score = []
    for i in range(12):
        #school and campus belong to the same characteristic actually, so we get 13-1=12 characteristics in total
        significance_score.append(random_n_generation(9))
    #如果期望指数中5分过多，重新生成减少5的个数
    while 1:
        if significance_score.count(10) > 3:
            significance_score[random.randint(0, 11)] = random_n_generation(9)
        else:
            break
    return significance_score

def generate_random_mbti():
    # MBTI dichotomies
    extraversion = random.choice(["E", "I"])
    sensing_intuition = random.choice(["S", "N"])
    thinking_feeling = random.choice(["T", "F"])
    judging_perceiving = random.choice(["J", "P"])

    # Combine dichotomies to create a random MBTI type
    mbti_type = extraversion + sensing_intuition + thinking_feeling + judging_perceiving

    return mbti_type



def generate_participant():
    gender = random_n_generation(2)
    age = random.randint(18, 30)
    #七种年级的可能与问卷中的选项对应
    grade = random_n_generation(7)
    school = random_n_generation(2)
    #1:交大闵行 2：交大徐汇 3.交大医学院 4.华师大闵行 5.华师大中北
    campus = random_n_generation(5)
    province = province_list[random_n_generation(34)-1]
    #七种专业的可能与问卷中的选项对应
    major = random_n_generation(7)
    height = random.randint(150, 200)
    weight = random.randint(40, 100)
    appearance = random.randint(2, 10)
    mbti_flag = random_n_generation(2)
    if mbti_flag == 1:
        mbti = generate_random_mbti()
    else:
        mbti = "None"

    num_hobbies = random_n_generation(12)
    # Generate a list of unique random numbers for hobbies
    hobbies = sorted(random.sample(range(1, 13), num_hobbies))

    # Generate a list of unique random numbers for characteristics
    num_characteristics = random_n_generation(8)
    characteristic = sorted(random.sample(range(1, 18), num_characteristics))

    hometown = province_list[random_n_generation(34)-1]


    expect_gender = random_n_generation(2)
    # expect_age = random.randint(18, 30)
    # 七种年级的可能与问卷中的选项对应
    expect_age = random_n_generation(7)
    # 七种年级的可能与问卷中的选项对应
    expect_grade = random_n_generation(7)
    expect_school = random_n_generation(2)
    # 1:交大闵行 2：交大徐汇 3.交大医学院 4.华师大闵行 5.华师大中北
    expect_campus = random_n_generation(5)
    # expect_province = province_list[random_n_generation(34)-1]
    # 七种专业的可能与问卷中的选项对应
    expect_major = random_n_generation(7)
    # expect_height = random.randint(150, 200)
    expect_height = sorted(random.sample(range(150, 200), 2))
    # expect_weight = random.randint(40, 100)
    expect_weight = sorted(random.sample(range(40, 100), 2))
    # expect_appearance = random.randint(0, 10)
    expect_appearance = sorted(random.sample(range(0, 10), 2))
    if mbti_flag == 1:
        expect_mbti = generate_random_mbti()
    else:
        expect_mbti = "None"

    # num_hobbies = random_n_generation(12)
    # # Generate a list of unique random numbers for hobbies
    # hobbies = random.sample(range(1, 13), num_hobbies)

    # Generate a list of unique random numbers for characteristics
    expect_num_characteristics = random_n_generation(6)
    expect_characteristic = sorted(random.sample(range(1, 18), num_characteristics))

    expect_hometown = province_list[random_n_generation(34) - 1]

    #生成字典存储这些参与者参数
    # Generate the dictionary to store participant data
    participant_dict = {
        "gender": gender,
        "age": age,
        "grade": grade,
        "school": school,
        "campus": campus,
        # "province": province,
        "major": major,
        "height": height,
        "weight": weight,
        "appearance": appearance,
        "mbti_flag": mbti_flag,
        "mbti": mbti,
        "num_hobbies": num_hobbies,
        "hobbies": hobbies,
        "num_characteristics": num_characteristics,
        "characteristic": characteristic,
        "hometown": hometown,
        "expect_gender": expect_gender,
        "expect_age": expect_age,
        "expect_grade": expect_grade,
        "expect_school": expect_school,
        "expect_campus": expect_campus,
        # "expect_province": expect_province,
        "expect_major": expect_major,
        "expect_height": expect_height,
        "expect_weight": expect_weight,
        "expect_appearance": expect_appearance,
        # "expect_mbti_flag": mbti_flag,
        "expect_mbti": expect_mbti,
        # "expect_num_hobbies": expect_num_hobbies,
        # "expect_hobbies": expect_hobbies,
        "expect_num_characteristics": expect_num_characteristics,
        "expect_characteristic": expect_characteristic,
        "expect_hometown": expect_hometown,
        "significance_score": generate_significance_score()
    }

    return participant_dict


def generate_fixed_gender_participant(gender, expect_gender):
    raw = generate_participant()
    raw["gender"] = gender
    raw["expect_gender"] = expect_gender
    return raw

def zh_write_jsonl(data, jsonl_file_path, mode="w"):
    # data is a list, each of the item is json-serilizable
    assert isinstance(data, list)
    if not os.path.exists(os.path.dirname(jsonl_file_path)):
        os.makedirs(os.path.dirname(jsonl_file_path))
    with open(jsonl_file_path, mode) as f:
        for item in data:
            f.write(json.dumps(item, ensure_ascii=False) + '\n')


if __name__ == '__main__':
    data = []
    for i in range(400):
        # data.append(generate_participant())
        data.append(generate_fixed_gender_participant(1, 2))
        data.append(generate_fixed_gender_participant(2, 1))
    for i in range(100):
        data.append(generate_fixed_gender_participant(1, 2))
    #homo
    for i in range(29):
        data.append(generate_fixed_gender_participant(1, 1))
    for i in range(17):
        data.append(generate_fixed_gender_participant(2, 2))

    # for i in range(50):
    #     # data.append(generate_participant())
    #     data.append(generate_fixed_gender_participant(1, 2))
    #     data.append(generate_fixed_gender_participant(2, 1))
    # for i in range(50):
    #     data.append(generate_fixed_gender_participant(1, 2))

    zh_write_jsonl(data, "./testdata_matching.jsonl", mode="w")
    print("written successfully!")



