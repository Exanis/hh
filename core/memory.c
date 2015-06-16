#include <string.h>
#include "hh.h"

void	*hh_tmp_this_reference = NULL;

void	hh_new(hh_object_struct *object_identifier)
{
  void	*object = malloc(object_identifier->size);

  if (!object)
    return ; /* TODO: Implement throw and throw here. */
  memcpy(object, object_identifier, sizeof(*object_identifier));
  hh_tmp_this_reference = object;
}

void	*hh_init_memory()
{
  void	*args = __builtin_apply_args();
  hh_object_struct	*object = hh_tmp_this_reference;
  
  __builtin_apply(object->__init, args, HH_COPY_STACK_SIZE);
  return (object);
}

void	delete(void *object)
{
  ((hh_object_struct *) object)->__delete(object);
  free(object);
}

void	hh_cleanup_local(void *obj)
{
  hh_object_struct **object = (hh_object_struct **) obj;

  delete(*object);
}
