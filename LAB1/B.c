#include<stdio.h> // standard input output
#include<string.h> // for string operations.(strlen(s) -> to get the string length)
#include<ctype.h> // for using isalpha(although not necessary to use).
#include<stdlib.h> // used to exit (in this program) program.

int main(int argc, char const *argv[])
{
	char s[100000]; // considered max size upto 1e+5;
	
	scanf("%[^\n]%*c",s); // to take string as input with spaces.
	// gets(s);        // -> this also can be used but gives warning
	
	int count = 0; // count -> character not in range of 'a' - 'z' and 'A' - 'Z';
	
	// strlen(s) -> returns string length of s.
	
	for(int i=0;i<strlen(s);i++)
	{
	    if(!((s[i]>='a'&&s[i]<='z')||(s[i]>='A'&&s[i]<='B'))) // condition for checking alphabet or not.
	    {
	        count++; // if they are not alphabet , then increment count;
	    }
	    
	    /*
	    
	    // isalpha(x) returns 1 if x is uppercase character ,
	    // returns 2 if x is lowercase , returns 0 if x is not alphabet 
	    // this method also can be done.
	    
	    if(isalpha(s[i])==0)
	    {
	        count++;
	    }
	    
	    */
	}
	
	fprintf(stderr,"%d\n",count); // printing on to stderr
	
    exit(0);
}
