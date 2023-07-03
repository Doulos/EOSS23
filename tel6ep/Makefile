SUBDIRS := $(wildcard demo?)

.PHONY: all clean

all clean: $(SUBDIRS)
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir $@; \
	done
