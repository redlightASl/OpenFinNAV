# SPDX-License-Identifier: GPL-2.0
# ===========================================================================
# VERSION = 6
# PATCHLEVEL = 2
# SUBLEVEL = 0
# EXTRAVERSION =
# NAME = Hurr durr I'ma ninja sloth

export KBUILD_VERBOSE = 0
export quiet = quiet_
export Q = @
export srctree = $(CURDIR)
export objtree = $(CURDIR)

include $(KCONFIG_PATH)/Kbuild.include

export KCONFIG_CONFIG = $(FINNAV_BUILD_DIR)/target/kconfig/.config
# export KCONFIG_AUTOHEADER = $(FINNAV_BUILD_DIR)/target/kconfig/include/generated/autoconf.h
export KCONFIG_AUTOCONFIG = $(FINNAV_BUILD_DIR)/target/kconfig/include/config/auto.conf
export KCONFIG_TRISTATE = $(FINNAV_BUILD_DIR)/target/kconfig/include/config/tristate.conf
export KCONFIG_RUSTCCFG = $(FINNAV_BUILD_DIR)/target/kconfig/include/generated/rustc_cfg

# SHELL used by kbuild
export CONFIG_SHELL := $(shell if [ -x "$$BASH" ]; then echo $$BASH; \
                else if [ -x /bin/bash ]; then echo /bin/bash; \
                else echo sh; fi ; fi)
export HOSTCC       = gcc
export HOSTCXX      = g++
export HOSTCFLAGS   = -O2 -Wall -Wextra
export HOSTCXXFLAGS = -O2 -Wall -Wextra

fixdep:
	$(MAKE) -C fixdep all

%config: fixdep force
	$(MAKE) $(build)=$(KCONFIG_PATH)/kconfig $@
	$(MAKE) $(build)=$(KCONFIG_PATH)/kconfig syncconfig

fixdep_clean:
	$(MAKE) -C fixdep clean

clean: fixdep_clean
	rm -rf $(KCONFIG_PATH)/kconfig/*.o
	rm -rf $(KCONFIG_PATH)/kconfig/lxdialog/*.o
	rm -rf $(KCONFIG_PATH)/kconfig/lxdialog/.*.cmd
	rm -rf $(KCONFIG_PATH)/kconfig/.*.cmd
	rm -rf $(KCONFIG_PATH)/kconfig/*.tmp
	rm -rf $(KCONFIG_PATH)/kconfig/conf
	rm -rf $(KCONFIG_PATH)/kconfig/lexer.lex.c
	rm -rf $(KCONFIG_PATH)/kconfig/mconf
	rm -rf $(KCONFIG_PATH)/kconfig/mconf-bin
	rm -rf $(KCONFIG_PATH)/kconfig/mconf-cfg
	rm -rf $(KCONFIG_PATH)/kconfig/mconf-cflags
	rm -rf $(KCONFIG_PATH)/kconfig/mconf-libs
	rm -rf $(KCONFIG_PATH)/kconfig/parser.tab.*

force:

.PHONY: fixdep %config fixdep_clean clean force

# *** EOF ***
