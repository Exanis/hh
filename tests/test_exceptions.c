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

static void	test_exception_4_1()
{
  throw(new_exception("An error occured"));
}

static bool	test_exception_4()
{
  try
    {
      test_exception_4_1();
      return (false);
    }
  finally
    {
      delete(exception);
      return (true);
    }
  return (false);
}

static bool	test_exception_5_1()
{
  {
    try
      {
	// Do nothing
      }
    finally
      {
	return (false);
      }
  }
  throw(new_exception("An error occured"));
  return (false);
}

static bool	test_exception_5()
{
  try
    {
      return (test_exception_5_1());
    }
  finally
    {
      delete(exception);
      return (true);
    }
  return (false);
}

static bool	test_exception_6_1()
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

static bool	test_exception_6()
{
  try
    {
      return (test_exception_6_1());
    }
  finally
    {
      return (false);
    }
  return (false);
}

static bool	test_exception_7()
{
  try
    {
      // Do nothing
    }
  finally
    {
      return (false);
    }

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

void	test_exception(int results[2])
{
  test(test_exception_1, "Basic test");
  test(test_exception_2, "Basic exception thrown test");
  test(test_exception_3, "Specialized catch test");
  test(test_exception_4, "Exception in subfunction");
  test(test_exception_5, "Nested exceptions - should not throw in first");
  test(test_exception_6, "Nested exceptions - should throw in first");
  test(test_exception_7, "Two exceptions in the same function");
}
