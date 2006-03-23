SUBDIRS = src

all install clean:
	for dir in $(SUBDIRS) ; do $(MAKE) -C $$dir $@ ; done

