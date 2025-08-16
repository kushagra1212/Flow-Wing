# =============================================================================
# Makefile for FlowWing (Cross-Platform)
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

# --- Local Running Variables ---
# The FlowWing source file to compile. Can be overridden from the command line.
FILE ?= 

# The filter pattern to pass to GTest. Defaults to '*' (all tests).
FILTER ?= .*
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

# --- Cross-Platform Command Abstractions ---
# This block defines variables for common shell commands, providing a
# compatible version for both Windows (cmd.exe) and POSIX (bash).
ifeq ($(OS),Windows_NT)
    # Windows commands
    MKDIR_P      = if not exist $(subst /,\,$(1)) mkdir $(subst /,\,$(1))
    TOUCH        = type nul > $(subst /,\,$(1))
    RM_RF        = if exist $(subst /,\,$(1)) rmdir /s /q $(subst /,\,$(1))
    CHMOD_X      = @REM chmod is not applicable on Windows
    CD_AND_EXEC  = cd /d $(subst /,\,$(1)) && $(2)
    RUN_EXE      = $(subst /,\,$(1))
else
    # POSIX commands (Linux, macOS)
    MKDIR_P      = mkdir -p $(1)
    TOUCH        = touch $(1)
    RM_RF        = rm -rf $(1)
    CHMOD_X      = chmod +x $(1)
    CD_AND_EXEC  = cd $(1) && $(2)
    RUN_EXE      = ./$(1)
endif

# To disable status messages, run: make SILENT=1 <target>
ifeq ($(SILENT), 1)
  ECHO_MSG = @:
  # Detect OS for redirection
  ifeq ($(OS),Windows_NT)
    SILENT_CMD := > NUL 2>&1
  else
    SILENT_CMD := > /dev/null 2>&1
  endif
else
  ECHO_MSG = @echo
  SILENT_CMD :=
endif


#! --- Help Command ---
# ... (help section is unchanged, no shell commands) ...
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
	@$(call CD_AND_EXEC, cmake/deps_builder, cmake --preset deps-install-debug $(SILENT_CMD))

$(RELEASE_DEPS_DIR)/.configured-release:
	$(ECHO_MSG) "--> Configuring dependencies (Release)..."
	@$(call CD_AND_EXEC, cmake/deps_builder, cmake --preset deps-install-release $(SILENT_CMD))
	
#? Install dependencies 
$(DEBUG_DEPS_DIR)/.installed-debug: $(DEBUG_DEPS_DIR)/.configured-debug
	$(ECHO_MSG) "--> Installing dependencies (Debug)..."
	@$(call MKDIR_P, $(STAMPS_DIR))
	@$(call CD_AND_EXEC, cmake/deps_builder, cmake --build --preset deps-install-debug -- $(JOBS) $(SILENT_CMD))
	@$(call TOUCH, $(CURDIR)/$(DEBUG_DEPS_DIR)/.installed-debug)
	
$(RELEASE_DEPS_DIR)/.installed-release: $(RELEASE_DEPS_DIR)/.configured-release
	$(ECHO_MSG) "--> Installing dependencies (Release)..."
	@$(call MKDIR_P, $(STAMPS_DIR))
	@$(call CD_AND_EXEC, cmake/deps_builder, cmake --build --preset deps-install-release -- $(JOBS) $(SILENT_CMD))
	@$(call TOUCH, $(CURDIR)/$(RELEASE_DEPS_DIR)/.installed-release)

#? Dependencies Aliases
.PHONY: deps-install-debug deps-install-release
deps-install-debug: $(DEBUG_DEPS_DIR)/.installed-debug
deps-install-release: $(RELEASE_DEPS_DIR)/.installed-release

#! ----- JIT -----

#? Configured JIT
$(JIT_DEBUG_DIR)/.configured: deps-install-debug
	$(ECHO_MSG) "--> Configuring JIT (Debug)..."
	@cmake --preset $(JIT_DEBUG_PRESET)  $(SILENT_CMD) && $(call TOUCH, $@)

