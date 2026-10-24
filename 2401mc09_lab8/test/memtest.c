#include "types.h"
#include "stat.h"
#include "user.h"
#include "meminfo.h"

static void
show(char *label)
{
  struct meminfo m;
  if(getmeminfo(&m) < 0) {
    printf(1, "memtest: getmeminfo failed\n");
    return;
  }
  printf(1, "%s: total_pages=%d free_pages=%d user_pages=%d page_table_pages=%d\n",
         label, m.total_pages, m.free_pages, m.user_pages, m.page_table_pages);
}

int
main(void)
{
  char *p;
  show("before allocation");

  p = sbrk(3 * 4096);
  if(p == (char*)-1) {
    printf(1, "memtest: sbrk failed\n");
    exit();
  }
  /* Touch one byte per page so the pages are actually backed by frames. */
  p[0] = 1;
  p[4096] = 2;
  p[8192] = 3;
  show("after allocation and touches");

  if(fork() == 0) {
    show("child after fork");
    exit();
  }
  wait();
  show("after child reaped");

  if(sbrk(-3 * 4096) == (char*)-1)
    printf(1, "memtest: shrink failed\n");
  show("after shrink");
  exit();
}
