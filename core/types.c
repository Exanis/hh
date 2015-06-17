#include "hh.h"

void	*hh_find_parent_of_type(hh_object_struct *object, hh_object_struct *this)
{
  if (this == NULL)
    return NULL;

  size_t	jump = sizeof(hh_object_struct);
  size_t	jumped = 0;
  size_t	max_jump = this->size;

  if (this->magic_number != HH_MAGIC_NUMBER)
    return (NULL);
  while (object->__this_identifier != this->__this_identifier)
    {
      void	*tmp;

      this = (hh_object_struct *) (((char *) this) + jump);
      jumped += jump;
      if (jumped >= max_jump || this->magic_number != HH_MAGIC_NUMBER)
	return (NULL);
      if ((tmp = hh_find_parent_of_type(object, this)) != NULL)
	return (tmp);
      jump = this->size;
    }
  return (this);
}

void	*hh_find_child_of_type(hh_object_struct *type, hh_object_struct *this)
{
  char	*position = (char *) this;

  if (this == NULL)
    return NULL;
  position--;
  do {
    while (((hh_object_struct *) position)->magic_number != HH_MAGIC_NUMBER)
      position--;
    if (((hh_object_struct *) position)->__this_identifier == type->__this_identifier)
      return position;
  } while (1);
}

void	*hh_find_of_type(hh_object_struct *type, hh_object_struct *this)
{
  void	*result;

  if (this == NULL)
    return NULL;
  result = hh_find_parent_of_type(type, this);
  if (!result)
    result = hh_find_child_of_type(type,this);
  return (result);
}
