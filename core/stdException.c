#include <string.h>
#include <stdio.h>
#include "hh/stdException.h"
#include "hh.h"

class(Exception)
{
  construct(char *function, char *file, int line, char *message)
    {
      $(this)->file = file;
      $(this)->line = line;
      $(this)->function = function;
      $(this)->message = message;
    }

  char	*method(getFile)()
  {
    return $(this)->file;
  }

  int	method(getLine)()
  {
    return $(this)->line;
  }

  char	*method(getFunction)()
  {
    return $(this)->function;
  }

  char	*method(getMessage)()
  {
    return $(this)->message;
  }

  char	*method(toString)()
  {
    snprintf($(this)->buffer, HH_EXCEPTION_BUFFER_SIZE, "[%s:%d][%s] %s", $(this)->file, $(this)->line, $(this)->function, $(this)->message);
    return ($(this)->buffer);
  }
}
