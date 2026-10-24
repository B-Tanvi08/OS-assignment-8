#include "types.h"
#include "stat.h"
#include "user.h"

int global_value = 111;

/* Q1: test global, local, malloc block, invalid address, and fork mappings. */
static void
show_mapping(char *label, int va)
{
  printf(1, "%s: VA=%x PA=%x\n", label, va, va2pa(va));
}

int
main(void)
{
  int local_value = 222;
  char *heap_value;

  heap_value = (char*)malloc(64);
  if(heap_value == 0) {
    printf(1, "vatest: malloc failed\n");
    exit();
  }
  heap_value[0] = 'X';

  show_mapping("global", (int)&global_value);
  show_mapping("local", (int)&local_value);
  show_mapping("malloc block", (int)heap_value);
  show_mapping("invalid 0x7fffffff", 0x7fffffff);

  if(fork() == 0) {
    printf(1, "child mappings (same VAs; copied pages may have different PAs):\n");
    show_mapping("child global", (int)&global_value);
    show_mapping("child local", (int)&local_value);
    show_mapping("child malloc block", (int)heap_value);
    exit();
  }
  wait();
  free(heap_value);
  exit();
}
