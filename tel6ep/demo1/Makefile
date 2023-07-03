CC ?= gcc
EXTRA_CFLAGS = -pthread -Og -g
TARGETS = hello hello-ok race race-ok


all: $(TARGETS)

hello: hello.c
	$(CC) $(EXTRA_CFLAGS) -o $@ $<

hello-ok: hello-ok.c 
	$(CC) $(EXTRA_CFLAGS) -o $@ $<

race: race.c
	$(CC) $(EXTRA_CFLAGS) -o $@ $<

race-ok: race-ok.c
	$(CC) $(EXTRA_CFLAGS) -o $@ $<

clean: 
	rm $(TARGETS)
