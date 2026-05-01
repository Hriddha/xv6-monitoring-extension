#include "types.h"
#include "param.h"
#include "x86.h"
#include "mmu.h"
#include "proc.h"
#include "user.h"

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
    struct pstat table[64];
    int count, i;

    count = getprocs(table, 64);

    if(count < 0){
        printf(2, "ps: error getting process info\n");
        exit();
    }

    // Header — use tabs, xv6 printf has no padding support
    printf(1, "PID\tSTATE\t\tSIZE\t\tPRI\tWAIT\tNAME\n");
    printf(1, "---\t-----\t\t----\t\t---\t----\t----\n");

    for(i = 0; i < count; i++){
        printf(1, "%d\t%s\t%d\t\t%d\t%d\t%s\n",
            table[i].pid,
            states[table[i].state],
            table[i].sz,
            table[i].priority,
            table[i].wait_ticks,
            table[i].name);
    }

    exit();
}