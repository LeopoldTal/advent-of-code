TESTS = check_intcode
check_PROGRAMS = check_intcode
check_intcode_SOURCES = check_intcode.c check_str_to_intcode_program.c $(top_builddir)/src/intcode.h
check_intcode_CFLAGS = @CHECK_CFLAGS@ -Wall -Wpedantic -fsanitize=address
check_intcode_LDADD = $(top_builddir)/src/libintcode.la @CHECK_LIBS@
