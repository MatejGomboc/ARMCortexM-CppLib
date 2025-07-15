# ARMCortexM-CppLib Testing Makefile
# Provides convenient targets for running the test suite

.PHONY: help install test test-all test-basic test-performance clean setup
.DEFAULT_GOAL := help

# Configuration
PYTHON := python3
PIP := pip3

# Test configurations
BASIC_DEVICES := CM0 CM0plus CM1 CM3
ALL_DEVICES := CM0 CM0plus CM1 CM3 CM4 CM4FP CM33 CM55
COMPILERS := GCC Clang
OPTIMIZATIONS := none balanced speed size

help: ## Show this help message
	@echo "ARMCortexM-CppLib Testing Framework"
	@echo "==================================="
	@echo ""
	@echo "Available targets:"
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | sort | awk 'BEGIN {FS = ":.*?## "}; {printf "  %-20s %s\n", $$1, $$2}'
	@echo ""
	@echo "Examples:"
	@echo "  make setup          # First-time setup"
	@echo "  make test           # Quick test (CM0 with GCC, no optimization)"
	@echo "  make test-basic     # Test basic devices with GCC"
	@echo "  make test-all       # Comprehensive test suite (takes time!)"
	@echo "  make test DEVICE=CM3 COMPILER=Clang OPT=speed"

setup: ## Set up the testing environment (install dependencies and toolchains)
	@echo "Setting up testing environment..."
	$(PIP) install -r requirements.txt
	@echo "Installing ARM toolchains via vcpkg..."
	vcpkg install
	@echo "Setup complete!"

install: setup ## Alias for setup

test: ## Run basic test (CM0, GCC, no optimization)
	@echo "Running basic test..."
	$(PYTHON) build.py lit -d $(or $(DEVICE),CM0) -c $(or $(COMPILER),GCC) -o $(or $(OPT),none)

test-basic: ## Test basic supported devices (CM0, CM0+, CM1, CM3) with GCC
	@echo "Running basic device tests..."
	@for device in $(BASIC_DEVICES); do \
		echo "Testing $$device..."; \
		$(PYTHON) build.py lit -d $$device -c GCC -o none || exit 1; \
	done
	@echo "Basic tests completed successfully!"

test-compilers: ## Test all compilers with CM0
	@echo "Testing all compilers..."
	@for compiler in $(COMPILERS); do \
		echo "Testing $$compiler..."; \
		$(PYTHON) build.py lit -d CM0 -c $$compiler -o none || exit 1; \
	done
	@echo "Compiler tests completed successfully!"

test-optimization: ## Test optimization levels with CM0 and GCC
	@echo "Testing optimization levels..."
	@for opt in $(OPTIMIZATIONS); do \
		echo "Testing optimization: $$opt"; \
		$(PYTHON) build.py lit -d CM0 -c GCC -o $$opt || exit 1; \
	done
	@echo "Optimization tests completed successfully!"

test-performance: ## Run performance and optimization tests
	@echo "Running performance tests..."
	$(PYTHON) build.py lit -d CM0 -d CM3 -c GCC -c Clang -o none -o speed
	@echo "Performance tests completed!"

test-integration: ## Run cross-device integration tests
	@echo "Running integration tests..."
	$(PYTHON) build.py lit -d CM0 -d CM0plus -d CM3 -c GCC -o balanced

test-all: ## Run comprehensive test suite (all devices, compilers, optimizations)
	@echo "Running comprehensive test suite..."
	@echo "Warning: This will take a significant amount of time!"
	@read -p "Continue? [y/N] " confirm && [ "$$confirm" = "y" ] || exit 1
	$(PYTHON) build.py lit $(foreach d,$(ALL_DEVICES),-d $(d)) $(foreach c,$(COMPILERS),-c $(c)) $(foreach o,$(OPTIMIZATIONS),-o $(o))
	@echo "Comprehensive tests completed!"

test-matrix: ## Run a balanced test matrix (reasonable subset for CI)
	@echo "Running balanced test matrix..."
	$(PYTHON) build.py lit -d CM0 -d CM0plus -d CM3 -c GCC -c Clang -o none -o speed

test-cm0: ## Test Cortex-M0 specifically
	$(PYTHON) build.py lit -d CM0 -c GCC -c Clang -o none -o speed

test-cm0plus: ## Test Cortex-M0+ specifically (includes MPU tests)
	$(PYTHON) build.py lit -d CM0plus -c GCC -c Clang -o none -o speed

test-cm3: ## Test Cortex-M3 specifically
	$(PYTHON) build.py lit -d CM3 -c GCC -c Clang -o none -o speed

test-gcc: ## Test with GCC compiler across basic devices
	$(PYTHON) build.py lit $(foreach d,$(BASIC_DEVICES),-d $(d)) -c GCC -o none -o speed

test-clang: ## Test with Clang compiler across basic devices
	$(PYTHON) build.py lit $(foreach d,$(BASIC_DEVICES),-d $(d)) -c Clang -o none -o speed

