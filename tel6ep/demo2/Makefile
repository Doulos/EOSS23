CC ?= gcc
EXTRA_CFLAGS = -pthread  -Wl,-z,noexecstack
TARGETS = stack-overflow 

all: $(TARGETS)

stack-overflow: stack-overflow.c 
	$(CC) $(EXTRA_CFLAGS) -o $@ $<

clean:
	rm $(TARGETS)