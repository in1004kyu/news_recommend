MAEK = make

SUB_DIRS = src
CLEANDIRS = $(SUB_DIRS:%=clean-%)

all:subdirs

subdirs: $(SUB_DIRS)

$(SUB_DIRS):
	$(MAKE) -C $@


clean: $(CLEANDIRS)
$(CLEANDIRS):
	$(MAKE) -C $(@:clean-%=%) clean

.PHONY: subdirs $(SUB_DIRS) clean
