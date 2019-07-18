#include <stdio.h>
#include <string.h>

int main() {
	int n;
	char input;
	char name[100][101];//i 代表学生的编号 j 储存学生的名字
	char name_max[101]={ '\0' };//找出最长的名字

	scanf("%d\n", &n);
	//读入所有的名字到数组的各个行
	for (int i = 0; i < n; i++) {
		gets(name[i]);
	}

	strcpy(name_max, name[0]);

	for (int i = 1; i < n; i++) {
		if (strlen(name_max) < strlen(name[i]))
			strcpy(name_max, name[i]);
	}
	for(int i = 0; i < 100; i++){
        if(name_max[i] != '\0' )
        printf("%c", name_max[i]);
	}

	return 0;
}