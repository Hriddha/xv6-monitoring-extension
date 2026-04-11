#include "types.h"
#include "stat.h"
#include "user.h"
#include "syscall.h" // for Sys.getpid

int main(void){

    print(1, "System Call Usage Tracker Test Initialized");

    //Check current count for getpid
    int start = getcounts(SYS_getpid);
    printf(1, "Initial getpid calls: %d\n", start);

    printf(1, "Triggering getpid 4 times...\n");
    getpid();
    getpid();
    getpid();
    getpid();

    int end = getcounts(SYS_getpid);
    printf(1, "Final getpid calls: %d\n", end);

  
    if (end - start == 4) {
        printf(1, "SUCCESS: Tracker accurately recorded 4 calls.\n");
    } else {
        printf(1, "FAILURE: Tracker count mismatch.\n");
    }

    exit();


}