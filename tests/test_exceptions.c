#include <stdio.h>
#include "hh/noclass.h"
#include "hh/stdException.h"
#include "class.h"
#include "testing.h"
#include "hh.h"

static bool	test_exception_1()
{
  try
    {
      return (true);
    }
  finally
    {
      return (false);
    }
  return (false);
}

static bool	test_exception_2()
{
  try
    {
      throw(new_exception("An error occured"));
      return (false);
    }
  finally
    {
      delete(exception);
      return (true);
    }
  return (false);
}

static bool	test_exception_3()
{
  try
    {
      throw(new_exception("An error occured"));
      return (false);
    }
  catch(testingClass)
  {
    return (false);
  }
  catch(Exception)
  {
    delete(exception);
    return (true);
  }
  finally
    {
      return (false);
    }
  return (false);
}

void	test_exception(int results[2])
{
  test(test_exception_1, "Basic test");
  test(test_exception_2, "Basic exception thrown test");
  test(test_exception_3, "Specialized catch test");
}
