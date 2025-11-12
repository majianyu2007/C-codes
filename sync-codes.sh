#!/bin/bash
# ============================================================
# 双向同步脚本：rsync over SSH
# 作者: majianyu
# 说明:
#   - 从服务器下载: ./sync-codes.sh pull
#   - 上传到服务器: ./sync-codes.sh push
# ============================================================

# === 用户配置区域 ===
LOCAL_DIR="$HOME/codes"
REMOTE_USER="s13665"
REMOTE_HOST="172.29.1.84"
REMOTE_DIR="/home/${REMOTE_USER}/codes"

# === rsync 通用参数 ===
RSYNC_OPTS="-avz --delete --progress"

# === 检查参数 ===
if [ $# -ne 1 ]; then
    echo "用法: $0 [push|pull]"
    echo "  push : 本地 -> 服务器"
    echo "  pull : 服务器 -> 本地"
    exit 1
fi

ACTION=$1

# === 确保本地目录存在 ===
if [ ! -d "$LOCAL_DIR" ]; then
    echo "本地目录不存在: $LOCAL_DIR"
    exit 2
fi

# === 执行同步 ===
if [ "$ACTION" = "push" ]; then
    echo "📤 正在将本地 -> 服务器 同步中..."
    rsync $RSYNC_OPTS "$LOCAL_DIR/" "${REMOTE_USER}@${REMOTE_HOST}:${REMOTE_DIR}/"

elif [ "$ACTION" = "pull" ]; then
    echo "📥 正在从服务器 -> 本地 同步中..."
    rsync $RSYNC_OPTS "${REMOTE_USER}@${REMOTE_HOST}:${REMOTE_DIR}/" "$LOCAL_DIR/"

else
    echo "无效操作: $ACTION"
    echo "用法: $0 [push|pull]"
    exit 3
fi

echo "✅ 同步完成。"
