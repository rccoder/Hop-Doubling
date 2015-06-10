#!/bin/bash 
echo "正在自动生成数据........."
if [ -f "./data.txt" ]; then
    echo "曾经残留data.txt,正在删除"
    rm ./data.txt 
else
    echo " "
fi
g++ ./data.cpp 
./a.out >> data.txt
echo "生产数据完毕，数据内容保存在data.txt"
echo "程序启动中....."
g++ ./main.cpp 
echo "编译完毕，正在输出内容"
echo "............................................"
./a.out 
echo "............................................"

