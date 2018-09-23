#
#   JAM(mbp) - The Joaquim-Andrew-Mats Message Base Proposal
#
#   C API
#
#   Written by Mats Wallin
#
#   ----------------------------------------------------------------------
#
#   makefile (JAMmb)
#
#   Make file for JAM(mbp) C API library and GCC for a Sparc
#
#   Copyright 1993 Joaquim Homrighausen, Andrew Milner, Mats Birch, and
#   Mats Wallin. ALL RIGHTS RESERVED.
#
CC      = gcc
CFLAGS  = -c -ansi

OBJS    = jamfetch.o jamfield.o jamhinfo.o jamlock.o\
          jamlread.o jammbini.o jamscan.o  jamstore.o\
          jamcrc32.o jamsys.o

.c.o:
	$(CC) $(CFLAGS) $*.c

libjamcapi.a:   $(OBJS)
	ar rcv $@ $?
	ranlib $@
