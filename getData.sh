#!/bin/bash 
if [ -f "./data.txt" ]; then
    echo "曾经存在data.txt，现已删除,并且自动生成"
    rm data.txt
else
    echo "曾经不存在data.txt，正在生成"
fi
g++ data.cpp
./a.out >> data.txt
