#pragma once

typedef void	*var;

#define when(object, type)	{					\
  void	*hh_tmp_name_ ##object = object;				\
  type	object = hh_find_parent_of_type(__hh_definition_ ##type, hh_tmp_name_ ##object); \
									\
  if (object != NULL)

#define end_when	}
