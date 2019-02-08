// -------------------------
// ipc_compare.c
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
#include <math.h>

#include "ipc_center.h"

// get the maxi and mini value of an integer array 
int maxi (int *tArr, int nb)
{
int idx=0;
int ark;
  for(ark=1 ; ark<nb ; ark++)
    if (tArr[ark] > tArr[idx]) idx=ark;
  return idx;
}

int mini  (int *tArr, int nb)
{
int idx=0;
int ark;
  for(ark=1 ; ark<nb ; ark++)
    if (tArr[ark] < tArr[idx]) idx=ark;
  return idx;
}

// initialize two array of integers 
int *init_array (int nb)
{
int ark;
int  *a;
   srand (time(NULL) + getpid());
   a = malloc (nb * sizeof (int));
   for (ark=0 ; ark<nb ; ark++)
      a[ark] = 10 + rand()%90;
   return a;
} // init_array


// display the array
void DumpArray (const char *intro, int *p, int n)
{
int ark;
  printf ("%s: [", intro);
  for (ark=0 ; ark<n-1 ; ark++)
      printf ("%d ", p[ark]);
  printf ("%d]\n", p[ark]);
} // DumpArray


// -----------------------------------
// worker function:
// send the max (P1) or min value (P2) of the array into
// the shared memory structure S_Shm 
// wait for P0 do to the swap the swap the new value in S_Shm.M (P1) 
// or S_Shm.m (P2) with the maxi (P1) or mini (P2) value
// if P0 has trigger the finish flag, the sorting is finished
// and all values from P1 are lower than the values of P2
// -----------------------------------

int worker (int *p, int n, struct S_Shm *ptr, int semid)
{
int idx;  // get the idx since we have to put a new value at this place
struct sembuf op;
   op.sem_flg = 0;

#ifdef P1
   idx = maxi (p, n);
   ptr->Max_of_P1 = p[ idx ];
#else
  idx =  mini (p, n);
  ptr->min_of_P2 = p[ idx ];
#endif
  printf ("after changing M/m:  M is %d and m is %d\n", ptr->Max_of_P1, ptr->min_of_P2);

   // give one token to P0 (which need two)
   op.sem_num = P0_WORK;
   op.sem_op = 1;
   semop (semid, & op, 1);
   // and wait until it finish

   printf ("waiting\n");
   // take one slot from semaphore p0
   op.sem_num = P12_WORK;
   op.sem_op = -1;
   semop (semid, & op, 1);
   

   // les nombres ont ete inverses
   if ( ! ptr->finished )
   {
#ifdef P1
       p[idx] = ptr->min_of_P2;  // take the min value of P2
#else
       p[idx] = ptr->Max_of_P1;   // take the max value of P1
#endif
   } 
  return ptr->finished;
} // worker

// ---------------------------------------------------------
// main : inits shared memory, semaphoe and call worker...
//
int main (int argc, char argv[])
{
int N = 20;
int *pArr ;
int shmid, semid;
struct S_Shm *ptr;


  // init shared memeory and semaphore
  shmid = shmget (SHMKEY, SHM_SIZE, 0666 | IPC_CREAT);
  if (shmid == -1) ERROR("shared memory");
  ptr = shmat (shmid, NULL, 0);
  semid  = semget (SEMKEY, 2, 0666 | IPC_CREAT);
  if (semid == -1 ) ERROR("semaphore");

  // create the array and "sort" it using process P0
  pArr = init_array (N);   // 
  DumpArray ("before", pArr, N);

  for ( ; ! worker (pArr, N, ptr, semid) ;  );

  DumpArray ("after ", pArr, N);

  // detach memory and remove it
  shmdt (ptr) ;
  shmctl (shmid, IPC_RMID, NULL);
  // destroy semaphore
  semctl (semid, 0, IPC_RMID, 0);
  return 0;
}

