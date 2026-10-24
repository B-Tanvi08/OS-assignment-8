#ifndef XV6_MEMINFO_H
#define XV6_MEMINFO_H
#include "types.h"
struct meminfo {
  uint total_pages;
  uint free_pages;
  uint user_pages;
  uint page_table_pages;
};
#endif
