#list all .o files here
OBJS = smash.o commands.o history.o

#list all executables here
EXE = smash

CFLAGS = -Wall -std=c99

#make all
all:	rules.d $(EXE)

rules.d: Makefile $(wildcard *.c) $(wildcard *.h)
	gcc -MM $(wildcard *.c) >rules.d

-include rules.d

#general purpose
$(EXE): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

#make clean
clean:
	rm -f $(OBJS) $(EXE) *.d  *~
