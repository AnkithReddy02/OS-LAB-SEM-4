#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<fcntl.h>
#include<sys/types.h>
#include<signal.h>
#include<unistd.h>
#include<sys/wait.h>

void handler(int signum)
{


    if(signum==SIGPIPE)
    {
        fprintf(stderr,"\n`I've been killed because my pipe reader died!\n");
        exit(2);
    }
    if(signum==SIGTERM)
    {
        fprintf(stderr,"\nI have been killed -> convert\n");
        exit(2);
    }
}
int main(int argc,char **argv)
{
    signal(SIGTERM,handler);
    signal(SIGPIPE,handler);

    sleep(5); // sleep for 5 secs , such that count can check for valid argument.
    
    char x[BUFSIZ]; // char array of BUFSIZ.
    
    int count = 0;


    int size ; // number of characters read.

    while((size = read(0,x,BUFSIZ))>0)
    {
        for(int i=0;i<size;i++)
        {
            char s = x[i];

            // converting lower to upper and upper to lower.
            if(islower(s))
            {
               s = toupper(s);
            }
            else
            {
                s = tolower(s);
            }
            x[i] = s;

        }

        write(1,x,size); // writing into Pipe. of (size) bytes.
    }



   close(0);
   close(1);

    exit(0);

}
