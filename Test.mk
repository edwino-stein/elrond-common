# General settings
include Config.mk

TEST_DIR = test
BUILD_DIR := $(BUILD_DIR)/$(TEST_DIR)

INCLUDES := $(addprefix -I, $(INCLUDES) $(i))
MACROS := $(addprefix -D, $(MACROS) $(m))

LDLIBS = $(addprefix -l, pthread $(ld))
LSLIBS = $(l)

ALL_TEST_SRC = $(shell find $(TEST_DIR) -type f \( -name "*.test.cpp" \))
LIB_CATCH_OBJ = $(BUILD_DIR)/catch.cpp.o

VPATH = src: $(TEST_DIR)
vpath %.cpp $(TEST_DIR)

CXXFLAGS += $(INCLUDES) $(MACROS)
LDFLAGS += $(INCLUDES) $(MACROS)

.PHONY: all run clean

# *********************************** RULES ************************************

all: $(ALL_TEST_SRC) $(LIB_CATCH_OBJ)
	@mkdir -p $(@D)
	$(CXX) $(LDFLAGS) $^ $(LSLIBS) $(MACROS) -o $(BUILD_DIR)/all.test $(LDLIBS)
	./$(BUILD_DIR)/all.test $(a)
	@rm -f $(BUILD_DIR)/all.test

run: $(BUILD_DIR)/$(notdir $(basename $(t)))
	./$^ $a
	@rm -f $^

# Generic test runner builder
$(BUILD_DIR)/%.test: %.test.cpp $(LIB_CATCH_OBJ)
	@mkdir -p $(@D)
	$(CXX) $(LDFLAGS) $^ $(LSLIBS) $(MACROS) -o $@  $(LDLIBS)

$(LIB_CATCH_OBJ): catch.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $< -o $@
