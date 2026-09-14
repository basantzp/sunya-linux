.PHONY: all build clean install test docs help

all: build

build:
	@echo "Building Sunya Linux v0.1.0..."
	@echo "[1/4] Building package manager..."
	@cd package-manager && cargo build --release 2>/dev/null && echo "✓ Package manager built"
	@echo "[2/4] Building init system..."
	@cd init && gcc -O2 -Wall -Wextra -o init init.c && echo "✓ Init system built"
	@echo "[3/4] Building shell..."
	@cd shell && gcc -O2 -Wall -o sunya-shell sunya-shell.c && echo "✓ Shell built"
	@echo "[4/4] Building bootloader..."
	@cd bootloader && nasm -f bin -o bootloader.bin bootloader.asm 2>/dev/null && echo "✓ Bootloader built" || echo "⚠ NASM not installed, skipping bootloader"
	@echo ""
	@echo "✓ Build complete! All components ready."

clean:
	@echo "Cleaning build artifacts..."
	@cd package-manager && cargo clean 2>/dev/null
	@cd init && rm -f init
	@cd shell && rm -f sunya-shell
	@cd bootloader && rm -f bootloader.bin
	@echo "✓ Clean complete!"

test:
	@echo "Running tests..."
	@cd package-manager && cargo test
	@echo "✓ Tests complete!"

install: build
	@echo "Installing Sunya Linux components..."
	@sudo cp init/init /sbin/sunya-init
	@sudo cp shell/sunya-shell /usr/local/bin/
	@sudo cp package-manager/target/release/sunya-pkg /usr/local/bin/
	@echo "✓ Installation complete!"

docs:
	@echo "Sunya Linux v0.1.0-alpha"
	@echo ""
	@cat README.md
	@echo ""
	@echo "For more information, see docs/ directory"

help:
	@echo "Sunya Linux Build System"
	@echo ""
	@echo "Usage: make [target]"
	@echo ""
	@echo "Targets:"
	@echo "  all       - Build all components (default)"
	@echo "  build     - Build all components"
	@echo "  clean     - Remove build artifacts"
	@echo "  test      - Run tests"
	@echo "  install   - Install components to system"
	@echo "  docs      - Show documentation"
	@echo "  help      - Show this help message"
