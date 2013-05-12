PATH_DEST_LIB= ./lib
PATH_DEST_BIN= ./bin
PATH_SRC=./src
PATH_NVE=$(PATH_SRC)/nve
PATH_D2V=$(PATH_SRC)/d2vlib
PATH_GTT=$(PATH_SRC)/gttlib
PATH_PDV=$(PATH_SRC)/pdvllib
SUB_DIRS = $(PATH_NVE) $(PATH_D2V) $(PATH_GTT) $(PATH_PDV)
MAEK = make

subdirs :
	@for dir in $(SUB_DIRS); do \
		$(MAKE) -C $$dir all; \
		if [ $$? != 0 ]; then exit 1; fi; \
	done

clean :
	@for dir in $(SUB_DIRS); do \
		$(MAKE) -C $$dir clean; \
		if [ $$? != 0 ]; then exit 1; fi; \
	done


