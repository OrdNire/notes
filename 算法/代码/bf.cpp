#include <stdio.h>

//Æ¥Åä³É¹¦·µ»ØË÷Òı£¬Æ¥ÅäÊ§°Ü·µ»Ø-1 
int bf(const char s[],const char t[]){
	int start = 0;
	int i = 0,j = 0;
	while((s[i] != '\0') && (t[j] != '\0')){
		if(s[i] == t[j]){
			i ++;
			j ++;
		}else{
			start ++;
			i = start;
			j = 0;
		}
	}
	if(t[j] == '\0') return j;
	else return -1;
}

int main()
{
	printf("%d\n",bf("abcdef","cd"));
	printf("%d\n",bf("abcdef","ced"));
	return 0;
}