$(JIT_RELEASE_DIR)/.configured: deps-install-release
	$(ECHO_MSG) "--> Configuring JIT (Release)..."
	@cmake --preset $(JIT_RELEASE_PRESET)  $(SILENT_CMD) && $(call TOUCH, $@)

#? Build JIT
.PHONY: build-jit-debug build-jit-release
build-jit-debug: $(JIT_DEBUG_DIR)/.configured
	$(ECHO_MSG) "--> Building JIT (Debug)..."
	@cmake --build --preset $(JIT_DEBUG_PRESET) -- $(JOBS) $(SILENT_CMD)
	$(ECHO_MSG) "--> Staging SDK to $(SDK_DIR)..."
	@cmake --install $(JIT_DEBUG_DIR) --prefix $(SDK_DIR) $(SILENT_CMD)
	@$(call MKDIR_P, $(RUN_OUT_DIR))
	@$(call CHMOD_X, $(SDK_DIR)/bin/FlowWing)

build-jit-release: $(JIT_RELEASE_DIR)/.configured
	$(ECHO_MSG) "--> Building JIT (Release)..."
	@cmake --build --preset $(JIT_RELEASE_PRESET) -- $(JOBS) $(SILENT_CMD)
	$(ECHO_MSG) "--> Staging SDK to $(SDK_DIR)..."
	@cmake --install $(JIT_RELEASE_DIR) --prefix $(SDK_DIR) $(SILENT_CMD)
	@$(call MKDIR_P, $(RUN_OUT_DIR))
	@$(call CHMOD_X, $(SDK_DIR)/bin/FlowWing)

#? Run JIT
.PHONY: run-jit-debug run-jit-release
run-jit-debug: build-jit-debug
	$(ECHO_MSG) "--> Compiling $(FILE) with JIT (Debug)..." 
	@$(call RUN_EXE, $(SDK_DIR)/bin/FlowWing) $(FILE)

run-jit-release: build-jit-release
	$(ECHO_MSG) "--> Compiling $(FILE) with JIT (Release)..."
	@$(call RUN_EXE, $(SDK_DIR)/bin/FlowWing) $(FILE)

#! ----- JIT Tests -----

#? Configured JIT Tests
$(TESTS_JIT_DIR)/.configured: deps-install-release
	$(ECHO_MSG) "--> Configuring JIT tests..."
	@cmake --preset $(TESTS_JIT_PRESET) && $(call TOUCH, $@)

.PHONY: test-jit
#? Build and Run JIT Tests
test-jit: $(TESTS_JIT_DIR)/.configured
	$(ECHO_MSG) "--> Building and running JIT tests... (Filter: $(FILTER))"
	@cmake --build --preset $(TESTS_JIT_PRESET)
	$(ECHO_MSG) "--> Staging SDK for tests..."
	@cmake --install $(TESTS_JIT_DIR) --prefix $(TEST_SDK_DIR)
	@ctest --preset $(TESTS_JIT_PRESET)  -R $(FILTER)

#! ----- AOT -----

#? Configured AOT
$(AOT_DEBUG_DIR)/.configured: deps-install-debug
	$(ECHO_MSG) "--> Configuring AOT (Debug)..."
	@cmake --preset $(AOT_DEBUG_PRESET)  $(SILENT_CMD) && $(call TOUCH, $@)

$(AOT_RELEASE_DIR)/.configured: deps-install-release
	$(ECHO_MSG) "--> Configuring AOT (Release)..."
	@cmake --preset $(AOT_RELEASE_PRESET)  $(SILENT_CMD) && $(call TOUCH, $@)

