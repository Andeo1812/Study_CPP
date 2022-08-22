#!/usr/bin/env bash

set -o pipefail

function print_header() {
    echo -e "\n***** ${1} *****"
}

function check_log() {
    LOG=$( { ${1}; } 2>&1 )
    STATUS=$?
    echo "$LOG"
    if echo "$LOG" | grep -q -E "${2}"
    then
        exit 1
    fi

    if [ $STATUS -ne 0 ]
    then
        exit $STATUS
    fi
}

Tests_cpp="tests/unit_tests/*.cpp"

main="project/main.cpp"

Config_hpp="project/configs/*.hpp"
Config_path_hpp="-I project/configs/"

Context_hpp="project/context/include/*/*.hpp"
Context_cpp="project/context/src/*/*"
Context_path_hpp="-I project/context/include -I project/context/include/Data -I project/context/include/Group"

Database_hpp="project/database/include/*/*"
Database_path_hpp="-I project/database/include/virtual -I project/database/include/impl -I project/database/PostgreSQL"

Parsing_hpp="project/parsing/include/impl/*.hpp project/parsing/include/impl/Data/*.hpp project/parsing/include/impl/Group/*.hpp project/parsing/include/virtual/*.hpp"
Parsing_cpp="project/parsing/JSON/src/*.cpp project/parsing/JSON/src/Data/*.cpp project/parsing/JSON/src/Group/*.cpp"
Parsing_path_hpp="-I project/parsing/include/impl -I project/parsing/include/impl/Data -I project/parsing/include/impl/Group -I project/parsing/include/virtual"

Handling_hpp="project/handling/include/impl/*.hpp project/handling/include/impl/Data/*.hpp project/handling/include/impl/Group/*.hpp project/handling/include/virtual/*.hpp project/handling/definition/Group/MeetUp/SupportMeetUp/include/*.hpp"
Handling_cpp="project/handling/definition/Group/MeetUp/SupportMeetUp/src/*.cpp"
Handling_path_hpp="-I project/handling/include/impl -I project/handling/include/impl/Data -I project/handling/include/impl/Group -I project/handling/include/virtual -I project/handling/definition/Group/MeetUp/SupportMeetUp/include -I project/handling/definition -I project/handling/definition/Data -I project/handling/definition/Group/Base/ -I project/handling/definition/Group/User -I project/handling/definition/Group/MeetUp"

Routing_hpp="project/routing/include/impl/*.hpp project/routing/include/virtual/*.hpp"
Routing_path_hpp="-I project/routing/include/impl -I project/routing/include/virtual -I project/routing/definition"

Sum_hpp="${Config_hpp} ${Context_hpp} ${Database_hpp} ${Parsing_hpp} ${Handling_hpp} ${Routing_hpp}"
Sum_cpp="${main} ${Context_cpp} ${Parsing_cpp} ${Handling_cpp} ${Tests_cpp}"

Sum_path_hpp="${Config_path_hpp} ${Context_path_hpp} ${Database_path_hpp} ${Handling_path_hpp} ${Routing_path_hpp} ${Parsing_path_hpp}"


print_header "RUN cppcheck"
check_log "cppcheck ${Sum_cpp} ${Sum_hpp} --enable=all --check-config --inconclusive --error-exitcode=1 ${Sum_path_hpp} --suppress=missingIncludeSystem" "\(information\)"

#print_header "RUN clang-tidy"
#check_log "clang-tidy ${Sum_cpp} ${Sum_hpp} -warnings-as-errors=*  -- -x c++ ${Sum_path_hpp}" "Error (?:reading|while processing)"

print_header "RUN cpplint"
check_log "cpplint --extensions=cpp ${Sum_cpp} ${Sum_hpp}" "Can't open for reading"

print_header "SUCCESS"
