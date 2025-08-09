# =============================================================================
# Makefile for FlowWing
# A simple and memorable command-line interface for the CMake build system.
# =============================================================================

#! ----- Dependencies -----

#? Dependency Presets
DEPS_INSTALL_PRESET ?= deps-install-debug

#? Dependency Stamps
STAMPS_DIR := .fw_dependencies/stamps

#? Dependency Directories
DEBUG_DEPS_DIR := $(STAMPS_DIR)
RELEASE_DEPS_DIR := $(STAMPS_DIR)

#! ----- SDK -----

#? SDK Directory
SDK_DIR := build/sdk
TEST_SDK_DIR := build/test-sdk

#! ----- AOT -----

#? AOT Presets
AOT_DEBUG_PRESET := aot-debug
AOT_RELEASE_PRESET := aot-release

#? AOT Directories
AOT_DEBUG_DIR   := build/$(AOT_DEBUG_PRESET)
AOT_RELEASE_DIR := build/$(AOT_RELEASE_PRESET)

#? Test AOT Presets
TESTS_AOT_PRESET := test-aot

#? Test AOT Directories
TESTS_AOT_DIR := build/$(TESTS_AOT_PRESET)

#! ----- JIT -----

#? JIT Presets
JIT_DEBUG_PRESET := jit-debug
JIT_RELEASE_PRESET := jit-release

#? JIT Directories
JIT_DEBUG_DIR   := build/$(JIT_DEBUG_PRESET)
JIT_RELEASE_DIR := build/$(JIT_RELEASE_PRESET)


#? Test JIT Presets
TESTS_JIT_PRESET := test-jit

#? Test JIT Directories
TESTS_JIT_DIR := build/$(TESTS_JIT_PRESET)
#



# --- Local Running Variables ---
# The FlowWing source file to compile. Can be overridden from the command line.
FILE ?= 

# The filter pattern to pass to GTest. Defaults to '*' (all tests).
FILTER ?= *
# The directory where compiled scratch files will go.
RUN_OUT_DIR := build/bin
# The name of the output executable, derived from the input FILE.
RUN_OUT_NAME := $(basename $(notdir $(FILE)))
RUN_OUT_EXE := $(RUN_OUT_DIR)/$(RUN_OUT_NAME)

# Determine the number of CPU cores for parallel builds
ifeq ($(OS),Windows_NT)
    NPROC := $(NUMBER_OF_PROCESSORS)
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        NPROC := $(shell nproc)
    endif
    ifeq ($(UNAME_S),Darwin)
        NPROC := $(shell sysctl -n hw.ncpu)
    endif
endif
# Set the jobs flag, defaulting to all cores. Can be overridden.
JOBS ?= -j$(NPROC)

SILENT_CMD :=

# To disable status messages, run: make SILENT=1 <target>
# By default, SILENT is not 1, so messages are shown.
ifeq ($(SILENT), 1)
  # In silent mode, ECHO_MSG does nothing. '@:' is a silent, no-op command.
  ECHO_MSG = @:
  SILENT_CMD := > /dev/null 2>&1
else
  # In normal mode, ECHO_MSG is an alias for $(ECHO_MSG).
  ECHO_MSG = @echo 
endif


