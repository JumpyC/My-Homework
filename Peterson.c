#include  <stdio.h>
#include  <stdlib.h>
#include  <sys/types.h>
#include  <sys/ipc.h>
#include  <sys/shm.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
int flag[2];
int turn;
int j;
void lock(int self)
{
    flag[self] = 1;
    turn = 1 - self;
    while(flag[turn] && turn == 1 - self);
}
void unlock(int self)
{
    flag[self] = 0;
}
int main()
{
    int shmid;
    int* shm;
    shmid = shmget(IPC_PRIVATE ,sizeof(int),IPC_CREAT | 0666);
    shm = (int*)shmat(shmid,NULL,0);
    *shm = 0;
    pid_t pid = fork();
    if(pid == 0)
    {
        lock(0);
        (*shm)++;
        unlock(0);
    }
    else
    {
        lock(1);
        (*shm)--;
        unlock(1);
    }
    wait(0);
    printf("pid : %d shm = %d\n",getpid(),*shm);
    shmdt(shm);
}