# Utility targets
clean: ## Clean up test artifacts
	@echo "Cleaning test artifacts..."
	find . -name "*.xml" -delete
	find . -name "*.o" -delete
	find . -name "*.tmp" -delete
	find . -name "__pycache__" -type d -exec rm -rf {} + 2>/dev/null || true
	@echo "Cleanup complete!"

check-env: ## Check if testing environment is properly set up
	@echo "Checking testing environment..."
	@$(PYTHON) -c "import lit.main" 2>/dev/null && echo "✓ lit installed" || echo "✗ lit not found"
	@$(PYTHON) -c "import matrix_runner" 2>/dev/null && echo "✓ matrix-runner installed" || echo "✗ matrix-runner not found"
	@which arm-none-eabi-gcc >/dev/null 2>&1 && echo "✓ GCC found" || echo "✗ GCC not found"
	@which clang >/dev/null 2>&1 && echo "✓ Clang found" || echo "✗ Clang not found"
	@which FileCheck >/dev/null 2>&1 && echo "✓ FileCheck found" || echo "✗ FileCheck not found"

list-tests: ## List all available test files
	@echo "Available test files:"
	@find tests -name "*.cpp" -o -name "*.c" | sort

info: ## Show information about the test framework
	@echo "ARMCortexM-CppLib Testing Framework"
	@echo "=================================="
	@echo ""
	@echo "Framework components:"
	@echo "  • Matrix runner (build.py) - Orchestrates test execution"
	@echo "  • LIT configuration (lit.cfg.py) - Device-specific settings"
	@echo "  • Test suite (tests/) - Comprehensive test coverage"
	@echo "  • CI/CD (.github/workflows/) - Automated testing"
	@echo ""
	@echo "Supported devices: $(BASIC_DEVICES)"
	@echo "Supported compilers: $(COMPILERS)"
	@echo "Optimization levels: $(OPTIMIZATIONS)"
	@echo ""
	@echo "Test categories:"
	@echo "  • Assembly verification - Ensures correct instruction generation"
	@echo "  • Functionality tests - Verifies API behavior"
	@echo "  • Performance tests - Checks optimization effectiveness"
	@echo "  • Integration tests - Cross-device compatibility"

# Development targets
dev-test: ## Quick development test (CM0, GCC, no optimization, verbose)
	$(PYTHON) build.py lit -d CM0 -c GCC -o none --verbose

debug-test: ## Debug a specific test file
	@echo "Usage: make debug-test TEST=tests/cortexm0/special_regs_test.cpp"
	@if [ -z "$(TEST)" ]; then \
		echo "Error: TEST variable not set"; \
		echo "Example: make debug-test TEST=tests/cortexm0/special_regs_test.cpp"; \
		exit 1; \
	fi
	lit -v "$(TEST)"

validate: ## Validate test files for common issues
	@echo "Validating test files..."
	@for file in $$(find tests -name "*.cpp" -o -name "*.c"); do \
		echo "Checking $$file..."; \
		grep -q "CHECK-LABEL:" "$$file" || echo "Warning: $$file missing CHECK-LABEL"; \
		grep -q "REQUIRES:" "$$file" || echo "Warning: $$file missing REQUIRES"; \
		grep -q "RUN:" "$$file" || echo "Warning: $$file missing RUN"; \
	done
	@echo "Validation complete!"

# Documentation targets
docs: ## Generate documentation for the test framework
	@echo "Generating test documentation..."
	@echo "# Test Coverage Report" > test-coverage.md
	@echo "" >> test-coverage.md
	@echo "Generated on: $$(date)" >> test-coverage.md
	@echo "" >> test-coverage.md
	@echo "## Test Files" >> test-coverage.md
	@for file in $$(find tests -name "*.cpp" -o -name "*.c" | sort); do \
		echo "- $$file" >> test-coverage.md; \
	done
	@echo "" >> test-coverage.md
	@echo "## Device Support" >> test-coverage.md
	@for device in $(BASIC_DEVICES); do \
		count=$$(find tests -name "*$$device*" | wc -l); \
		echo "- $$device: $$count test files" >> test-coverage.md; \
	done
	@echo "Documentation generated: test-coverage.md"

# CI simulation
ci-basic: ## Simulate basic CI testing locally
	@echo "Simulating basic CI pipeline..."
	$(MAKE) test-basic
	$(MAKE) test-compilers
	@echo "Basic CI simulation complete!"

ci-full: ## Simulate full CI testing locally
	@echo "Simulating full CI pipeline..."
	$(MAKE) test-matrix
	$(MAKE) test-performance
	@echo "Full CI simulation complete!"

# Quick shortcuts
quick: test ## Quick alias for basic test
fast: test-basic ## Fast alias for basic device tests
full: test-all ## Full alias for comprehensive tests
matrix: test-matrix ## Matrix alias for balanced test matrix