#! --- Help Command ---
help:
	@echo ""
	@echo "FlowWing Compiler Build System"
	@echo ""
	@echo "Usage: make <target> [OPTIONS...]"
	@echo ""
	@echo "  Primary Targets:"
	@echo "    build-aot-debug          Build the AOT compiler in Debug mode (default development build)."
	@echo "    build-aot-release        Build the AOT compiler in Release mode."
	@echo "    build-jit-debug          Build the JIT compiler in Debug mode."
	@echo "    build-jit-release        Build the JIT compiler in Release mode."
	@echo ""
	@echo "  Run Local Files:"
	@echo "    run-aot-debug            Compile and run a .fg file using the AOT Debug compiler."
	@echo "    run-aot-release          Compile and run a .fg file using the AOT Release compiler."
	@echo "    run-jit-debug            Interpret and run a .fg file using the JIT Debug compiler."
	@echo "    run-jit-release          Interpret and run a .fg file using the JIT Release compiler."
	@echo "    (Example: make run-aot-debug FILE=path/to/your.fg)"
	@echo ""
	@echo "  Testing:"
	@echo "    test-aot                 Build and run all tests in AOT mode."
	@echo "    test-jit                 Build and run all tests in JIT mode."
	@echo "    (Example: make test-aot FILTER=MyTestSuite.*)"
	@echo ""
	@echo "  Dependency Management:"
	@echo "    deps-install-debug       Download and build all third-party dependencies (Debug)."
	@echo "    deps-install-release     Download and build all third-party dependencies (Release)."
	@echo ""
	@echo "  Cleaning:"
	@echo "    clean                    Delete all build and binary output directories."
	@echo "    clean-all                Delete all build artifacts AND downloaded dependencies."
	@echo ""
	@echo "  Options:"
	@echo "    FILE=<path>              Required for 'run-*' targets. Specifies the .fg file to execute."
	@echo "    FILTER=<pattern>         Optional for 'test-*' targets. Filters which tests to run (e.g., 'Parser*')."
	@echo "    JOBS=-j<N>               Sets the number of parallel build jobs (default: all available cores)."
	@echo "    SILENT=1                 Suppress build and configuration messages for a clean output."
	@echo ""

#! ----- Dependencies -----

#? Configured Dependencies 
$(DEBUG_DEPS_DIR)/.configured-debug:
	$(ECHO_MSG) "--> Configuring dependencies (Debug)..."
	@cd cmake/deps_builder && cmake --preset deps-install-debug  $(SILENT_CMD)

$(RELEASE_DEPS_DIR)/.configured-release:
	$(ECHO_MSG) "--> Configuring dependencies (Release)..."
	@cd cmake/deps_builder && cmake --preset deps-install-release  $(SILENT_CMD)
	

#? Install dependencies 
$(DEBUG_DEPS_DIR)/.installed-debug: $(DEBUG_DEPS_DIR)/.configured-debug
	$(ECHO_MSG) "--> Installing dependencies (Debug)..."
	@mkdir -p $(STAMPS_DIR)
	@cd cmake/deps_builder && cmake --build --preset deps-install-debug -- $(JOBS)  $(SILENT_CMD)
	@touch $(CURDIR)/$(DEBUG_DEPS_DIR)/.installed-debug 
	
$(RELEASE_DEPS_DIR)/.installed-release: $(RELEASE_DEPS_DIR)/.configured-release
	$(ECHO_MSG) "--> Installing dependencies (Release)..."
	@mkdir -p $(STAMPS_DIR)
	@cd cmake/deps_builder && cmake --build --preset deps-install-release -- $(JOBS)  $(SILENT_CMD)
	@touch $(CURDIR)/$(RELEASE_DEPS_DIR)/.installed-release


#? Dependencies Aliases
.PHONY: deps-install-debug deps-install-release
deps-install-debug: $(DEBUG_DEPS_DIR)/.installed-debug
deps-install-release: $(RELEASE_DEPS_DIR)/.installed-release



#! ----- JIT -----

#? Configured JIT

$(JIT_DEBUG_DIR)/.configured: deps-install-debug
	$(ECHO_MSG) "--> Configuring JIT (Debug)..."
	@cmake --preset $(JIT_DEBUG_PRESET)  $(SILENT_CMD) && touch $@

$(JIT_RELEASE_DIR)/.configured: deps-install-release
	$(ECHO_MSG) "--> Configuring JIT (Release)..."
	@cmake --preset $(JIT_RELEASE_PRESET)  $(SILENT_CMD) && touch $@



#? Build JIT

.PHONY: build-jit-debug build-jit-release

