#include <stdio.h>
#include "hh/noclass.h"
#include "parent.h"
#include "testing.h"
#include "hh.h"

static bool	test_parent_1()
{
  local child	test = new(child, 32);

  return ($(test)->getValue() == 32);
}

static bool	test_parent_2()
{
  local child	test = new(child, 0);

  $(test)->doSomething(8);
  return ($(test)->getValue() == 8);
}

void	test_parent(int results[2])
{
  test(test_parent_1, "Basic parent test");
  test(test_parent_2, "Child use parent method");
}
