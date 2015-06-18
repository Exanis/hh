#include <string.h>
#include <hh/stdException.h>
#include <hh.h>

void	*hh_tmp_this_reference = NULL;
static __hh_no_ptr_Exception	hh_mem_error_exception;

void	hh_new(hh_object_struct *object_identifier)
{
  void	*object = malloc(object_identifier->size);

  if (!object)
    {
      memset(&hh_mem_error_exception, 0, __hh_definition_Exception->size);
      memcpy(&hh_mem_error_exception, __hh_definition_Exception, sizeof(*__hh_definition_Exception));
      hh_init_memory(__RAISE_FUNC, __FILE__, __LINE__, "Cannot allocate memory");
      throw(&hh_mem_error_exception);
    }
  memset(object, 0, object_identifier->size);
  memcpy(object, object_identifier, sizeof(*object_identifier));
  hh_tmp_this_reference = object;
}

void	hh_construct_object(hh_object_struct *type)
{
  hh_object_struct	*child = hh_tmp_this_reference;
  hh_object_struct	*parent = (hh_object_struct *) (((char *) child) + child->next_parent);

  memcpy(parent, type, sizeof(*type));
  child->next_parent += parent->size;
  hh_tmp_this_reference = parent;
}

void	*hh_init_memory()
{
  void	*args = __builtin_apply_args();
  hh_object_struct	*object = hh_tmp_this_reference;
  
  object->__construct();
  __builtin_apply(object->__init, args, HH_COPY_STACK_SIZE);
  return (object);
}

static void	run_delete(void *object)
{
  hh_object_struct *obj = object;
  char	*struct_ptr = object;
  char	*max_position;
  
  max_position = struct_ptr + obj->size;
  obj->__delete(object);
  struct_ptr = struct_ptr + sizeof(hh_object_struct);
  while (struct_ptr < max_position)
    {
      hh_object_struct *obj_struct = (hh_object_struct *) struct_ptr;

      if (obj_struct->magic_number != HH_MAGIC_NUMBER)
	return ;

      char	*next_struct_ptr = struct_ptr + obj_struct->size;
      
      run_delete((void *) obj_struct);
      struct_ptr = next_struct_ptr;
    }
}

void	delete(void *object)
{
  run_delete(object);
  free(object);
}

void	hh_cleanup_local(void *obj)
{
  hh_object_struct **object = (hh_object_struct **) obj;

  delete(*object);
}
