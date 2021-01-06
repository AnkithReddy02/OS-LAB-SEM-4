#include<stdio.h> // for stdin , stdout.
#include<stdlib.h> // for exiting program
void main(int argc, char const *argv[])
{
	int numNonPrintedArgs = 0;

	for(int i=1;i<argc;i++) // start from 1 as 0th index represents 'command-line program name'.
	{
		if(argv[i][0]!='-') // check the first character of the argument as if there is any '-' character.
		{
			printf("%s ",argv[i]);
		}
		else
		{
			numNonPrintedArgs++;
		}
	}
	if(numNonPrintedArgs!=argc-1) // condition for printing new line character.
	{
		printf("\n");
	}
	
	exit(0);
}
