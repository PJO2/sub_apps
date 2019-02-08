// -------------------------
// ipc_center.h
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
// -----------------------------

#define SHMKEY 786543
#define SEMKEY 234567890

#define P0_WORK  0
#define P12_WORK  1

// structure shared
struct S_Shm
{
   int Max_of_P1;
   int min_of_P2;
   int finished;
};

#define SHM_SIZE (sizeof (struct S_Shm))

#define ERROR(x) { printf(x); exit (-1); }