#? Build AOT
.PHONY: build-aot-debug build-aot-release
build-aot-debug: $(AOT_DEBUG_DIR)/.configured
	$(ECHO_MSG) "--> Building AOT (Debug)..."
	@cmake --build --preset $(AOT_DEBUG_PRESET) -- $(JOBS) $(SILENT_CMD)
	$(ECHO_MSG) "--> Staging SDK to $(SDK_DIR)..."
	@cmake --install $(AOT_DEBUG_DIR) --prefix $(SDK_DIR) $(SILENT_CMD)
	@$(call MKDIR_P, $(RUN_OUT_DIR))
	@$(call CHMOD_X, $(SDK_DIR)/bin/FlowWing)

build-aot-release: $(AOT_RELEASE_DIR)/.configured
	$(ECHO_MSG) "--> Building AOT (Release)..."
	@cmake --build --preset $(AOT_RELEASE_PRESET) -- $(JOBS) $(SILENT_CMD)
	$(ECHO_MSG) "--> Staging SDK to $(SDK_DIR)..."
	@cmake --install $(AOT_RELEASE_DIR) --prefix $(SDK_DIR) $(SILENT_CMD)
	@$(call MKDIR_P, $(RUN_OUT_DIR))
	@$(call CHMOD_X, $(SDK_DIR)/bin/FlowWing)

#? Run AOT
.PHONY: run-aot-debug run-aot-release
run-aot-debug: build-aot-debug
	$(ECHO_MSG) "--> Compiling and executing $(FILE) with AOT (Debug)..."
	$(ECHO_MSG) "---------------------------------"
	@$(call RUN_EXE, $(SDK_DIR)/bin/FlowWing) $(FILE) -o $(RUN_OUT_EXE) && $(call RUN_EXE, $(RUN_OUT_EXE))

run-aot-release: build-aot-release
	$(ECHO_MSG) "--> Compiling and executing $(FILE) with AOT (Release)..."
	$(ECHO_MSG) "---------------------------------"
	@$(call RUN_EXE, $(SDK_DIR)/bin/FlowWing) $(FILE) -o $(RUN_OUT_EXE) && $(call RUN_EXE, $(RUN_OUT_EXE))

#! ----- AOT Tests -----

#? Configured AOT Tests
$(TESTS_AOT_DIR)/.configured: deps-install-release
	$(ECHO_MSG) "--> Configuring AOT tests..."
	@cmake --preset $(TESTS_AOT_PRESET) && $(call TOUCH, $@)

.PHONY: test-aot
#? Build and Run AOT Tests
test-aot: $(TESTS_AOT_DIR)/.configured
	$(ECHO_MSG) "--> Building and running AOT tests... (Filter: $(FILTER))"
	@cmake --build --preset $(TESTS_AOT_PRESET)
	$(ECHO_MSG) "--> Staging SDK for tests..."
	@cmake --install $(TESTS_AOT_DIR) --prefix $(TEST_SDK_DIR)
	@ctest --preset $(TESTS_AOT_PRESET)  -R $(FILTER)

#! ----- Clean -----

.PHONY: clean clean-all
#? Clean Targets (Only Build Artifacts)
clean:
	$(ECHO_MSG) "--> Deleting the build, bin..."
	@$(call RM_RF, build)
	@$(call RM_RF, bin)

#? Clean All Targets (All Build Artifacts, Including Dependencies)
clean-all:
	$(ECHO_MSG) "--> Deleting ALL build artifacts, including downloaded dependencies..."
ifeq ($(OS),Windows_NT)
    # No confirmation prompt on Windows for non-interactive shells
	@$(call RM_RF, build)
	@$(call RM_RF, bin)
	@$(call RM_RF, .fw_dependencies)
else
    # Interactive confirmation for POSIX systems
	@read -p "Are you sure? This will delete all dependencies. [y/N]: " -n 1 -r; \
	echo; \
	if [[ $$REPLY =~ ^[Yy]$$ ]]; then \
	    echo "--> Deleting files..."; \
	    $(call RM_RF, build); \
	    $(call RM_RF, bin); \
	    $(call RM_RF, .fw_dependencies); \
	else \
	    echo "--> Aborted."; \
	fi
endif
