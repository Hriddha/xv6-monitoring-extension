#include "types.h"
#include "param.h"      
#include "x86.h"         
#include "mmu.h"        
#include "proc.h"
#include "user.h"
// State names for display
char *states[] = {
    "UNUSED  ",
    "EMBRYO  ",
    "SLEEPING",
    "RUNNABLE",
    "RUNNING ",
    "ZOMBIE  "
};

int
main(void)
{
    struct pstat table[64];  // Array for up to 64 processes
    int count, i;

    count = getprocs(table, 64);

    if(count < 0) {
        printf(2, "ps: error getting process info\n");
        exit();
    }

    // Print header
    printf(1, "PID\tSTATE\t\tSIZE\tNAME\n");
    printf(1, "---\t-----\t\t----\t----\n");

    // Print each process
    for(i = 0; i < count; i++) {
        printf(1, "%d\t%s\t%d\t%s\n",
            table[i].pid,
            states[table[i].state],
            table[i].sz,
            table[i].name);
    }

    exit();
}