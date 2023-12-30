cmake_minimum_required(VERSION 3.10)
project(jsonl_test)

find_package(nlohmann_json 3.2.0 REQUIRED)

add_executable(jsonl_test main.cpp
        scoring_util.h
        scoring_util.cpp
        Participant.h
        util.h
        util2.cpp)
target_link_libraries(jsonl_test PRIVATE nlohmann_json::nlohmann_json)

