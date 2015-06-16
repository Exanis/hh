#pragma once

#define	new(what, ...)	({ hh_new(__hh_definition_ ## what); hh_init_memory(__VA_ARGS__); })
#define	$(what)		({ hh_tmp_this_reference = what; what; })

#define construct	auto void	__hh_construct();	\
  __construct_func = &__hh_construct;				\
  void	__hh_construct

#define destruct	auto void	__hh_destruct();	\
  __destruct_func = &__hh_destruct;				\
  void	__hh_destruct

#define	extends(what)	what

#define	local	__attribute__ ((cleanup(hh_cleanup_local)))
