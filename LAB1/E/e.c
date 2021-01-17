
/*

1) If no arguments it will take input for 30 secs and then exit.
2) If only one argument , then based on whether it is -n or inputfile , if it is -n then input will  be asked from user and output will be wrtten to the stdout.
  if it is inputfile , then it will take take input from file and output to stdout.
 3) if 2 arguments are there , it can be (-n,inputfile),(inputfile,outputfile) -> in case of 1st one output is on stdout and in case 
  of 2nd takes input from input file and writes into output file after converting adn frprintf of number of non-alpha.
  4) if 3 arguments , then (-n , inputfile ,outputfile) then it will read atmost n characters and write atmost n characters from pipe and to stdout.
  
-> for all valid -n are checked.(based on that exited with 2).
argc2,argc3,argc4 are functions.
argc2 -> is used for handling only 1 argument extra (other than ./programname);
argc3-> is used for handling only 2 arguments extras.
argc4-> is used for handling only 3 arguments extras.

->in case of zero arguments extra then it is handled in main function itself.


*/

#include<stdio.h> // stdin,stdout.
#include<stdlib.h> // exit
#include<fcntl.h> // for files.
#include<sys/types.h>
#include<unistd.h>
#include<sys/stat.h>
#include<setjmp.h>
#include<signal.h>
#include<sys/wait.h> // for wait.
#include<ctype.h>
#include<time.h>
jmp_buf env;

