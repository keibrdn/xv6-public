// Test that fork fails gracefully.
// Tiny executable so that the limit can be filling the proc table.

#include "types.h"
#include "stat.h"
#include "user.h"

#define N  1000

void
printf(int fd, const char *s, ...)
{
  write(fd, s, strlen(s));
}

void
forktest(void)
{
  int n, pid;

  printf(1, "fork test\n");

  for(n=0; n<N; n++){
    pid = fork();
    if(pid < 0)
      break;
    if(pid == 0)
	exitStatus(1);
      exit();
  }

  if(n == N){
    printf(1, "fork claimed to work N times!\n", N);
exitStatus(1);    
exit();
  }

  for(; n > 0; n--){
    if(wait(&pid) < 0){
      printf(1, "wait stopped early\n");
exitStatus(1);   
   exit();
    }
  }

  if(wait(&pid) != -1){
    printf(1, "wait got too many\n");
exitStatus(1);   
 exit();
  }

  printf(1, "fork test OK\n");
}

int
main(void)
{
  forktest();
exitStatus(1); 
 exit();
return 0;
}
