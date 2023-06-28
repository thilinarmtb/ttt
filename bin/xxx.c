#include <stdio.h>
#include <xxx.h>

int main(int argc, char **argv) {
  struct xxx_t *xxx = xxx_init(&argc, &argv);

  for (int i = 0; i < argc; i++)
    printf("%d: %s\n", i, argv[i]);

  xxx_finalize(&xxx);

  return 0;
}
