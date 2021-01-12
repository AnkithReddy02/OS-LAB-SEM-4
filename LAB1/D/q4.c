#include<stdio.h> // stdin,stdout.
#include<stdlib.h> // exit
#include<fcntl.h> // for files.
#include<sys/types.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/wait.h> // for wait.

int main(int argc,char **argv)
{
    if(argc<=2)
    {
        fprintf(stderr,"Arguments are not sufficient.\n");
        exit(1);
    }

    int fd_in = open(argv[1],O_RDONLY); // read only mode.

    if(fd_in < 0) // checking for valid file access.
    {
        fprintf(stderr,"Unable to access the file..\n");
        exit(1);
    }

    close(0); // closing stdin;
    
    if(dup(fd_in)<0) // creating duplicate of file and keeping in near index (i.e : 0th index). and checking for validity.
    {
        fprintf(stderr,"Unable to create duplicate of  the file..\n");
        exit(1);
    }
    close(fd_in); // closing the actually file index.

    int fd_out = creat(argv[2],O_WRONLY); // creating file in writing mode only.

    if(fd_out < 0)// checking for file creation successful or not.
    {
        fprintf(stderr,"Unable to create the file..\n");
        exit(1);
    }

    close(1); // closing stdout.
    if(dup(fd_out)<0) // creating duplicate of file and keeping in near index (i.e : 1st index);
    {
        fprintf(stderr,"Unable to create duplicate of  the file..\n");
        exit(1);
    }
    close(fd_out); // closing the actual file index.


    int fd_pipes[2]; // 0th index-> pipe read , 1st index-> pipe write.

    if(pipe(fd_pipes)<0) // creating pipe file descriptors.
    {
        fprintf(stderr,"Unsucessful creation of pipe.\n");
        exit(1);
    }
    
    int m,n;

    if( m = fork())
    {
        if(m==-1)
        {
            fprintf(stderr,"fork is Unsucessful\n");
            exit(1);
        }
        if( n = fork() )
        {
            if(n==-1)
            {
               fprintf(stderr,"fork is Unsucessful\n");
               exit(1); 
            }
            close(fd_pipes[0]); // close read pipe 
            close(fd_pipes[1]); // close write pipe.
            close(0); // close stdin.
            close(1); // close stdout.
            
            int status;

            while(wait(&status)>0); // waits for all childrens to get finished.
            
            exit(0) ; // program finished.
        }
        else
        {
            close(1); // close stdout.
            dup(fd_pipes[1]); // pipe write dup.
            close(fd_pipes[0]); // pipe read close.
            close(fd_pipes[1]); // pipe write close.

            execl("convert","convert",NULL);

        }
    }
    else
    {
            close(0); // close stdin
            dup(fd_pipes[0]); // dup pipe read;
            close(fd_pipes[1]); // close wite pipe.
            close(fd_pipes[0]); // close read pipe.

            execl("count","count",NULL);
    }






}
