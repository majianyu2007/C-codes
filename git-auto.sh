#!/bin/bash

# ================================
#   颜色定义
# ================================
RED="\033[31m"
GREEN="\033[32m"
YELLOW="\033[33m"
BLUE="\033[34m"
RESET="\033[0m"

# ================================
#   切换到脚本所在目录
# ================================
cd "$(dirname "$0")"

# ================================
#   确认 git 仓库
# ================================
if [ ! -d .git ]; then
    echo -e "${RED}❌ 当前目录不是 Git 仓库${RESET}"
    exit 1
fi

# ================================
#   当前分支
# ================================
branch=$(git rev-parse --abbrev-ref HEAD)
echo -e "${BLUE}📌 当前分支：${YELLOW}$branch${RESET}"

# ================================
#   参数解析
# ================================
NO_PUSH=false
AMEND=false
USE_STASH=false
MSG_ARG=""

while [[ $# -gt 0 ]]; do
    case "$1" in
        -m)
            MSG_ARG="$2"
            shift 2
            ;;
        --no-push)
            NO_PUSH=true
            shift
            ;;
        --amend)
            AMEND=true
            shift
            ;;
        --stash)
            USE_STASH=true
            shift
            ;;
        *)
            echo -e "${RED}❌ 未知参数：$1${RESET}"
            exit 1
            ;;
    esac
done

# ================================
#   自动 stash - 可选
# ================================
if $USE_STASH; then
    echo -e "${BLUE}📦 正在 stash 未提交更改...${RESET}"
    git stash push -m "auto-stash-$(date '+%Y-%m-%d_%H-%M-%S')"
fi

# ================================
#   检查是否有改动
# ================================
if git diff --quiet && git diff --cached --quiet; then
    echo -e "${YELLOW}⚠️ 没有检测到修改，结束。${RESET}"
    exit 0
fi

# ================================
#   获取 commit message
# ================================
if [ -n "$MSG_ARG" ]; then
    message="$MSG_ARG"
else
    echo -e "${BLUE}📝 请输入 commit 信息（支持中文、多行，按 Ctrl+D 完成，回车空则用当前时间）：${RESET}"
    echo -e "${YELLOW}（提示：多行输入时换行即可，结束输入按 Ctrl+D）${RESET}"
    input=$(cat)
    if [ -z "$input" ]; then
        message="$(date '+%Y-%m-%d %H:%M:%S')"
    else
        message="$input"
    fi
fi

echo -e "${GREEN}🔧 使用提交信息：${YELLOW}$message${RESET}"

# ================================
#   执行 commit
# ================================
git add -A

if $AMEND; then
    git commit --amend -m "$message"
else
    git commit -m "$message"
fi

# ================================
#   推送（可选 no-push）
# ================================
if ! $NO_PUSH; then
    git push
    echo -e "${GREEN}🚀 已推送到远程 ${YELLOW}$branch${RESET}"
else
    echo -e "${YELLOW}⚠️ --no-push：未推送到远程。${RESET}"
fi

# ================================
#   自动 stash pop
# ================================
if $USE_STASH; then
    echo -e "${BLUE}📦 恢复之前 stash 的内容（stash pop）${RESET}"
    git stash pop
fi

echo -e "${GREEN}✨ 完成！${RESET}"
