#include<stdio.h>
int main(int argc, char const *argv[])
{
	int numNonPrintedArgs = 0;

	for(int i=1;i<argc;i++)
	{
		if(argv[i][0]!='-')
		{
			printf("%s ",argv[i]);
		}
		else
		{
			numNonPrintedArgs++;
		}
	}
	if(numNonPrintedArgs!=argc-1)
	{
		printf("\n");
	}
	return 0;
}
