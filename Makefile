# The c compiler
CC = g++
CFLAGS = -lm 

# The filename
file1 = lcs
file2 = rk

# The build target executable:

all: lcs rk

lcs: $(file1).c
	$(CC)  $(CFLAGS) -o $(file1) $(file1).c
rk: $(file2).cpp
	$(CC)  $(CFLAGS) -o $(file2) $(file2).cpp

clean: 
	rm -rf lcs rk