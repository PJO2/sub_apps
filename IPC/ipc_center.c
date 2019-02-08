// -------------------------
// ipc_center.c
//
// A shared memory and semaphore exercice
//
// a set of 3 pgms :
// compare1 and compare2 manage an array of N int
// compare1 send the maximum value into S_Shm.M
// compare2 send the minimum value into S_Sm.m
// center switch them if M < m
// compare1 replace the max value by S_Shm.M and
// compare2 replace the minimum value with S_Shm.m
// it ends when M>m !
//
// compile:
// gcc -D P1 ipc_compare.c -o P1 && -D P2 ipc_compare.c -o P2 && gcc ipc_center.c -o P0
// start:
// ./P1, ./P2, ./P0
// -----------------------------

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

#include "ipc_center.h"

#ifndef FALSE
#   define FALSE (0==1)
#endif

// this program just test if the shared mamory structure is sorted ptr->M < ptr->m 

int swapsort (struct S_Shm *ptr, int semid)
{
struct sembuf op;    // semaphore control strucure
     op.sem_flg = 0;   // pre fill the op structure

    // wait 2 tokens from P1 and P2
     op.sem_num = P0_WORK;
     op.sem_op = -2;
     semop (semid, & op, 1);

     printf ("Max_of_P1 is %d, min_of_P2 is %d\n", ptr->Max_of_P1, ptr->min_of_P2);
     ptr->finished = (ptr->Max_of_P1 <= ptr->min_of_P2);

     // give two tokens for P1 and P2
     op.sem_num = P12_WORK;
     op.sem_op = 2;
     semop (semid, & op, 1);

   return  ptr->finished;
} // swapsort


// main : loop until the sorting is finished

int main (int argc, char argv[])
{
int    shmid;        // shared memoty handle
int    semid;        // semaphore handle
struct S_Shm *ptr;   // pointer to shared memory


  // access to the shared memory and to the semaphore group
  shmid = shmget (SHMKEY, SHM_SIZE, 0644 | IPC_CREAT);
  if (shmid == -1) ERROR("shared memory");
  semid  = semget (SEMKEY, 2, 0666 | IPC_CREAT);
  if (semid == -1 ) ERROR("semaphore");
  ptr = shmat (shmid, NULL, 0);  // ptr points on the shared structure

  // init : there is still work to do
  ptr->finished = FALSE;

   // check if the swapping between P2 and P1 is finished
  for ( ; ! swapsort (ptr, semid)   ;  )
  {
     sleep (1);  // for the fun
  }
  sleep (10);
  // detach and remove the sahred memory
  shmdt (ptr) ;
  shmctl (shmid, IPC_RMID, NULL);
  // destroy semaphore
  semctl (semid, 0, IPC_RMID, 0);
} // main

