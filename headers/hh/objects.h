#pragma once

#include <stdlib.h>

typedef struct
{
  unsigned int	magic_number;
  void	*__this_identifier;
  size_t	next_parent;
  void	(*__init)();
  void	(*__construct)();
  void	(*__delete)(void *);
  size_t size;
}	hh_object_struct;

void	hh_new(hh_object_struct *);
void	hh_construct_object(hh_object_struct *);
void	*hh_init_memory();
void	delete(void *);
void	hh_cleanup_local(void *);

void	*hh_find_parent_of_type(hh_object_struct *, hh_object_struct *);
void	*hh_find_child_of_type(hh_object_struct *, hh_object_struct *);
void	*hh_find_of_type(hh_object_struct *, hh_object_struct *);

extern void	*hh_tmp_this_reference;
