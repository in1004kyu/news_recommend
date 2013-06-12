MAEK = make

SUB_DIRS = nve d2vlib gttlib pdvllib nvmuldiv cosine evald traind collectData 
CLEANDIRS = $(SUB_DIRS:%=clean-%)

all:subdirs

subdirs: $(SUB_DIRS)

$(SUB_DIRS):
	$(MAKE) -C $@


clean: $(CLEANDIRS)
$(CLEANDIRS):
	$(MAKE) -C $(@:clean-%=%) clean

.PHONY: subdirs $(SUB_DIRS) clean
