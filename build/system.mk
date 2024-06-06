######################################
# Check System Environment
######################################
UNAME ?= $(shell uname)
ARCH ?= $(shell uname -m)
OS ?= $(shell uname -s)
# ARCH
ifneq (,$(filter $(ARCH), x86_64 amd64))
X86-64 := 1
X86_64 := 1
AMD64 := 1
ARCHFAMILY := x86_64
else
ARCHFAMILY := $(ARCH)
endif

# Linux
ifeq ($(OS), Linux)
OSFAMILY := linux
endif
# Windows
ifeq ($(OS), Windows_NT)
OSFAMILY := windows
endif

ifndef OSFAMILY
$(error Detect OS failed!)
else
$(info Host OS is $(OSFAMILY)!)
endif

# Windows using MinGW shell
ifeq (MINGW, $(findstring MINGW,$(UNAME)))
MINGW := 1
$(info Using MinGW!)
endif

# Windows using Cygwin shell
ifeq (CYGWIN ,$(findstring CYGWIN,$(UNAME)))
CYGWIN := 1
$(info Using Cygwin!)
endif
# *** included ***
