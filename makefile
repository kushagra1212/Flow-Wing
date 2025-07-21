# =============================================================================
# Makefile for FlowWing
# A simple and memorable command-line interface for the CMake build system.
# =============================================================================

# --- Preset Name Variables (to prevent typos) ---
AOT_RELEASE_DEV := aot-release-dev
AOT_DEBUG_DEV   := aot-debug-dev
JIT_RELEASE_DEV := jit-release-dev
JIT_DEBUG_DEV   := jit-debug-dev

TESTS_AOT := tests-aot-dev
TESTS_JIT := tests-jit-dev

AOT_PROD_RELEASE := aot-release
JIT_PROD_RELEASE := jit-release

# --- Directory Variables ---
AOT_DEBUG_DIR   := build/aot-debug-dev
AOT_RELEASE_DIR := build/aot-release-dev
JIT_DEBUG_DIR   := build/jit-debug-dev
JIT_RELEASE_DIR := build/jit-release-dev
TESTS_AOT_DIR   := build/tests-aot-dev
TESTS_JIT_DIR   := build/tests-jit-dev
AOT_PROD_DIR    := build/aot-release
JIT_PROD_DIR    := build/jit-release

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


# To disable status messages, run: make SILENT=1 <target>
# By default, SILENT is not 1, so messages are shown.
ifeq ($(SILENT), 1)
  # In silent mode, ECHO_MSG does nothing. '@:' is a silent, no-op command.
  ECHO_MSG = @:
else
  # In normal mode, ECHO_MSG is an alias for $(ECHO_MSG).
  ECHO_MSG = @echo 
endif

# --- Phony Targets (Commands that are not files) ---
.PHONY: all build build-aot build-aot-release build-jit test test-aot test-jit package package-aot package-jit clean help run run-aot run-aot-release run-jit run-jit-release

# --- Default Command ---
all: build

# --- Help Command ---
help:
	$(ECHO_MSG) ""
	$(ECHO_MSG) "Usage: make <target> [FILE=<path/to/your.fg>]"
	$(ECHO_MSG) "-----------------------------------------------------------------"
	$(ECHO_MSG) "Primary Development Targets:"
	$(ECHO_MSG) "  build               Builds the AOT debug version (default)."
	$(ECHO_MSG) "  build-aot           Builds the AOT debug version."
	$(ECHO_MSG) "  build-aot-release   Builds the AOT release version."
	$(ECHO_MSG) "  build-jit           Builds the JIT debug version."
	$(ECHO_MSG) ""
	$(ECHO_MSG) "Local Running Targets (for scratch files):"
	$(ECHO_MSG) "  run                 Compile & run a .fg file with the AOT Debug compiler."
	$(ECHO_MSG) "  run-aot             Same as 'run'."
	$(ECHO_MSG) "  run-aot-release     Compile & run a .fg file with the AOT Release compiler."
	$(ECHO_MSG) "  run-jit             Run a .fg file with the JIT Debug interpreter."
	$(ECHO_MSG) "                      Example: make run FILE=my_tests/feature.fg"
	$(ECHO_MSG) ""
	$(ECHO_MSG) "Testing Targets:"
	$(ECHO_MSG) "  test                Run all AOT tests."
	$(ECHO_MSG) "  test-aot            Configure, build, and run the AOT tests."
	$(ECHO_MSG) "  test-jit            Configure, build, and run the JIT tests."
	$(ECHO_MSG) "                      Example: make test-aot FILTER=ParserTests.*"
	$(ECHO_MSG) ""
	$(ECHO_MSG) "Packaging Targets (for distribution):"
	$(ECHO_MSG) "  package             Create the final AOT release package."
	$(ECHO_MSG) "  package-aot         Create the final AOT release package."
	$(ECHO_MSG) "  package-jit         Create the final JIT release package."
	$(ECHO_MSG) ""
	$(ECHO_MSG) "Utility Targets:"
	$(ECHO_MSG) "  clean               Deletes the entire 'build' and 'run_output' directories."
	$(ECHO_MSG) "Options:"
	$(ECHO_MSG) "  FILE=<path>         Sets the .fg file for 'run' targets."
	$(ECHO_MSG) "  FILTER=<pattern>    Sets the GTest filter for 'test' targets."
	$(ECHO_MSG) "  SILENT=1            Suppresses build status messages for a cleaner log."
	@echo ""
	$(ECHO_MSG) "-----------------------------------------------------------------"

# --- Build Targets ---
build: build-aot
build-aot: $(AOT_DEBUG_DIR)/.configured
	$(ECHO_MSG) "--> Building AOT Debug (Dev)..."
	@cmake --build --preset $(AOT_DEBUG_DEV)
build-aot-release: $(AOT_RELEASE_DIR)/.configured
	$(ECHO_MSG) "--> Building AOT Release (Dev)..."
	@cmake --build --preset $(AOT_RELEASE_DEV)
build-jit: $(JIT_DEBUG_DIR)/.configured
	$(ECHO_MSG) "--> Building JIT Debug (Dev)..."
	@cmake --build --preset $(JIT_DEBUG_DEV)
build-jit-release: $(JIT_RELEASE_DIR)/.configured
	$(ECHO_MSG) "--> Building JIT Release (Dev)..."
	@cmake --build --preset $(JIT_RELEASE_DEV)
