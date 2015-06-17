#ifndef	public
# define	public(a)	(a)
#endif

#if __INCLUDE_LEVEL__ == 3
# if __COUNTER__ == 0
#  undef private
#  undef protected
#  define	private(a)	(a)
#  define	protected(a)	(a)
# else
#  undef private
#  undef protected
#  define	private(a)	(a ##__hh_private_field_do_not_use_)
#  define	protected(a)	(a ##__hh_protected_field_do_not_use_)
# endif
#elif __INCLUDE_LEVEL__ > 3
# undef private
# define	private(a)	(a ##__hh_private_field_do_not_use_)
#else
# undef private
# undef protected
# define	private(a)	(a ##__hh_private_field_do_not_use_)
# define	protected(a)	(a ##__hh_protected_field_do_not_use_)
#endif
