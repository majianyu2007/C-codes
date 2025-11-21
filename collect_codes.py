import os

output_file = "all_codes.md"

with open(output_file, "w", encoding="utf-8") as md:
    for root, dirs, files in os.walk("."):
        for file in files:
            if file.endswith(".c"):
                path = os.path.join(root, file)
                rel_path = os.path.relpath(path, ".")
                
                md.write(f"# {rel_path}\n\n")
                md.write("```c\n")
                with open(path, "r", encoding="utf-8") as f:
                    md.write(f.read())
                md.write("\n```\n\n")

print(f"已生成：{output_file}")

## 请根据markdown中的代码，反推出代码的作业题目（问题+考点）尽量简略（要打印，节约用纸），总结至一级标题下的二级标题
