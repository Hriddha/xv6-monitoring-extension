#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  if(argc != 3){
    printf(2, "Usage: setpri <pid> <priority>\n");
    printf(2, "  priority range: 0 (highest) to 20 (lowest)\n");
    exit();
  }

  int pid      = atoi(argv[1]);
  int priority = atoi(argv[2]);

  if(setpriority(pid, priority) < 0){
    printf(2, "setpri: failed — invalid pid or priority out of range\n");
    exit();
  }

  printf(1, "setpri: pid %d priority set to %d\n", pid, priority);
  exit();
}