#ifndef	public
# define	public(a)	(a)
#endif

#undef private

#if __COUNTER__ == 0
# define	private(a)	(a)
#else
# define	private(a)	(a ##__hh_private_field_do_not_use_)
#endif
