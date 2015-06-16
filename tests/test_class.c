#include <stdio.h>
#include "hh/noclass.h"
#include "class.h"
#include "testing.h"
#include "hh.h"

static bool	test_new_1()
{
  local testingClass test = new(testingClass, 1);

  return (test != NULL);
}

static bool	test_new_2()
{
  local testingClass test = new(testingClass, 1);

  return ($(test)->getValue() == 1);
}

static bool	test_delete_1()
{
  testingClass test = new(testingClass, 2);

  delete(test);
  return (true);
}

static bool	test_value_1()
{
  local testingClass test = new(testingClass, 2);

  $(test)->setValue(3);
  return ($(test)->getValue() == 3);
}

void	test_class(int results[2])
{
  test(test_new_1, "Basic new test");
  test(test_new_2, "New parameter test");
  test(test_delete_1, "Basic delete test");
  test(test_value_1, "Test getter / setter");
}
