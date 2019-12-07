lib_LTLIBRARIES = libintcode.la
libintcode_la_SOURCES = intcode.c intcode.h

bin_PROGRAMS = main
main_SOURCES = main.c
main_LDADD = libintcode.la

AM_CFLAGS =-Wall -Wpedantic -fsanitize=address
