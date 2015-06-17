#include <stdio.h>
#include "hh/noclass.h"
#include "parent.h"
#include "testing.h"
#include "hh.h"

static bool	test_polymorphism_internal_1(var myclass)
{
  when(myclass, testingClass)
    {
      $(myclass)->setValue(3);
      return ($(myclass)->getValue() == 3);
    } end_when;
  return (false);
}

static bool	test_polymorphism_internal_2(var myclass)
{
  when(myclass, child)
    {
      $(myclass)->doSomething(8);
      return ($(myclass)->getValue() == 8);
    } end_when;
  return (false);
}

static bool	test_polymorphism_1()
{
  local testingClass clazz = new(testingClass, 1);

  return (test_polymorphism_internal_1(clazz));
}

static bool	test_polymorphism_2()
{
  local child clazz = new(child, 1);

  return (test_polymorphism_internal_1(clazz));
}

static bool	test_polymorphism_3()
{
  local testingClass clazz = new(testingClass, 1);

  return (!test_polymorphism_internal_2(clazz));
}

static bool	test_polymorphism_4()
{
  local child clazz = new(child, 1);

  return (test_polymorphism_internal_2(clazz));
}

void	test_polymorphism(int results[2])
{
  test(test_polymorphism_1, "Basic test");
  test(test_polymorphism_2, "Polymorphism on parent class");
  test(test_polymorphism_3, "Invalid class given");
  test(test_polymorphism_4, "Good class given, has child");
}
