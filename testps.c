#include "types.h"
#include "param.h"
#include "x86.h"
#include "mmu.h"
#include "proc.h"
#include "user.h"

// State names
char *states[] = {
    "UNUSED",
    "EMBRYO",
    "SLEEPING",
    "RUNNABLE",
    "RUNNING",
    "ZOMBIE"
};

void
test_basic(void)
{
    struct pstat table[64];
    int count;

    printf(1, "\n=== TEST 1: Basic ps functionality ===\n");

    count = getprocs(table, 64);

    // Test 1: Should return positive number
    if(count <= 0) {
        printf(1, "FAILED: getprocs returned %d\n", count);
        return;
    }
    printf(1, "PASSED: getprocs returned %d processes\n", count);

    // Test 2: init process should always exist (PID 1)
    int found_init = 0;
    for(int i = 0; i < count; i++) {
        if(table[i].pid == 1) {
            found_init = 1;
            printf(1, "PASSED: Found init process\n");
            break;
        }
    }
    if(!found_init)
        printf(1, "FAILED: init process not found!\n");

    // Test 3: sh process should exist
    int found_sh = 0;
    for(int i = 0; i < count; i++) {
        if(table[i].name[0] == 's' &&
           table[i].name[1] == 'h') {
            found_sh = 1;
            printf(1, "PASSED: Found sh process\n");
            break;
        }
    }
    if(!found_sh)
        printf(1, "FAILED: sh process not found!\n");
}

void
test_state_validity(void)
{
    struct pstat table[64];
    int count, i;

    printf(1, "\n=== TEST 2: State validity check ===\n");

    count = getprocs(table, 64);

    for(i = 0; i < count; i++) {
        // State must be between 1-5 (not UNUSED=0)
        if(table[i].state < 1 || table[i].state > 5) {
            printf(1, "FAILED: Process %d has invalid state %d\n",
                table[i].pid, table[i].state);
            return;
        }
    }
    printf(1, "PASSED: All process states are valid\n");
}

void
test_memory_validity(void)
{
    struct pstat table[64];
    int count, i;

    printf(1, "\n=== TEST 3: Memory size validity ===\n");

    count = getprocs(table, 64);

    for(i = 0; i < count; i++) {
        // Memory size should be greater than 0
        if(table[i].sz == 0) {
            printf(1, "FAILED: Process %s has 0 memory\n",
                table[i].name);
            return;
        }
    }
    printf(1, "PASSED: All processes have valid memory sizes\n");
}

void
test_self_detection(void)
{
    struct pstat table[64];
    int count, i;
    int found_self = 0;

    printf(1, "\n=== TEST 4: Self detection ===\n");

    count = getprocs(table, 64);

    // This test program itself should appear in the list
    for(i = 0; i < count; i++) {
        if(table[i].name[0] == 't' &&
           table[i].name[1] == 'e' &&
           table[i].name[2] == 's' &&
           table[i].name[3] == 't') {
            found_self = 1;
            printf(1, "PASSED: testps found itself (PID %d)\n",
                table[i].pid);
            break;
        }
    }
    if(!found_self)
        printf(1, "INFO: testps not found by name (may be truncated)\n");
}

void
test_display(void)
{
    struct pstat table[64];
    int count, i;

    printf(1, "\n=== TEST 5: Full display output ===\n");
    printf(1, "PID\tSTATE\t\tSIZE\t\tNAME\n");
    printf(1, "---\t-----\t\t----\t\t----\n");

    count = getprocs(table, 64);

    for(i = 0; i < count; i++) {
        printf(1, "%d\t%s\t\t%d\t\t%s\n",
            table[i].pid,
            states[table[i].state],
            table[i].sz,
            table[i].name);
    }
}

int
main(void)
{
    printf(1, "=============================\n");
    printf(1, "  Process Monitor Test Suite  \n");
    printf(1, "=============================\n");

    test_basic();
    test_state_validity();
    test_memory_validity();
    test_self_detection();
    test_display();

    printf(1, "\n=== All tests completed ===\n");

    exit();
}