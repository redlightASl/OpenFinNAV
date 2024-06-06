#!/usr/bin/env python
# -*- coding: UTF-8 -*-
import os, sys
from kconfiglib import Kconfig
from menuconfig import menuconfig

finnav_root_path = os.path.join(os.getcwd(), "..", "..", "..")

def mconf_set_env(menu_style, menu_config, menu_header):
    """
    Set Kconfig Env
    """
    os.environ["MENUCONFIG_STYLE"] = menu_style
    os.environ["KCONFIG_CONFIG"] = menu_config
    os.environ["KCONFIG_CONFIG_HEADER"] = menu_header
    # os.environ["KCONFIG_AUTOHEADER"] = os.path.join(finnav_root_path, "build", "target", "kconfig", "menuconfig.h")
    # os.environ["CONFIG_"] = ""


def mconf(argv):
    kconfig = os.path.join(finnav_root_path, "build", "kconfig", "Kconfig")
    display_style = "default selection=fg:white,bg:blue"
    target_config = os.path.join(finnav_root_path, "build", "target", "kconfig", ".config")
    menu_header = "#\n# Automatically generated file; DO NOT EDIT.\n"
    mconf_set_env(display_style, target_config, menu_header)

    kconf = Kconfig(filename=kconfig)
    if len(argv) == 2 and argv[1] == 'genconfig': # generate menuconfig.h from ".config"
        kconf.load_config()
        print(kconf.write_config())
    elif len(argv) == 2 and argv[1] == 'defconfig': # defconfig
        kconf.load_allconfig("alldef.config")
        print(kconf.write_config())
    elif len(argv) == 2 and argv[1] == 'allyesconfig': # all yes config
        kconf.warn = False
        for sym in kconf.unique_defined_syms:
            sym.set_value(1 if sym.choice else 2)
        for choice in kconf.unique_choices:
            choice.set_value(2)
        kconf.warn = True
        kconf.load_allconfig("allyes.config")
        print(kconf.write_config())
    elif len(argv) == 2 and argv[1] == 'allnoconfig': # all no config
        kconf.warn = False
        for sym in kconf.unique_defined_syms:
            sym.set_value(2 if sym.is_allnoconfig_y else 0)
        kconf.warn = True
        kconf.load_allconfig("allno.config")
        print(kconf.write_config())
    else:
        menuconfig(kconf) # do menuconfig
    kconf.write_autoconf()


if __name__ == "__main__":
    mconf(sys.argv)
