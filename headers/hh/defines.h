#pragma once

#define HH_MAGIC_NUMBER	0xCA11AB1E

#define	new(what, ...)	({ hh_new(__hh_definition_ ## what); hh_init_memory(__VA_ARGS__); })
#define	$(what)		({ hh_tmp_this_reference = what; what; })

#define construct	auto void	__hh_construct();	\
  __construct_func = &__hh_construct;				\
  void	__hh_construct

#define destruct	auto void	__hh_destruct();	\
  __destruct_func = &__hh_destruct;				\
  void	__hh_destruct

#define	extends(what)	__hh_no_ptr_ ##what

#define using(what)	struct hh_object_struct_complete_ ##what;	\
  typedef struct hh_object_struct_complete_ ##what *what

#define	parent(what, ...)	({ hh_tmp_this_reference = this; hh_construct_object(__hh_definition_ ##what); hh_init_memory(__VA_ARGS__); })

#define local	__attribute__((cleanup(hh_cleanup_local)))
