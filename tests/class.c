#include "class.h"
#include "hh.h"

class(testingClass)
{
  construct(int value)
    {
      $(this)->value = value;
    }
  
  int	method(getValue)()
  {
    return $(this)->value;
  }

  void	method(setValue)(int value)
  {
    $(this)->value = value;
  }
}
