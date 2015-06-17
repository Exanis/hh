#pragma once

#include <setjmp.h>

extern void	*hh_exception_result_ptr;
extern void	*hh_good_exception_caught;

#define	try	hh_exception_result_ptr = NULL;				\
  hh_good_exception_caught = NULL;					\
  __attribute__((unused, cleanup(hh_remove_try_context))) hh_exception_marker_ ##__LINE__; \
  if (setjmp(*hh_add_try_context()) == 0)

#define catch(what)	else if ((hh_good_exception_caught = hh_find_parent_of_type(__hh_definition_ ##what, hh_exception_result_ptr)) != NULL)

#define finally		else if ((hh_good_exception_caught = hh_exception_result_ptr) != NULL || true)
#define exception	hh_good_exception_caught

#define throw(what)	hh_exception_result_ptr = (void *) what; longjmp(*hh_get_last_try_context(), 1)

# if defined __cplusplus ? __GNUC_PREREQ (2, 6) : __GNUC_PREREQ (2, 4)
#  define	__RAISE_FUNC	__PRETTY_FUNCTION__
# else
#  if defined __STDC_VERSION__ && __STDC_VERSION__ >= 199901L
#   define	__RAISE_FUNC	__func__
#  else
#   define__RAISE_FUNC("Unknown function")
#  endif
# endif

#define	new_exception(message)	new(Exception, __RAISE_FUNC, __FILE__, __LINE__, message)

jmp_buf	*hh_add_try_context();
void	hh_remove_try_context(void *);
jmp_buf	*hh_get_last_try_context();
