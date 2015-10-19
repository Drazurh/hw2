# This sample Makefile allows you to make an OpenGL application
#   whose source is exactly one .c file or one .cc file under Solaris.
#   check the location of the X libraries on your implementation.
#
# To use this Makefile, you type:
#
#        make xxxx
#                  
# where
#       xxxx.cc is the name of the c++-file you wish to compile 
#  or 
#       xxxx.c is the name of the c-file you wish to compile 
#       
# A binary named xxxx will be produced
# Libraries are assumed to be in the default search paths
# as are any required include files

#
# Modified by Prof. Chelberg to also allow you to make from a single
# c++ source file.  So if xxxx.cc is the sourcefile, you type make
# xxxx to produce the binary file.

# last-modified: Mon Sep 17 15:17:00 2012

# Assumes the following file exists in the proper place.
#include /home/cs4250/code-egs/Makefile.defs
include ./Makefile.defs

# Next line says what options to use to compile programs
OPTIONS+=-Wall;

OBJECTS = $(patsubst %.cc,%,$(wildcard *.cc))

all: hw2

hw2: hw2.o game.o entity.o
	$(CC)  hw2.o game.o entity.o  $(InitShader) $(OPTIONS) $(LDLIBS) -o hw2

hw2.o: hw2.cc
	$(CC) -c hw2.cc   $(InitShader) $(OPTIONS) $(LDLIBS) 

game.o: game.cc
	$(CC) -c game.cc   $(InitShader) $(OPTIONS) $(LDLIBS) 

entity.o: entity.cc
	$(CC) -c entity.cc $(InitShader) $(OPTIONS) $(LDLIBS)


clean:
	rm -f $(OBJECTS) *~
