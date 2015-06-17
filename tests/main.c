#include <stdio.h>
#include "hh/noclass.h"
#include "testing.h"
#include "hh.h"

bool	launch_test(void (*func)(int[2]), char *name)
{
  int	results[2] = {0, 0};

  printf("===== %s =====\n", name);
  func(results);
  printf("===== Resultats : %d / %d =====\n", results[1], results[0]);
  return (results[0] == results[1]);
}

int	main()
{
  int	results[2] = {0, 0};

  main_test(test_class);
  main_test(test_parent);
  printf("[===== TOTAL RESULT : %d / %d sections OK =====]\n", results[1], results[0]);
  return !(results[0] == results[1]);
}
