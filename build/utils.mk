###############################################################
# Auxiliary Tools
# NOTE: These are not tied to the default goals and must be invoked manually
###############################################################

######################################
# Functions
######################################
# convert parameter to lowercase
define lower
$(shell echo $(1) | tr '[A-Z]' '[a-z]')
endef

# convert parameter to uppercase
define upper
$(shell echo $(1) | tr '[a-z]' '[A-Z]')
endef

# Strip quotes and then whitespaces
qstrip = $(strip $(subst ",,$(1)))

ifeq ($(OSFAMILY), windows)
red :=
green :=
yellow :=
reset :=
else ifeq ($(OSFAMILY), linux)
red := $(shell tput setaf 1)
green := $(shell tput setaf 2)
yellow := $(shell tput setaf 3)
reset := $(shell tput sgr0)
endif

define INFO
	$(info $(green)[INFO: $1]$(reset) $2)
endef

define WARNING
	$(warning $(yellow)[WARNING: $1]$(reset) $2)
endef

define ERROR
	$(error $(red)[ERROR: $1]$(reset) $2)
endef

# *** included ***
