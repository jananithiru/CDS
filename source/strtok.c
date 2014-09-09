#include "headers.h"
char* strTok(char *string, char *delimiter)
{
	static int remstring=0;
	static char *str;

	if(string!=NULL)
	{
	        int length=strlen(string);
		str=(char*)malloc(sizeof(char)*(length+1));
		strcpy(str,string);
		str[length]='\0';
	}
	int i;
	char *return_string=NULL;
	if(delimiter==NULL)
		return str;
	for(i=remstring;i<=strlen(str);i++)
	{
		if(str[i]==delimiter[0] || str[i]=='\0')
		{
			int len;
			return_string=(char*)malloc(sizeof(char)*(len=(i-(remstring)+1)));
			int k,l;
			for(k=0,l=remstring;k<(len-1)&&(str[l]!='\n');k++,l++)
				return_string[k]=str[l];
			return_string[k]='\0';
			remstring=i+1;
			return return_string;
		}
	}

	if(string!=NULL)
		return string;
	if(string==NULL)
	{
			remstring=0;
			free(str);
		return NULL; 
	}
}


























