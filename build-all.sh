#!/bin/bash
# 自动递归编译当前目录下的所有 .c 文件（含 math.h）

find . -type f -name "*.c" | while read -r cfile; do
    exe="${cfile%.c}"
    echo "正在编译: $cfile -> $exe"

    # 判断文件中是否包含 math.h
    if grep -q "math.h" "$cfile"; then
        # 包含 math.h：链接数学库
        gcc "$cfile" -o "$exe" -lm -Wall
    else
        # 不包含 math.h：正常编译
        gcc "$cfile" -o "$exe" -Wall
    fi

    # 检查编译结果
    if [ $? -eq 0 ]; then
        echo "✅ 编译成功: $exe"
    else
        echo "❌ 编译失败: $cfile"
    fi
done

