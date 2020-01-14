# General settings
MAKE_FILE = test.mk
SRC_DIR = test
BUILD_DIR = build/$(SRC_DIR)

CXX = g++
CXXFLAGS = -std=c++11 -Wall -MMD
AR = ar
ARFLAGS = rs

LIB_TEST_NAME = libelrond-test.a
LIB_TEST = $(BUILD_DIR)/$(LIB_TEST_NAME)

INCLUDES = -I$(SRC_DIR) -Iinclude $(addprefix -I, $(i))
MACROS = -DGENERIC_STD_PLATFORM -DLINUX_PLATFORM

LDLIBS = $(addprefix -l, $(ld))
LSLIBS = $(l)

LIB_TEST_SRC = $(shell find $(SRC_DIR)/elrond-test -type f \( -name "*.cpp" \) )
LIB_TEST_OBJ := $(addsuffix .o, $(subst $(SRC_DIR)/elrond-test,$(BUILD_DIR)/elrond-test,$(LIB_TEST_SRC)))

LIB_CATCH_OBJ = $(BUILD_DIR)/catch.cpp.o

ALL_TEST_SRC = $(shell find $(SRC_DIR) -type f \( -name "*.test.cpp" \))

VPATH = src: $(SRC_DIR)
vpath %.cpp $(SRC_DIR)

.PHONY: all run clean

# *********************************** RULES ************************************

all: $(ALL_TEST_SRC) $(LIB_CATCH_OBJ) $(LIB_TEST)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ $(LSLIBS) $(MACROS) -o $(BUILD_DIR)/all.test $(LDFLAGS) $(LDLIBS)
	./$(BUILD_DIR)/all.test $(a)

run: $(BUILD_DIR)/$(notdir $(basename $(t)))
	./$^ $a

clean:
	rm -rf $(BUILD_DIR)

# Test lib builder
$(LIB_TEST): $(LIB_TEST_OBJ)
	@mkdir -p $(@D)
	$(AR) $(ARFLAGS) $@ $?

# Test lib objects builder
$(BUILD_DIR)/%.cpp.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(MACROS) -c $< -o $@

# Generic test runner builder
$(BUILD_DIR)/%.test: %.test.cpp $(LIB_CATCH_OBJ) $(LIB_TEST)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ $(LSLIBS) $(MACROS) -o $@ $(LDFLAGS) $(LDLIBS)
