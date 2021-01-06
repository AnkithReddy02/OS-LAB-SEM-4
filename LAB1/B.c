#include<stdio.h> // standard input output
#include<string.h> // for string operations.(strlen(s) -> to get the string length)
#include<stdlib.h> // used to exit (in this program) program.
int main(int argc, char const *argv[])
{
	char s[100000]; // considered max size upto 1e+5;
	
	scanf("%[^\n]%*c",s); // to take string as input with spaces.
	// gets(s);        // -> this also can be used but gives warning
	
	int count = 0; // count -> character not in range of 'a' - 'z' and 'A' - 'Z';
	for(int i=0;i<strlen(s);i++)
	{
	    if(!((s[i]>='a'&&s[i]<='z')||(s[i]>='A'&&s[i]<='B'))) // condition for checking alphabet or not.
	    {
	        count++; // if they are not alphabet , then increment count;
	    }
	}
	
	fprintf(stderr,"%d\n",count); // printing on to stderr
	
    exit(0);
}
