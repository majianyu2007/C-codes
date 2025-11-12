#!/bin/bash
# 自动提交并推送当前仓库改动
# 使用当前时间作为提交信息

# 切换到脚本所在目录（可选，防止误运行）
cd "$(dirname "$0")"

# 检查是否为 Git 仓库
if [ ! -d .git ]; then
    echo "❌ 当前目录不是一个 Git 仓库。"
    exit 1
fi

# 获取当前时间作为提交信息
commit_msg="$(date '+%Y-%m-%d %H:%M:%S')"

# 添加所有变更
git add -A

# 提交
git commit -m "$commit_msg"

# 推送（默认推送到当前分支）
git push

# 完成提示
echo "✅ 已提交并推送: $commit_msg"

