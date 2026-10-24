#include "types.h"
#include "stat.h"
#include "user.h"

/* Q3 requires calls at startup, after +8 pages, and after shrinking. */
int
main(void)
{
  printf(1, "vmprinttest: startup page table\n");
  vmprint();

  if(sbrk(8 * 4096) == (char*)-1) {
    printf(1, "vmprinttest: heap growth failed\n");
    exit();
  }
  printf(1, "vmprinttest: after sbrk(8 * 4096)\n");
  vmprint();

  if(sbrk(-8 * 4096) == (char*)-1)
    printf(1, "vmprinttest: heap shrink failed\n");
  printf(1, "vmprinttest: after sbrk(-8 * 4096)\n");
  vmprint();
  exit();
}
