include $(FINNAV_BUILD_DIR)/compile.mk


######################################
# Inner Variables
######################################
TARGET := unittest
BUILD_DIR := $(FINNAV_LIB_DIR)/test/$(TARGET)/$(TARGET)_build

CMAKE_GEN_TARGET := "Unix Makefiles"
CMAKE_CMD := cmake .. -G $(CMAKE_GEN_TARGET) \
-DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ -DCMAKE_CXX_FLAGS=-std=c++11 \
-DBUILD_GMOCK=OFF -DINSTALL_GTEST=OFF

CXX_TB := D:/mingw64-posix-seh/bin/g++
# CXX_TB := g++

LIBDIR_GTEST := -L$(FINNAV_LIB_DIR)/test/googletest/build/lib
INCLUDE_GTEST := -I$(FINNAV_LIB_DIR)/test/googletest/googletest/include
INCLUDE_UNIT := -I$(FINNAV_LIB_DIR)/test/unittest/include
TBFLAGS += $(INCLUDE_UNIT) $(INCLUDE_GTEST) $(LIBDIR_GTEST)
# TBFLAGS += -lgtest -lgtest_main -pthread

# C sources Config for testbench
TB_SRC_DIR := $(FINNAV_LIB_DIR)/test/unittest
CPP_SOURCES := $(wildcard $(TB_SRC_DIR)/*.cpp)

$(call add_sources_cpp)
#######################################
# Target
#######################################
.DEFAULT_GOAL = all
all: build_gtest

build_gtest: cleanlib
	cd googletest && mkdir build && cd build && $(CMAKE_CMD) && $(MAKE)

build: build_gtest

unittest: $(FINNAV_LIB_DIR)/test/unittest
	$(FINNAV_LIB_DIR)/test/unittest

$(FINNAV_LIB_DIR)/test/unittest: $($(TARGET)_OBJS)
	$(V0)$(CXX_TB) $^ $(TBFLAGS) -lgtest -lgtest_main -pthread -o $@

$(BUILD_DIR)/%.o: %.cpp Makefile | $(BUILD_DIR)
	$(V0)$(CXX_TB) -c $< $(TBFLAGS) -o $@

$(BUILD_DIR):
	$(V1)mkdir -p $@

clean:
	rm -rf $(BUILD_DIR)

cleanlib:
	rm -rf googletest/build

.PHONY: build_gtest unittest clean cleanlib
# *** EOF ***
