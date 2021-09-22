# BEGIN of VARIABLE def

# ASSIGNMENT for VARIABLES
# 		:= simple      assign: only valid to the variable in this current statement
# 		=  recursive   assign: will affect any variables referring to this one
# 		?= conditional assign: if the variable is undefined, using value on the right; if not, this statement is invalid
# 		+= appending   assign: append a new value separated by space ' ' 

CC = gcc
CXX = g++
VFLAGS = -DVERBOSE
CFLAGS = -O2 -DDEBUG -Wall 
VFLAGS += $(CFLAGS)
LDFLAGS = 

# wildcard function: to expand .cpp files, usually used for Variables
# notdir   function: to remove dirpath from absolute filename

SRCS = $(notdir $(wildcard *.cpp))

# patsubst function: to substitute suffix .cpp for .o

OBJS = $(patsubst %.cpp, %.o, $(SRCS))

TARGET = main mainv

# END of VARIABLES def


all: $(TARGET)
	@echo $(SRCS)
	@echo $(OBJS)

# filter-out funtion: to filter out the corresponding files from a VARIABLE
# 		   $@ symbol: THE obj file
# 		   $^ symbol: all the dependent file list 
# 		   $< symbol: the 1st dependent file 
# 		   $? symbol: dependent file list that is newer than THE obj file

main: main.o $(filter-out , $(OBJS))
	$(CXX) $(CFLAGS) -o $@ $^ $(LDFLAGS)

mainv: main.o big_integer_v.o $(filter-out big_integer.o, $(OBJS))
	$(CXX) $(VFLAGS) -o $@ $^ $(LDFLAGS)

big_integer_v.o: big_integer.cpp big_integer.h
	$(CXX) -c $(VFLAGS) big_integer.cpp -o big_integer_v.o

%.o: %.cpp
	$(CXX) -c $(CFLAGS) $^ -o $@

.PHONY: clean

# the '-' before rm is to neglect error code from rm command if no such file exist

clean:
	-rm *.o
	-rm main mainv

