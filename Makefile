.PHONY: all build clean docs

all: build

build:
	@echo "Building Sunya Linux components..."
	cd package-manager && cargo build --release
	cd ../init && gcc -O2 -Wall -Wextra -o init init.c
	cd ../shell && gcc -O2 -Wall -o sunya-shell sunya-shell.c
	@echo "Build complete!"

clean:
	cd package-manager && cargo clean
	cd ../init && rm -f init
	cd ../shell && rm -f sunya-shell
	@echo "Clean complete!"

docs:
	@echo "Sunya Linux - Fast, Minimal Linux Distribution"
	@cat ARCHITECTURE.md