void handler(int signum)
{
    fprintf(stderr,"\nread timeout in second child, killing both children\n");
    longjmp(env,1);
    exit(1);

}
void argc2(int argc,char **argv)
{
    int fd_open = -1;

    int fd_pipes[2];

    if(pipe(fd_pipes)<0)
    {
        fprintf(stderr,"\nUnable to create pipe,exiting..\n");
            exit(1);
    }


    if(argv[1][0]!='-')
    {
         fd_open = open(argv[1],O_RDONLY);
         if(fd_open<0)
         {
            fprintf(stderr,"\nUnable to open the file,exiting..\n");
            exit(1);
         }

         close(0);
         dup(fd_open);
         close(fd_open);
    }



    int child1pid,child2pid;

    signal(SIGALRM, handler);//alarm register

    if(setjmp(env))
    {
      // fprintf(stderr,"Jumped\n");
        kill(child1pid,SIGTERM); // kill 1st child;
        kill(child2pid,SIGTERM); // kill 2nd child;

        int pid,status;
        while ((pid = wait(&status)) > 0)
        {
             fprintf(stderr, "child pid=%d reaped with exit status=%d\n", pid, WEXITSTATUS(status));
             /* if pid is count's and exit status == 2, kill convert ... */
        }
        exit(1);
    }



    int m,n;



    if( m = fork())
    {
        if(m==-1)
        {
            fprintf(stderr,"\nfork is Unsucessful\n");
            exit(1);
        }
        if( n = fork() )
        {
            // PARENT
            if(n==-1)
            {
               fprintf(stderr,"\nfork is Unsucessful\n");
               exit(1);
            }
            close(fd_pipes[0]); // close read pipe
            close(fd_pipes[1]); // close write pipe.
            close(0); // close stdin.
            close(1); // close stdout.

            int status;

            alarm(15); // alarm for 15 secs approx.

            int pid;

            int exitstatus=0;
            while ((pid = wait(&status)) > 0)
            {
                 fprintf(stderr,"\nchild pid=%d reaped with exit status=%d\n", pid, WEXITSTATUS(status));
                 /* if pid is count's and exit status == 2, kill convert ... */

                 if(pid==child1pid&& WEXITSTATUS(status)==2)
                 {
                     if(kill(child2pid,SIGTERM)==-1)
                     {
                         fprintf(stderr,"\nSecond child already died.\n");
                     }

                 }
                 if(WEXITSTATUS(status)>0)
                 {
                     exitstatus = WEXITSTATUS(status);
                 }
             }

             alarm(0);

             if(exitstatus)
             {
                 fprintf(stderr,"\nAbnormal Children exit\n");
                 exit(exitstatus);
             }

             fprintf(stderr,"\nNormal Children Exit\n");

            exit(0) ; // program finished.
        }
        else
        {
            // CHILD-2
            child2pid = getpid();

            close(1); // close stdout.
            dup(fd_pipes[1]); // pipe write dup.
            close(fd_pipes[0]); // pipe read close.
            close(fd_pipes[1]); // pipe write close.

            fprintf(stderr,"\nConvert process id : %d\n",child2pid); // printing child2 process id;

            execl("q5convert","q5convert",NULL);

        }
    }
    else
    {
            // CHILD - 1.
            child1pid = getpid();

            close(0); // close stdin
            dup(fd_pipes[0]); // dup pipe read;
            close(fd_pipes[1]); // close wite pipe.
            close(fd_pipes[0]); // close read pipe.

            fprintf(stderr,"\nCount process id : %d\n",child1pid); // printing child1pid process id.

            if(fd_open>=0)
            {
                execl("q5count","q5count",NULL);
            }
            else
            {
                execl("q5count","q5count",argv[1],NULL);
            }
    }
}
void argc3(int argc,char **argv)
{
    int fd_open = -1,fd_create;

    int fd_pipes[2];

    if(pipe(fd_pipes)<0)
    {
        fprintf(stderr,"\nUnable to create pipe,exiting..\n");
            exit(1);
    }

    int bothfiles = 0; // 0 if both arguments are not files. else 1.


    if(argv[1][0]!='-')
    {
         fd_open = open(argv[1],O_RDONLY);

         if(fd_open<0)
         {
            fprintf(stderr,"\nUnable to open the file,exiting..\n");
            exit(1);
         }
         fd_create = creat(argv[2],O_WRONLY);
         if(fd_create<0)
         {
            fprintf(stderr,"\nUnable to create the file,exiting..\n");
            exit(1);
         }
         close(0);
         dup(fd_open);
         close(fd_open);

         close(1);
         dup(fd_create);
         close(fd_create);

         bothfiles = 1;
    }
    else
    {
        fd_open = open(argv[2],O_RDONLY);

         if(fd_open<0)
         {
            fprintf(stderr,"\nUnable to open the file,exiting..\n");
            exit(1);
         }

         close(0);
         dup(fd_open);
         close(fd_open);


    }



    int child1pid,child2pid;

    signal(SIGALRM, handler);//alarm register

    if(setjmp(env))
    {
           // fprintf(stderr,"\nJumped\n");
        kill(child1pid,SIGTERM); // kill 1st child;
        kill(child2pid,SIGTERM); // kill 2nd child;

        int pid,status;
        while ((pid = wait(&status)) > 0)
        {
             fprintf(stderr, "child pid=%d reaped with exit status=%d\n", pid, WEXITSTATUS(status));
             /* if pid is count's and exit status == 2, kill convert ... */
        }
        exit(1);
    }



    int m,n;



    if( m = fork())
    {
        if(m==-1)
        {
            fprintf(stderr,"\nfork is Unsucessful\n");
            exit(1);
        }
        if( n = fork() )
        {
            // PARENT
            if(n==-1)
            {
               fprintf(stderr,"\nfork is Unsucessful\n");
               exit(1);
            }
            close(fd_pipes[0]); // close read pipe
            close(fd_pipes[1]); // close write pipe.
            close(0); // close stdin.
            close(1); // close stdout.

            int status;

            alarm(15); // alarm for 15 secs approx.

            int pid;

            int exitstatus=0;
            while ((pid = wait(&status)) > 0)
            {
                 fprintf(stderr, "child pid=%d reaped with exit status=%d\n", pid, WEXITSTATUS(status));
                 /* if pid is count's and exit status == 2, kill convert ... */

                 if(pid==child1pid&& WEXITSTATUS(status)==2)
                 {
                     if(kill(child2pid,SIGTERM)==-1)
                     {
                         fprintf(stderr,"\nSecond child already died.\n");
                     }

                 }
                 if(WEXITSTATUS(status)>0)
                 {
                     exitstatus = WEXITSTATUS(status);
                 }
             }

             alarm(0);
            // fprintf(stderr,"Exit : %d\n",exitstatus);
             if(exitstatus)
             {
                 fprintf(stderr,"\nAbnormal Children exit\n");
                 exit(exitstatus);
             }

             fprintf(stderr,"\nNormal Children Exit\n");

            exit(0) ; // program finished.
        }
        else
        {
            // CHILD-2
            child2pid = getpid();

            close(1); // close stdout.
            dup(fd_pipes[1]); // pipe write dup.
            close(fd_pipes[0]); // pipe read close.
            close(fd_pipes[1]); // pipe write close.

            fprintf(stderr,"\nConvert process id : %d\n",child2pid); // printing child2 process id;


            execl("q5convert","q5convert",NULL);


        }
    }
    else
    {
        // CHILD - 1.
            child1pid = getpid();

            close(0); // close stdin
            dup(fd_pipes[0]); // dup pipe read;
            close(fd_pipes[1]); // close wite pipe.
            close(fd_pipes[0]); // close read pipe.

            fprintf(stderr,"\nCount process id : %d\n",child1pid); // printing child1pid process id.

            if(bothfiles)
            {
                execl("q5count","q5count",NULL);
            }
            else
            {
                execl("q5count","q5count",argv[1],NULL);
            }
    }
}
void argc4(int argc,char **argv)
{
    int pid;
    int fd_in = open(argv[2],O_RDONLY); // read only mode.

    if(fd_in < 0) // checking for valid file access.
    {
        fprintf(stderr,"\nUnable to access the file..\n");
        exit(1);
    }

    close(0); // closing stdin;

    if(dup(fd_in)<0) // creating duplicate of file and keeping in near index (i.e : 0th index). and checking for validity.
    {
        fprintf(stderr,"\nUnable to create duplicate of  the file..\n");
        exit(1);
    }
    close(fd_in); // closing the actually file index.

    int fd_out = creat(argv[3],O_WRONLY); // creating file in writing mode only.

    if(fd_out < 0)// checking for file creation successful or not.
    {
        fprintf(stderr,"\nUnable to create the file..\n");
        exit(1);
    }

    close(1); // closing stdout.
    if(dup(fd_out)<0) // creating duplicate of file and keeping in near index (i.e : 1st index);
    {
        fprintf(stderr,"\nUnable to create duplicate of  the file..\n");
        exit(1);
    }
    close(fd_out); // closing the actual file index.


    int fd_pipes[2]; // 0th index-> pipe read , 1st index-> pipe write.

    if(pipe(fd_pipes)<0) // creating pipe file descriptors.
    {
        fprintf(stderr,"\nUnsucessful creation of pipe.\n");
        exit(1);
    }
/*.......................................................................................................*/


    int child1pid,child2pid;

    signal(SIGALRM, handler);//alarm register

    if(setjmp(env))
    {
        kill(child1pid,SIGTERM); // kill 1st child;
        kill(child2pid,SIGTERM); // kill 2nd child;

        int pid,status;
        while ((pid = wait(&status)) > 0)
        {
             fprintf(stderr, "child pid=%d reaped with exit status=%d\n", pid, WEXITSTATUS(status));
             /* if pid is count's and exit status == 2, kill convert ... */
        }
        exit(1);
    }



    int m,n;



    if( m = fork())
    {
        if(m==-1)
        {
            fprintf(stderr,"\nfork is Unsucessful\n");
            exit(1);
        }
        if( n = fork() )
        {
            // PARENT
            if(n==-1)
            {
               fprintf(stderr,"\nfork is Unsucessful\n");
               exit(1);
            }
            close(fd_pipes[0]); // close read pipe
            close(fd_pipes[1]); // close write pipe.
            close(0); // close stdin.
            close(1); // close stdout.

            int status;

            alarm(15); // alarm for 15 secs approx.

            int exitstatus=0;
            while ((pid = wait(&status)) > 0)
            {
                 fprintf(stderr, "child pid=%d reaped with exit status=%d\n", pid, WEXITSTATUS(status));
                 /* if pid is count's and exit status == 2, kill convert ... */

                 if(pid==child1pid&& WEXITSTATUS(status)==2)
                 {
                     if(kill(child2pid,SIGTERM)==-1)
                     {
                         fprintf(stderr,"\nSecond child already died.\n");
                     }

                 }
                 if(WEXITSTATUS(status)>0)
                 {
                     exitstatus = WEXITSTATUS(status);
                 }
             }

             alarm(0);

             if(exitstatus)
             {
                 fprintf(stderr,"\nAbnormal Children exit\n");
                 exit(exitstatus);
             }

             fprintf(stderr,"\nNormal Children Exit\n");


            exit(0) ; // program finished.
        }
        else
        {
            // CHILD-2
            child2pid = getpid();

            close(1); // close stdout.
            dup(fd_pipes[1]); // pipe write dup.
            close(fd_pipes[0]); // pipe read close.
            close(fd_pipes[1]); // pipe write close.

            fprintf(stderr,"\nConvert process id : %d\n",child2pid); // printing child2 process id;

            execl("q5convert","q5convert",NULL);

        }
    }
    else
    {
            // CHILD - 1.
            child1pid = getpid();

            close(0); // close stdin
            dup(fd_pipes[0]); // dup pipe read;
            close(fd_pipes[1]); // close wite pipe.
            close(fd_pipes[0]); // close read pipe.

            fprintf(stderr,"\nCount process id : %d\n",child1pid); // printing child1pid process id.

            execl("q5count","q5count",argv[1],NULL);
    }
}
int main(int argc,char **argv)
{

    if(argc==1)
    {
            char s[100000];
          clock_t start = clock();
          int i=0;
          printf("You can type something until 30secs.\n");
          while ( (clock() - start)/CLOCKS_PER_SEC <= 30)
          {
                  scanf("%c",&s[i++]);

          }
          s[i]='\0';
          printf("Entered string : %s\n",s);
         exit(0);
    }
    else if(argc==2)
    {
        argc2(argc,argv);
    }
    else if(argc==3)
    {
       argc3(argc,argv);
    }
    else
    {
        argc4(argc,argv);
    }

    exit(0);

}
