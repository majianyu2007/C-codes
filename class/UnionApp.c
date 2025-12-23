#include <stdio.h>

// 1. 定义一个union来查看double的字节存储
union DoubleViewer {
    double d;        // 8字节的浮点数
    unsigned char bytes[8];  // 8个字节
    unsigned long long ull;  // 8字节的整数
};

// 2. 定义一个union查看整数的二进制表示
union IntViewer {
    int num;
    unsigned char bytes[4];
};

// 3. 定义一个union来演示共用体的特点
union Data {
    int i;
    float f;
    char c;
};

// 4. union在网络通信中的应用
union IPAddress {
    unsigned int addr;           // 32位IP地址
    unsigned char octets[4];     // 分别为 192.168.1.1 中的 192, 168, 1, 1
};

int main()
{
    printf("========== 1. 按字节查看double类型的存储 ==========\n");
    double d = 11.23456;
    
    union DoubleViewer dv;
    dv.d = d;
    
    printf("double值: %.5f\n", dv.d);
    printf("大小: %zu 字节\n", sizeof(double));
    printf("按字节显示（十六进制）: ");
    for (int i = 0; i < 8; i++) {
        printf("%02X ", dv.bytes[i]);
    }
    printf("\n");
    printf("按十进制显示: ");
    for (int i = 0; i < 8; i++) {
        printf("%d ", dv.bytes[i]);
    }
    printf("\n");
    printf("作为整数看: %llu\n\n", dv.ull);

    printf("========== 2. 演示union的共享内存特性 ==========\n");
    union Data data;
    
    // 修改整数成员
    data.i = 65;  // ASCII值65是字母'A'
    printf("赋值 data.i = 65\n");
    printf("查看 data.c: %c (ASCII值: %d)\n", data.c, (unsigned char)data.c);
    printf("查看 data.f: %f\n\n", data.f);
    
    // 修改浮点数成员
    data.f = 3.14f;
    printf("赋值 data.f = 3.14\n");
    printf("查看 data.i: %d\n", data.i);
    printf("查看 data.c: %c (ASCII值: %d)\n\n", data.c, (unsigned char)data.c);

    printf("========== 3. union和struct的大小对比 ==========\n");
    
    struct StructData {
        int i;
        float f;
        char c;
    };
    
    printf("struct StructData的大小: %zu 字节\n", sizeof(struct StructData));
    printf("union Data的大小: %zu 字节\n", sizeof(union Data));
    printf("int的大小: %zu 字节\n", sizeof(int));
    printf("float的大小: %zu 字节\n", sizeof(float));
    printf("char的大小: %zu 字节\n\n", sizeof(char));

    printf("========== 4. 查看整数的字节组成 ==========\n");
    union IntViewer iv;
    iv.num = 0x12345678;
    
    printf("整数值: 0x%X\n", iv.num);
    printf("按字节查看: ");
    for (int i = 0; i < 4; i++) {
        printf("%02X ", iv.bytes[i]);
    }
    printf("\n");
    printf("大小端判断: ");
    if (iv.bytes[0] == 0x78) {
        printf("小端序（Intel x86处理器）\n\n");
    } else {
        printf("大端序\n\n");
    }

    printf("========== 5. IP地址的union应用 ==========\n");
    union IPAddress ip;
    ip.octets[0] = 192;
    ip.octets[1] = 168;
    ip.octets[2] = 1;
    ip.octets[3] = 100;
    
    printf("IP地址: %d.%d.%d.%d\n", 
           ip.octets[0], ip.octets[1], ip.octets[2], ip.octets[3]);
    printf("作为32位无符号整数: %u (0x%X)\n", ip.addr, ip.addr);
    printf("大小: %zu 字节\n\n", sizeof(union IPAddress));

    printf("========== 6. 修改部分字节 ==========\n");
    union DoubleViewer dv2;
    dv2.d = 100.5;
    printf("原始double值: %.1f\n", dv2.d);
    printf("修改第一个字节...\n");
    dv2.bytes[0] = 0xFF;  // 修改第一个字节
    printf("修改后double值: %.15f\n", dv2.d);
    printf("（说明：修改了内存中的一个字节，影响了整个浮点数的解释）\n");

    return 0;
}
