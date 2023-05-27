#include <stdio.h>
#include <xxx.h>

int main(int argc, char **argv) {
  struct xxx_t *xxx = xxx_init(argc, argv);
  xxx_finalize(&xxx);

  return 0;
}
