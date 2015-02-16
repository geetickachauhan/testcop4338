# Disable implict rules with "make -r"

TARGET = geometry
CC = gcc
CFLAGS = -Wall -ggdb 
#enable warnings and debugging info
LDFLAGS = 
# here we could add dynamically linked libraries like -lrt -lm -lpthread and others

# here we list all source files
SRC = geometry.c list.c topology.c A.c B.c C.c D.c 
OBJS = $(SRC:.c=.o)
DEPS = $(OBJS:.o=.d)
DSYM = $(OBJS:.o=.dSYM)

.PHONY: all clean

all: $(TARGET)

# let's clean up the mess
clean:
	rm -f $(TARGET) $(OBJS) $(DEPS); 
	rm -rf $(DSYM)

%: %.o $(OBJS)
	$(CC) $^ $(LDFLAGS) -o $@


# the -MMD flags creates dependency files for every object, so 
%.o: %.c
	$(CC) $(CFLAGS) -c -MMD $<  


# here make reads the dependency files and handle them.
-include $(DEPS)