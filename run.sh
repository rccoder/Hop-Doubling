#!/bin/bash 
if [ ! -f "./data.txt"  ]; then
    echo "不存在data.txt,请运行./getData.sh生成"
else
    g++ main.cpp 
    ./a.out
fi
