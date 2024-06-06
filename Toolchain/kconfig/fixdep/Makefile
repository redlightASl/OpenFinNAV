###############################################################################
# SPDX-License-Identifier: GPL-3.0-or-later
###############################################################################
.DEFAULT_GOAL = all
all: build
build: fixdep
fixdep: fixdep.o
	@gcc '$<' -o '$@'

%.o: %.c
	@echo '  HOSTCC  kconfig/fixdep/$(@F)'
	@gcc -c '$<' -o '$@'

clean:
	rm -rf *.o
	rm -rf *.cmd
	rm -rf fixdep

.PHONY: all build fixdep clean

# *** EOF ***