build-test-jit: $(TESTS_JIT_DIR)/.configured
	$(ECHO_MSG) "--> Building JIT tests (Dev)..."
	@cmake --build --preset $(TESTS_JIT)
build-test-aot: $(TESTS_AOT_DIR)/.configured
	$(ECHO_MSG) "--> Building AOT tests (Dev)..."
	@cmake --build --preset $(TESTS_AOT)


# --- NEW! Local Development & Running Targets ---
run: run-aot

run-aot: build-aot
	@mkdir -p $(RUN_OUT_DIR)
	$(ECHO_MSG) "--> Compiling $(FILE) with AOT Debug compiler..."
	@$(AOT_DEBUG_DIR)/FlowWing $(FILE) -o $(RUN_OUT_EXE)
	$(ECHO_MSG) "--> Executing ./$(RUN_OUT_EXE)..."
	$(ECHO_MSG) "---------------------------------"
	@./$(RUN_OUT_EXE)

run-aot-release: build-aot-release
	@mkdir -p $(RUN_OUT_DIR)
	$(ECHO_MSG) "--> Compiling $(FILE) with AOT Release compiler..."
	@$(AOT_RELEASE_DIR)/FlowWing $(FILE) -o $(RUN_OUT_EXE)
	$(ECHO_MSG) "--> Executing ./$(RUN_OUT_EXE)..."
	$(ECHO_MSG) "---------------------------------"
	@./$(RUN_OUT_EXE)

run-jit: build-jit
	$(ECHO_MSG) "--> Interpreting $(FILE) with JIT Debug compiler..."
	$(ECHO_MSG) "---------------------------------"
	@$(JIT_DEBUG_DIR)/FlowWing $(FILE)

run-jit-release: build-jit-release
	$(ECHO_MSG) "--> Interpreting $(FILE) with JIT Release compiler..."
	$(ECHO_MSG) "---------------------------------"
	@$(JIT_RELEASE_DIR)/FlowWing $(FILE)


# --- Test Targets ---
test: test-aot
test-aot: $(TESTS_AOT_DIR)/.configured
	$(ECHO_MSG) "--> Building and running AOT tests... (Filter: $(FILTER))"
	@cmake --build --preset $(TESTS_AOT)
	@GTEST_FILTER=$(FILTER) ctest --preset $(TESTS_AOT)
test-jit: $(TESTS_JIT_DIR)/.configured
	$(ECHO_MSG) "--> Building and running JIT tests... (Filter: $(FILTER))"
	@cmake --build --preset $(TESTS_JIT)
	@GTEST_FILTER=$(FILTER) ctest --preset $(TESTS_JIT)


# --- Packaging Targets ---
package: package-aot
package-aot: $(AOT_PROD_DIR)/.configured
	$(ECHO_MSG) "--> Building final AOT release..."
	@cmake --build --preset $(AOT_PROD_RELEASE)
	$(ECHO_MSG) "--> Creating package in $(AOT_PROD_DIR)/..."
	@cd $(AOT_PROD_DIR) && cpack
package-jit: $(JIT_PROD_DIR)/.configured
	$(ECHO_MSG) "--> Building final JIT release..."
	@cmake --build --preset $(JIT_PROD_RELEASE)
	$(ECHO_MSG) "--> Creating package in $(JIT_PROD_DIR)/..."
	@cd $(JIT_PROD_DIR) && cpack


# --- Configuration Stamp Files ---
$(AOT_DEBUG_DIR)/.configured:
	$(ECHO_MSG) "--> Configuring AOT Debug (Dev)..."
	@cmake --preset $(AOT_DEBUG_DEV) && touch $@
# ... (all other stamp file rules are the same) ...
$(AOT_RELEASE_DIR)/.configured:
	$(ECHO_MSG) "--> Configuring AOT Release (Dev)..."
	@cmake --preset $(AOT_RELEASE_DEV) && touch $@
$(JIT_DEBUG_DIR)/.configured:
	$(ECHO_MSG) "--> Configuring JIT Debug (Dev)..."
	@cmake --preset $(JIT_DEBUG_DEV) && touch $@
$(JIT_RELEASE_DIR)/.configured:
	$(ECHO_MSG) "--> Configuring JIT Release (Dev)..."
	@cmake --preset $(JIT_RELEASE_DEV) && touch $@
$(TESTS_AOT_DIR)/.configured:
	$(ECHO_MSG) "--> Configuring AOT tests..."
	@cmake --preset $(TESTS_AOT) && touch $@
$(TESTS_JIT_DIR)/.configured:
	$(ECHO_MSG) "--> Configuring JIT tests..."
	@cmake --preset $(TESTS_JIT) && touch $@
$(AOT_PROD_DIR)/.configured:
	$(ECHO_MSG) "--> Configuring final AOT release..."
	@cmake --preset $(AOT_PROD_RELEASE) && touch $@
$(JIT_PROD_DIR)/.configured:
	$(ECHO_MSG) "--> Configuring final JIT release..."
	@cmake --preset $(JIT_PROD_RELEASE) && touch $@


# --- Utility Targets ---
clean:
	$(ECHO_MSG) "--> Deleting the build and bin directories..."
	@rm -rf build bin