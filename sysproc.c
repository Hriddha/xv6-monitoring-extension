#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;
  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;
  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

extern struct spinlock scutlock;
extern int global_counts[30];

int
sys_getcounts(void)
{
  int sys_id;

  if(argint(0, &sys_id) < 0)
    return -1;

  if(sys_id < 0){
    int positive_id = -sys_id;
    if(positive_id >= 30) return -1;
    int val;
    acquire(&scutlock);
    val = global_counts[positive_id];
    release(&scutlock);
    return val;
  }

  if(sys_id >= 30) return -1;
  return myproc()->syscall_counts[sys_id];
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;
  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

int
sys_uptime(void)
{
  uint xticks;
  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

int getprocs(struct pstat *table, int max);

int
sys_getprocs(void)
{
  struct pstat *table;
  int max;

  // Fetch max first so we can use it in argptr
  if(argint(1, &max) < 0)
    return -1;
  if(argptr(0, (void*)&table, sizeof(struct pstat) * max) < 0)
    return -1;

  return getprocs(table, max);
}

int
sys_setpriority(void)
{
  int pid, priority;

  if(argint(0, &pid) < 0 || argint(1, &priority) < 0)
    return -1;

  if(priority < 0 || priority > 20)
    return -1;

  return setpriority(pid, priority);   // calls proc.c function, no ptable access here
}