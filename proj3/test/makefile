# Disable implict rules with "make -r"

TARGET = main 
CC = gcc
CFLAGS = -m32 -fpic -Wall -ggdb #enable warnings and debugging info
LDPATH = . 
SHFLAGS = -m32 -shared
LDFLAGS = -lmemory # here we could add dynamically linked libraries like -lrt -lm -lpthread and others

# here we list all source files
SRC = memory.c bits.c threads.c
OBJS = $(SRC:.c=.o)
DEPS = $(OBJS:.o=.d)
DSYM = $(OBJS:.o=.dSYM)

.PHONY: all clean

all: $(TARGET)

# let's clean up the mess
clean:
	rm -f $(TARGET) libmemory.so $(OBJS) $(DEPS); 
	rm -rf $(DSYM)

main: main.c libmemory.so
	$(CC) -m32 -o $@ $< $(LDFLAGS) -L$(LDPATH)

libmemory.so: memory.o bits.o
	$(CC) $(SHFLAGS) -o $@ $^

%: %.o
	$(CC) $^ $(LDFLAGS) -o $@

# the -MMD flags creates dependency files for every object, so 
%.o: %.c
	$(CC) $(CFLAGS) -c -MMD $<  


# here make reads the dependency files and handle them.
-include $(DEPS)