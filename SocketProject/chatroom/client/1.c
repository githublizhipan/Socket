/*************************************************************************
	> File Name: 1.c
	> Author: 
	> Mail: 
	> Created Time: 2020年03月31日 星期二 21时52分27秒
 ************************************************************************/

#include<stdio.h>
#include <string.h>

int main() {
    char name[50][500];
    char str[500];
    for(int i = 1; i <= 5; i++) {
        scanf("%s", name[i]);
    }
    for(int i = 1; i <= 5; i++) {
        sprintf(str + strlen(str), "%s\n", name[i]);
    }

    printf("---------------\n%s", str);
    return 0;
}
