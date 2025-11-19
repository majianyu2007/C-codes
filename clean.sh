#!/bin/bash
set -e

echo "==== 查找所有『可执行 + 无扩展名』的二进制文件 ===="
echo

# 找出所有可执行且无扩展名的普通文件
files=$(find . -type f -executable ! -name "*.*")

if [ -z "$files" ]; then
    echo "未发现任何可删除的可执行文件。"
    exit 0
fi

echo "以下文件将被删除："
echo "----------------------------------------"
echo "$files"
echo "----------------------------------------"
echo

read -p "确认删除吗？(y/N) " confirm

if [[ "$confirm" != "y" && "$confirm" != "Y" ]]; then
    echo "已取消操作。"
    exit 0
fi

echo
echo "正在删除..."
echo "$files" | xargs rm -f

echo "清理完成！"

