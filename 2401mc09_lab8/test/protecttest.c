#include "types.h"
#include "stat.h"
#include "user.h"

/* Q6 scaffold: exact protection API and expected fault behavior were not supplied. */
int
main(void)
{
  int value = 7;
  printf(1, "protecttest scaffold: address=%x value=%d\n", (uint)&value, value);
  printf(1, "Complete this test using the protection interface specified in Q6.\n");
  exit();
}
