#include "types.h"
#include "stat.h"
#include "user.h"
#include "meminfo.h"

#define BIG (32 * 1024 * 1024)

static void
showmem(char *label)
{
  struct meminfo m;
  if(getmeminfo(&m) < 0) {
    printf(1, "%s: getmeminfo failed\n", label);
    return;
  }
  printf(1, "%s: total=%d free=%d user=%d page_tables=%d\n",
         label, m.total_pages, m.free_pages,
         m.user_pages, m.page_table_pages);
}

int
main(void)
{
  char *p;
  int i;

  showmem("before reservation");
  p = sbrk(BIG);
  if(p == (char*)-1) {
    printf(1, "lazytest: large sbrk failed\n");
    exit();
  }
  showmem("after reservation, before touches");

  /* Touch only eight widely spaced pages in the reserved 32 MB range. */
  for(i = 0; i < BIG; i += 4 * 1024 * 1024)
    p[i] = (char)i;
  showmem("after sparse touches");

  /* Fork/exit should tolerate holes in the lazy heap. */
  if(fork() == 0) {
    printf(1, "lazytest child: fork with sparse heap succeeded\n");
    exit();
  }
  wait();
  showmem("after child reaped");

  if(sbrk(-BIG) == (char*)-1)
    printf(1, "lazytest: shrink failed\n");
  showmem("after shrink");
  exit();
}
