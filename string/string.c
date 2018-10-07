#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define d 10000
int main()
{int a[10][10];
	char *p;
	p=(char*)malloc(300*sizeof(char));
	
	char c[10];
	for(int i=0;i<10;i++)
	{for(int j=0;j<10;j++)
			a[i][j]=j;
	}
	p[0]='\0';	
	for(int i=0;i<10;i++)
	{
		for(int j=0;j<10;j++)
		{sprintf(c,"%d ",a[i][j]);

		strcat(p,c);
		}strcat(p,"\n");	}
	FILE *write;
	write=fopen("new.txt","wb");
	fputs(p,write);
	printf("%s",p);
	return 0;
}
