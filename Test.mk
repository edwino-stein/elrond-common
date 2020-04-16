# General settings
include Config.mk

BUILD_DIR := $(BUILD_DIR)/$(TEST_DIR)

INCLUDES := $(addprefix -I, $(INCLUDES) $(i))
MACROS := $(addprefix -D, $(MACROS) $(m))

LDLIBS = $(addprefix -l, $(ld))
LSLIBS = $(l)

LIB_CATCH_OBJ = $(BUILD_DIR)/catch.cpp.o
EXTERNAL_MOD = $(BUILD_DIR)/external-module.$(DYNAMIC_LIB_EXT)
EXTERNAL_LDFLAGS = $(LDFLAGS) -Idist

ifeq ($(TARGET_OS), Linux)
    EXTERNAL_LDFLAGS := -shared -fPIC $(EXTERNAL_LDFLAGS)
endif

CXXFLAGS += $(INCLUDES) $(MACROS)
LDFLAGS += $(INCLUDES) $(MACROS)

VPATH = src: $(TEST_DIR)
vpath %.cpp $(TEST_DIR)

.PHONY: all run

# *********************************** RULES ************************************

all: $(BUILD_DIR)/all.test
	./$^ $a

run: $(BUILD_DIR)/$(notdir $(basename $(t)))
	./$^ $a

# All test runner builder
$(BUILD_DIR)/all.test: $(ALL_TEST_SRC) $(LIB_CATCH_OBJ) $(EXTERNAL_MOD)
	@mkdir -p $(@D)
	$(CXX) $(LDFLAGS) $(ALL_TEST_SRC) $(LIB_CATCH_OBJ) $(LSLIBS) -o $(BUILD_DIR)/all.test $(LDLIBS)

# Generic test runner builder
$(BUILD_DIR)/%.test: %.test.cpp $(LIB_CATCH_OBJ)
	@mkdir -p $(@D)
	$(CXX) $(LDFLAGS) $^ $(LSLIBS) $(MACROS) -o $@  $(LDLIBS)

$(BUILD_DIR)/RuntimeTest.test: RuntimeTest.test.cpp $(LIB_CATCH_OBJ) $(EXTERNAL_MOD)
	@mkdir -p $(@D)
	$(CXX) $(LDFLAGS) $< $(LIB_CATCH_OBJ) $(LSLIBS) -o $@  $(LDLIBS)

$(LIB_CATCH_OBJ): catch.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -DCATCH_CONFIG_MAIN $< -o $@

$(EXTERNAL_MOD): ExternalMod.cpp
	@mkdir -p $(@D)
	$(CXX) $(EXTERNAL_LDFLAGS) $< -o $@
