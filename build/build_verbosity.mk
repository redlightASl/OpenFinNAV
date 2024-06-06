# Set verbosity level based on the V= parameter
# V=0 Low print nothing
# V=1 High print all
# V=undef print V0 information
export AT := @

ifndef V
export V0 :=
export V1 := $(AT)
export STDOUT :=
else ifeq ($(V), 0)
export V0 := $(AT)
export V1 := $(AT)
export STDOUT := "> /dev/null"
export MAKE := $(MAKE) --no-print-directory
else ifeq ($(V), 1)
export V0 :=
export V1 :=
export STDOUT :=
endif

# *** included ***
