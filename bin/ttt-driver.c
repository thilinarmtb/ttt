#include <stdio.h>
#include <ttt.h>

int main(int argc, char **argv) {
  struct ttt_t *ttt = ttt_init(&argc, &argv);

  for (int i = 0; i < argc; i++) printf("%d: %s\n", i, argv[i]);

  ttt_finalize(&ttt);

  return 0;
}
