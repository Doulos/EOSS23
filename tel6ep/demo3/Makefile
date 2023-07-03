CC ?= gcc
EXTRA_CFLAGS = -pthread -O0 -g
TARGETS = rt-drink

all: $(TARGETS)

rt-drink: rt-drink.c 
	$(CC) $(EXTRA_CFLAGS) -o $@ $<

rt-drink-ok: rt-drink-ok.c 
	$(CC) $(EXTRA_CFLAGS) -o $@ $<
	
clean:
	rm $(TARGETS)