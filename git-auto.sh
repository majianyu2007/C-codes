#!/bin/bash

# ============================
#   颜色定义
# ============================
RED="\033[31m"
GREEN="\033[32m"
YELLOW="\033[33m"
BLUE="\033[34m"
RESET="\033[0m"

# ============================
#   切换到脚本所在目录（可选）
# ============================
cd "$(dirname "$0")"

# ============================
#   检查是否为 Git 仓库
# ============================
if [ ! -d .git ]; then
    echo -e "${RED}❌ 当前目录不是一个 Git 仓库。${RESET}"
    exit 1
fi

# ============================
#   显示当前分支
# ============================
current_branch=$(git rev-parse --abbrev-ref HEAD)
echo -e "${BLUE}📌 当前分支：${YELLOW}${current_branch}${RESET}"

# ============================
#   获取命令行参数 -m
# ============================
user_msg=""

while getopts "m:" opt; do
    case $opt in
        m)
            user_msg="$OPTARG"
            ;;
        \?)
            echo -e "${RED}❌ 无效参数。${RESET}"
            exit 1
            ;;
    esac
done

# ============================
#   检查是否有修改
# ============================
if git diff --quiet && git diff --cached --quiet; then
    echo -e "${YELLOW}⚠️ 没有检测到任何改动，已退出。${RESET}"
    exit 0
fi

# ============================
#   获取最终 commit message
# ============================

if [ -n "$user_msg" ]; then
    # 使用 -m 参数内容
    commit_msg="$user_msg"
else
    # 交互获取
    echo -e "${BLUE}📝 请输入 commit 信息（直接回车则自动使用当前时间）：${RESET}"
    read input_msg

    if [ -z "$input_msg" ]; then
        commit_msg="$(date '+%Y-%m-%d %H:%M:%S')"
    else
        commit_msg="$input_msg"
    fi
fi

echo -e "${GREEN}🔧 使用 commit 信息：${YELLOW}$commit_msg${RESET}"

# ============================
#   Git 提交流程
# ============================
git add -A
git commit -m "$commit_msg"
git push

echo -e "${GREEN}✅ 已成功提交并推送到分支：${YELLOW}${current_branch}${RESET}"
