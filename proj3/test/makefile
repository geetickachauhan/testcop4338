# Disable implict rules with "make -r"

TARGET = main 
CC = gcc
CFLAGS = -fpic -Wall -ggdb #enable warnings and debugging info
LDPATH = . 
LDFLAGS = -lmemory # here we could add dynamically linked libraries like -lrt -lm -lpthread and others

# here we list all source files
SRC = memory.c bits.c 
OBJS = $(SRC:.c=.o)
DEPS = $(OBJS:.o=.d)
DSYM = $(OBJS:.o=.dSYM)

.PHONY: all clean

all: $(TARGET)

# let's clean up the mess
clean:
	rm -f $(TARGET) $(OBJS) $(DEPS); 
	rm -rf $(DSYM)

main: main.c libmemory.so
	$(CC) -o $@ $< $(LDFLAGS) -L$(LDPATH)

libmemory.so: memory.o bits.o
	$(CC) -shared -o $@ $^

%: %.o
	$(CC) $^ $(LDFLAGS) -o $@

# the -MMD flags creates dependency files for every object, so 
%.o: %.c
	$(CC) $(CFLAGS) -c -MMD $<  


# here make reads the dependency files and handle them.
-include $(DEPS)