#include "types.h"
#include "stat.h"
#include "user.h"

/* Q5 scaffold: confirm exact Q5 specification/API before final use. */
int
main(void)
{
  int *p = (int*)sbrk(4096);
  if(p == (int*)-1) { printf(1, "cowtest: sbrk failed\n"); exit(); }
  *p = 10;
  printf(1, "cowtest: parent before fork: %d\n", *p);
  if(fork() == 0) {
    *p = 20;
    printf(1, "cowtest: child after write: %d\n", *p);
    exit();
  }
  wait();
  printf(1, "cowtest: parent after child exit: %d\n", *p);
  sbrk(-4096);
  exit();
}
