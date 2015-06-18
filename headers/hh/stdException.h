#pragma once

#include "hh.h"

#define HH_EXCEPTION_BUFFER_SIZE	300

class(Exception)
{
  char	*protected(file);
  int	protected(line);
  char	*protected(function);
  char	*protected(message);

  char	*public(method getFile)();
  int	public(method getLine)();
  char	*public(method getFunction)();
  char	*public(method getMessage)();
  char	*public(method toString)();

  char	private(buffer)[HH_EXCEPTION_BUFFER_SIZE];
} end;
