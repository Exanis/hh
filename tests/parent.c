#include "parent.h"
#include "hh.h"

class(child)
{
  construct(int value)
    {
      parent(testingClass, value);
    }

  void	method(doSomething)(int value)
  {
    $(this)->setValue(value);
  }
} end;
