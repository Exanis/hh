#undef class
#undef method
#undef end

#if __INCLUDE_LEVEL__ < 3

#define	method(name)	*__hh_type_check_ ##name;			\
  auto typeof(*__hh_type_check_ ##name)	__hh_hidden_func_ ##name ();	\
  									\
  typeof(*__hh_type_check_ ##name)	name()				\
  {									\
    void	*old_this = this;					\
    void	*args = __builtin_apply_args();				\
    void	*result;						\
    									\
    this = hh_tmp_this_reference;					\
    result = __builtin_apply(						\
			     (void (*)()) &__hh_hidden_func_ ##name,	\
			     args, HH_COPY_STACK_SIZE);			\
    this = old_this;							\
    __builtin_return(result);						\
  };									\
  									\
  this->name = &name;							\
									\
  typeof(*__hh_type_check_ ##name)	__hh_hidden_func_ ##name

#define	class(name)							\
  static name	this;							\
  static void	__init_ ##name();					\
  static void	__delete_ ##name();					\
									\
  static hh_object_struct __object_definition_ ##name = {		\
    &this,								\
    &__init_ ##name,							\
    &__delete_ ##name,							\
    sizeof(__hh_no_ptr_ ##name)						\
  };									\
  									\
  hh_object_struct	*__hh_definition_ ##name = &__object_definition_ ##name; \
									\
  static void	(*__construct_func)() = NULL;				\
  static void	(*__destruct_func)() = NULL;				\
  static void	__init_obj_ ##name();					\
									\
  static void	__delete_ ##name(void *what)				\
  {									\
    name old_this = this;						\
									\
    this = what;							\
    if (__destruct_func)						\
      __destruct_func();						\
    this = old_this;							\
  }									\
									\
  static void	__object_ ##name();					\
									\
  static void	__init_ ##name()					\
  {									\
    void	*args = __builtin_apply_args();				\
    name	old_this = this;					\
									\
    this = hh_tmp_this_reference;					\
    __object_ ##name();							\
    if (__construct_func != NULL)					\
      __builtin_apply(__construct_func, args, HH_COPY_STACK_SIZE);	\
    this = old_this;							\
  }									\
									\
  void	__object_ ##name()

#define end	

#else

#define	class(name)	typedef struct hh_object_struct_complete_ ##name *name; \
  typedef struct hh_object_struct_complete_ ##name __hh_no_ptr_ ##name;	\
  extern	hh_object_struct *__hh_definition_ ##name;		\
									\
  struct hh_object_struct_complete_ ##name				\
  {									\
  hh_object_struct hh_base_obj_marker;					\
  struct

#define end	;}

#define method	*
#endif
