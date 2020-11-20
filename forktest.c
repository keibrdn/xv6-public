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
  int n, pid,status;

  printf(1, "fork test\n");

  for(n=0; n<N; n++){
    pid = fork();
    if(pid < 0)
      break;
    if(pid == 0){
      exitS(1);
      exit();
    }
  }

  if(n == N){
    printf(1, "fork claimed to work N times!\n", N);
    exitS(1);
    exit();
  }

for(; n > 0; n--){
    if(wait(&status) < 0){
      printf(1, "wait stopped early\n");
      exitS(1);
      exit();
    }
  }
if(wait(&status) != -1){
    printf(1, "wait got too many\n");
    exitS(1);
    exit();
  }

  printf(1, "fork test OK\n");
}

int
main(void)
{
  forktest();
  exitS(1);
  exit();
}
