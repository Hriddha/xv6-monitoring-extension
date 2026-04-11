#include "types.h"
#include "stat.h"
#include "user.h"
#include "syscall.h"

int main(void) {
  printf(1, "--- ADVANCED SCUT TEST ---\n");

  // 1. Local Tracking
  int local_start = getcounts(SYS_getpid);
  getpid();
  getpid();
  int local_end = getcounts(SYS_getpid);
  printf(1, "Local getpid calls: %d\n", local_end - local_start);

  // 2. Global Tracking
  int global_start = getcounts(-SYS_getpid); // The variable causing the error
  
  getpid(); 
  
  int global_end = getcounts(-SYS_getpid);

  // USE THE VARIABLE HERE TO FIX THE ERROR:
  printf(1, "Global change: %d to %d\n", global_start, global_end);
  
  if (local_end - local_start == 2 && global_end > global_start) {
    printf(1, ">> SUCCESS: Both layers working! <<\n");
  }

  exit();
}