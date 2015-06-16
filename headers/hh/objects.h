#pragma once

#include <stdlib.h>

typedef struct
{
  void	*__this_identifier;
  void	(*__init)();
  void	(*__delete)(void *);
  size_t size;
}	hh_object_struct;

void	hh_new(hh_object_struct *);
void	*hh_init_memory();
void	delete(void *);
void	hh_cleanup_local(void *);

extern void	*hh_tmp_this_reference;
