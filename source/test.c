#include<stdio.h>
#include<string.h>
#include<malloc.h>

int main()
{
		char *key=(char*)malloc(sizeof(char)*30);
		char *skey=(char*)malloc(sizeof(char)*30);
		scanf("%s%s",key,skey);
		
		printf("%d ",strlen(key));
		printf("%d ",strlen(skey));
}