build-jit-debug: $(JIT_DEBUG_DIR)/.configured
	$(ECHO_MSG) "--> Building JIT (Debug)..."
	@cmake --build --preset $(JIT_DEBUG_PRESET) -- $(JOBS) $(SILENT_CMD)
	$(ECHO_MSG) "--> Staging SDK to $(SDK_DIR)..."
	@cmake --install $(JIT_DEBUG_DIR) --prefix $(SDK_DIR) $(SILENT_CMD)
	@mkdir -p $(RUN_OUT_DIR) 
	$(ECHO_MSG) "--> Compiling $(FILE) with JIT (Debug)..." 
	@chmod +x $(SDK_DIR)/bin/FlowWing

build-jit-release: $(JIT_RELEASE_DIR)/.configured
	$(ECHO_MSG) "--> Building JIT (Release)..."
	@cmake --build --preset $(JIT_RELEASE_PRESET) -- $(JOBS) $(SILENT_CMD)
	$(ECHO_MSG) "--> Staging SDK to $(SDK_DIR)..."
	@cmake --install $(JIT_RELEASE_DIR) --prefix $(SDK_DIR) $(SILENT_CMD)
	@mkdir -p $(RUN_OUT_DIR)
	$(ECHO_MSG) "--> Compiling $(FILE) with JIT (Release)..."
	@chmod +x $(SDK_DIR)/bin/FlowWing



#? Run JIT

.PHONY: run-jit-debug run-jit-release

run-jit-debug: build-jit-debug
	@$(SDK_DIR)/bin/FlowWing $(FILE)

run-jit-release: build-jit-release
	@$(SDK_DIR)/bin/FlowWing $(FILE) 


#! ----- JIT Tests -----

#? Configured JIT Tests
$(TESTS_JIT_DIR)/.configured: deps-install-release
	$(ECHO_MSG) "--> Configuring JIT tests..."
	@cmake --preset $(TESTS_JIT_PRESET) && touch $@

.PHONY: test-jit

#? Build and Run JIT Tests
test-jit: $(TESTS_JIT_DIR)/.configured
	$(ECHO_MSG) "--> Building and running JIT tests... (Filter: $(FILTER))"
	@cmake --build --preset $(TESTS_JIT_PRESET)
    
	$(ECHO_MSG) "--> Staging SDK for tests..."
	@cmake --install $(TESTS_JIT_DIR) --prefix $(TEST_SDK_DIR)
	
	@GTEST_FILTER=$(FILTER) ctest --preset $(TESTS_JIT_PRESET)


#! ----- AOT -----

#? Configured AOT

$(AOT_DEBUG_DIR)/.configured: deps-install-debug
	$(ECHO_MSG) "--> Configuring AOT (Debug)..."
	@cmake --preset $(AOT_DEBUG_PRESET)  $(SILENT_CMD) && touch $@

$(AOT_RELEASE_DIR)/.configured: deps-install-release
	$(ECHO_MSG) "--> Configuring AOT (Release)..."
	@cmake --preset $(AOT_RELEASE_PRESET)  $(SILENT_CMD) && touch $@


#? Build AOT

.PHONY: build-aot-debug build-aot-release

build-aot-debug: $(AOT_DEBUG_DIR)/.configured
	$(ECHO_MSG) "--> Building AOT (Debug)..."
	@cmake --build --preset $(AOT_DEBUG_PRESET) -- $(JOBS) $(SILENT_CMD)
	$(ECHO_MSG) "--> Staging SDK to $(SDK_DIR)..."
	@cmake --install $(AOT_DEBUG_DIR) --prefix $(SDK_DIR) $(SILENT_CMD)
	@mkdir -p $(RUN_OUT_DIR) 
	$(ECHO_MSG) "--> Compiling $(FILE) with AOT (Debug)..." 
	@chmod +x $(SDK_DIR)/bin/FlowWing

