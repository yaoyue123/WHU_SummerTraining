#include <stdio.h>
#include <string.h>

int main() {
    int n;
    scanf("%d\n", &n);
    
    char input;

    char name[n][100];//i 代表学生的编号 j 储存学生的名字
    
    //读入所有的名字到数组的各个行
    for (int i = 0; i < n; i++){
        gets(name[i]);
    }
    
    //找出最长的名字
    char name_max[100];
    
    strcpy(name_max, name[0]);

    for(int i = 1; i < n; i++){
        if(strlen(name_max) < strlen(name[i]))
            strcpy(name_max, name[i]);
    }

    printf("%s", name_max);
    
    return 0;
}