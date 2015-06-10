#!/bin/bash
if [ -f "./a.out" ]; then
    echo "存在a.out,正在删除"
    rm ./a.out
else
    echo "不存在需要清理的东西"
fi
echo "清理完毕"