build-aot-release: $(AOT_RELEASE_DIR)/.configured
	$(ECHO_MSG) "--> Building AOT (Release)..."
	@cmake --build --preset $(AOT_RELEASE_PRESET) -- $(JOBS) $(SILENT_CMD)
	$(ECHO_MSG) "--> Staging SDK to $(SDK_DIR)..."
	@cmake --install $(AOT_RELEASE_DIR) --prefix $(SDK_DIR) $(SILENT_CMD)
	@mkdir -p $(RUN_OUT_DIR)
	$(ECHO_MSG) "--> Compiling $(FILE) with AOT (Release)..."
	@chmod +x $(SDK_DIR)/bin/FlowWing



#? Run AOT

.PHONY: run-aot-debug run-aot-release

run-aot-debug: build-aot-debug
	@$(SDK_DIR)/bin/FlowWing $(FILE) -o $(RUN_OUT_EXE)
	$(ECHO_MSG) "--> Executing ./$(RUN_OUT_EXE)..."
	$(ECHO_MSG) "---------------------------------"
	@./$(RUN_OUT_EXE)

run-aot-release: build-aot-release
	@$(SDK_DIR)/bin/FlowWing $(FILE) -o $(RUN_OUT_EXE)
	$(ECHO_MSG) "--> Executing ./$(RUN_OUT_EXE)..."
	$(ECHO_MSG) "---------------------------------"
	@./$(RUN_OUT_EXE)

#! ----- AOT Tests -----

#? Configured AOT Tests
$(TESTS_AOT_DIR)/.configured: deps-install-release
	$(ECHO_MSG) "--> Configuring AOT tests..."
	@cmake --preset $(TESTS_AOT_PRESET) && touch $@

.PHONY: test-aot

#? Build and Run AOT Tests
test-aot: $(TESTS_AOT_DIR)/.configured
	$(ECHO_MSG) "--> Building and running AOT tests... (Filter: $(FILTER))"
	@cmake --build --preset $(TESTS_AOT_PRESET)
    
	$(ECHO_MSG) "--> Staging SDK for tests..."
	@cmake --install $(TESTS_AOT_DIR) --prefix $(TEST_SDK_DIR)
	
	@GTEST_FILTER=$(FILTER) ctest --preset $(TESTS_AOT_PRESET)





#! ----- Clean -----

.PHONY: clean clean-debug clean-release clean-all

#? Clean Targets (Only Build Artifacts)
clean:
	$(ECHO_MSG) "--> Deleting the build and bin directories..."
	@rm -rf build bin

#? Clean Debug Targets (All Build Artifacts, Including Dependencies)
clean-debug:
	$(ECHO_MSG) "--> Deleting ALL build artifacts, including downloaded dependencies..."
	@rm -rf build bin $(DEBUG_DEPS_DIR)

#? Clean Release Targets (All Build Artifacts, Including Dependencies)
clean-release:
	$(ECHO_MSG) "--> Deleting ALL build artifacts, including downloaded dependencies..."
	@rm -rf build bin $(RELEASE_DEPS_DIR)

#? Clean All Targets (All Build Artifacts, Including Dependencies)
clean-all:
	$(ECHO_MSG) "--> Deleting ALL build artifacts, including downloaded dependencies..."
	@read -p "Are you sure? [y/N]: " -n 1 -r; \
	echo; \
	case "$$REPLY" in \
	  [yY]) \
	    echo "--> Deleting files..."; \
	    rm -rf build bin $(DEBUG_DEPS_DIR) $(RELEASE_DEPS_DIR) ;; \
	  *) \
	    echo "--> Aborted.";; \
	esac



# -- Debug
run-jit-with-lldb: build-jit
	$(ECHO_MSG) "--> Interpreting $(FILE) with JIT Debug compiler..."
	$(ECHO_MSG) "---------------------------------"
	@lldb $(JIT_DEBUG_DIR)/FlowWing $(FILE) 








