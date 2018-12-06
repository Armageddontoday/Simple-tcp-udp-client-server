MAKEFILES_DIR = config/makefiles

ifeq ($(MAKECMDGOALS),)
include $(MAKEFILES_DIR)/Makefile.x86_64.mk
endif
ifeq ($(MAKECMDGOALS),all)
include $(MAKEFILES_DIR)/Makefile.x86_64.mk
endif
ifeq ($(MAKECMDGOALS),x86_64)
include $(MAKEFILES_DIR)/Makefile.x86_64.mk
endif