#include "types.h"
#include "stat.h"
#include "user.h"

// Burn CPU cycles to simulate work
// Larger n = more work = takes longer
void
busywork(volatile int n)
{
    volatile int i;
    for(i = 0; i < n; i++)
        ;
}

int
main(void)
{
    int pid1, pid2, pid3;

    printf(1, "\n=== Priority Scheduling + Aging Test ===\n\n");

    // --- Fork Child 1: HIGH priority (2) ---
    pid1 = fork();
    if(pid1 == 0){
        int me = getpid();
        if(setpriority(me, 2) < 0){
            printf(2, "setpriority failed for child 1\n");
            exit();
        }
        printf(1, "[HIGH ] PID=%d priority=2  -- started\n", me);
        busywork(500000000);
        printf(1, "[HIGH ] PID=%d priority=2  -- DONE\n", me);
        exit();
    }

    // --- Fork Child 2: LOW priority (18) ---
    pid2 = fork();
    if(pid2 == 0){
        int me = getpid();
        if(setpriority(me, 18) < 0){
            printf(2, "setpriority failed for child 2\n");
            exit();
        }
        printf(1, "[LOW  ] PID=%d priority=18 -- started\n", me);
        busywork(500000000);
        printf(1, "[LOW  ] PID=%d priority=18 -- DONE\n", me);
        exit();
    }

    // --- Fork Child 3: MEDIUM priority (10) ---
    pid3 = fork();
    if(pid3 == 0){
        int me = getpid();
        if(setpriority(me, 10) < 0){
            printf(2, "setpriority failed for child 3\n");
            exit();
        }
        printf(1, "[MED  ] PID=%d priority=10 -- started\n", me);
        busywork(500000000);
        printf(1, "[MED  ] PID=%d priority=10 -- DONE\n", me);
        exit();
    }

    // Parent: print summary then wait
    printf(1, "\nChildren forked:\n");
    printf(1, "  PID %d -> priority 2  (HIGH)\n", pid1);
    printf(1, "  PID %d -> priority 18 (LOW)\n",  pid2);
    printf(1, "  PID %d -> priority 10 (MED)\n",  pid3);
   

    // Wait for all 3 children
    int finished;
    int order = 1;
    while((finished = wait()) != -1){
        if(finished == pid1)
            printf(1, "  [%d] HIGH (pid=%d) finished\n", order++, finished);
        else if(finished == pid2)
            printf(1, "  [%d] LOW  (pid=%d) finished\n", order++, finished);
        else if(finished == pid3)
            printf(1, "  [%d] MED  (pid=%d) finished\n", order++, finished);
        else
            printf(1, "  [%d] unknown pid=%d finished\n", order++, finished);
    }

    printf(1, "\n=== Test complete ===\n");
   
    exit();
}