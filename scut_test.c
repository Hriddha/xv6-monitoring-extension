#include "types.h"
#include "stat.h"
#include "user.h"
#include "syscall.h"

int main(void) {
  printf(1, "--- ADVANCED SCUT TEST ---\n");

  // 1. Check Local Count (for this process)
  int local_start = getcounts(SYS_getpid);
  getpid();
  getpid();
  int local_end = getcounts(SYS_getpid);
  
  printf(1, "Local getpid calls: %d (Expected change: 2)\n", local_end - local_start);

  // Check Global Count (System-wide)
  // We pass a negative ID to trigger the Global Mode logic in sysproc.c
  int global_start = getcounts(-SYS_getpid);
  
  printf(1, "Triggering system-wide activity...\n");
  getpid(); // One more call here
  
  int global_end = getcounts(-SYS_getpid);

  printf(1, "Global getpid calls: %d\n", global_end);
  
  //Verification
  if (local_end - local_start == 2 && global_end > local_end) {
    printf(1, ">> SUCCESS: Local and Global tracking are independent and working! <<\n");
  } else {
    printf(1, ">> FAILURE: Check your sysproc.c logic. <<\n");
  }

  exit();
}