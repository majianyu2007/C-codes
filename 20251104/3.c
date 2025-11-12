#include <stdio.h>

//函数声明
double CalculateAverage(double s1, double s2, double s3);
char GetGrade(double avg);
void PrintReport(int id, double avg, char grade);

int main() {

    int id = 1001;
    double score1 = 85.5, score2 = 92.0, score3 = 78.5;

    // 计算平均分
    double avg = CalculateAverage(score1, score2, score3);

    // 获取等级
    char grade = GetGrade(avg);

    // 输出成绩报告
    PrintReport(id, avg, grade);

    return 0;
}

// 计算三门课平均分
double CalculateAverage(double s1, double s2, double s3) {
    return (s1 + s2 + s3) / 3.0;
}

// 根据平均分返回等级，使用?: 运算符
char GetGrade(double avg) {
    return (avg >= 90.0) ? 'A' :
           (avg >= 80.0) ? 'B' :
           (avg >= 70.0) ? 'C' : 'D';
}

// 输出成绩报告
void PrintReport(int id, double avg, char grade) {
    printf("ID:%d, Average:%.2f, Grade:%c\n", id, avg, grade);
}

