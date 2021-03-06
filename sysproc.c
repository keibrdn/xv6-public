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
  int *status;
 argptr(0, (char **) &status, sizeof(int*));
  return wait(status);
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

int
sys_exitStatus(void)
{
int status;

if(argint(0, &status) < 0){
    exitStatus(0);
}
exitStatus(status);
return 0;
}

int
sys_waitpid(void)
{
 int pid, options;
 int *status;

argint(0, &pid);
argptr(1, (char **) &status, sizeof(int*));
argint(2, &options);


 return waitpid(pid, status, options);
   

}

int
sys_setpriority(void) {
  int priority_level;
  int prev_priority;

  prev_priority = myproc()->priority;
  argint(0, &priority_level);

  if(priority_level > 31 || priority_level < 0) {
   return -1;
 }
     myproc()->priority = priority_level; 
 return prev_priority;
 }

