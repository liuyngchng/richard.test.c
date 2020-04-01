SUBDIR = ./udt ./tcp
MAKE = make
$(EVERYTHING)::
	@for subdir in $(SUBDIR);\
	do \
		echo "making $@ in $$subdir";\
		(cd $(SUBDIR) && $(MAKE) -f makefile $@) || exit 1;\
	done
