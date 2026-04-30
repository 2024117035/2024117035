#include <stdio.h>

int main() {
    char input[100]; // 定义数组存储输入内容
    printf("请输入内容：");
    scanf("%s", input); // 读取键盘输入
    printf("你输入的内容是：%s\n", input);
    return 0;
}
