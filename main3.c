#include <stdlib.h>
#include <stdio.h>

long int random(void);

void srandom(unsigned int seed);

#define MAX_ITERATIONS 30
void  ChildProcess(void);                /* child process prototype  */
void  ParentProcess(void);       


void  main(void)
{

     srandom(time(NULL)); 
     pid_t  pid1, pid2;
     int status;

     pid1 = fork();
     if (pid1 == 0) {
          ChildProcess(); 
          exit(0);
     }
     pid2 = fork();
     if (pid2 == 0) {
          ChildProcess(); 
          exit(0);
     }

    
    ParentProcess();

    pid_t finished_pid1 = wait(&status);
    printf("Child Pid: %d has completed\n", finished_pid1);

    pid_t finished_pid2 = wait(&status);
    printf("Child Pid: %d has completed\n", finished_pid2);
    
    printf("*** Parent process is done waiting for both children ***\n");

}

void  ChildProcess(void)
{
     int   i;
     int iterations = random() % MAX_ITERATIONS;
     pid_t pid, parent_pid; 

    
     pid = getpid();
     parent_pid = getppid();
     for (i = 0; i <= iterations; i++) {
          printf("Child pid: %d is going to sleep!\n", pid);
          sleep(random() % 10);
          printf("   Child Pid: %d is awake! Where is my Parent: %d?\n", pid, parent_pid);
     } 
}

void  ParentProcess(void)
{
    printf("*** Parent process is waiting for both children ***\n");
    wait(NULL); /* Wait for the first child to finish */
    wait(NULL); /* Wait for the second child to finish */
}
