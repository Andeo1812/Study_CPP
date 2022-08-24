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

main="project/main.cpp"

Core_hpp="project/Core/include/*.hpp project/Core/definition/*.hpp"
Core_path_hpp="-I project/Core/include -I project/Core/definition"

Sum_hpp="${Core_hpp}"
Sum_cpp="${main}"

Sum_path_hpp="${Core_path_hpp}"


print_header "RUN cppcheck"
check_log "cppcheck ${Sum_cpp} ${Sum_hpp} --enable=all --check-config --inconclusive --error-exitcode=1 ${Sum_path_hpp} --suppress=missingIncludeSystem" "\(information\)"

#print_header "RUN clang-tidy"
#check_log "clang-tidy ${Sum_cpp} ${Sum_hpp} -warnings-as-errors=*  -- -x c++ ${Sum_path_hpp}" "Error (?:reading|while processing)"

print_header "RUN cpplint"
check_log "cpplint --extensions=cpp ${Sum_cpp} ${Sum_hpp}" "Can't open for reading"

print_header "SUCCESS"
