#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<fcntl.h>
#include<sys/types.h>
#include<unistd.h>
#include<signal.h>
#include<sys/wait.h>

void handler(int signum)
{
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
    
    
    int n = 1;// intialising positive number as it is required in while loop when there are no arguments.
    int noArgument = 1; // assuminng -n argument is present.

    // check valid -n argument. exit(2);
    
    
    
    if(argc>1)
    {
        if((atoi)(argv[1]))
        {
            n = abs((atoi)(argv[1]));
        }
        else
        {
            fprintf(stderr,"\nInvalid argument(which must be of form -n)\n");
            exit(2);
        }
    }
    else
    {
        noArgument = 0; // represents there is no -n argument.
    }
   
    char x;
    int count = 0; // count is number of non-alpha characters.
   
    while(n>0&&read(0,&x,1)>0)
    {
       
        write(1,&x,1); // writing into output file.
        if(!isalpha(x))
        {
            count++;
        }
        
        if(noArgument)
        {
            n--;
        }
        

    }

    close(0);
    close(1);

    fprintf(stderr,"\nNumber of non-alpha characters : %d\n",count);

    exit(0);

}
