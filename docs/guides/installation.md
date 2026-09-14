# Sunya Linux Installation Guide

## Prerequisites
- 2GB RAM minimum
- 10GB disk space
- x86_64 processor
- UEFI or BIOS firmware

## Installation Steps

### 1. Download ISO
```bash
wget https://github.com/basantpz/sunya-linux/releases/download/v0.1.0/sunya-linux-0.1.0.iso


sudo dd if=sunya-linux-0.1.0.iso of=/dev/sdX bs=4M status=progress
sunya> sunya-pkg update
sunya> sunya-pkg install base-system
make build
cd package-manager && cargo build --release
cd init && gcc -O2 -Wall -Wextra -o init init.c
cd shell && gcc -O2 -Wall -o sunya-shell sunya-shell.c
cd package-manager && cargo test
cd init && ./init --help
cd shell && ./sunya-shell
cargo fmt
cargo clippy
cat > ~/sunya-linux/docs/api/reference.md <<'EOF'
# Sunya Linux API Reference

## Package Manager (sunya-pkg)

### Installation
```bash
sunya-pkg install <package-name>
sunya-pkg install package1 package2 package3
sunya-pkg remove <package-name>
sunya-pkg update
sunya-pkg search <search-term>
sunya-pkg list
void start_service(const char *name, const char *path);
void stop_service(const char *name);
void restart_service(const char *name);
void mount_essential(void);
void unmount_all(void);
sunya> help
sunya> version
sunya> exit
sunya> /usr/bin/program arg1 arg2
sunya> export VAR=value
sunya> echo $VAR
mkdir -p ~/.github/workflows 2>/dev/null || true
cat > ~/sunya-linux/.gitignore <<'EOF'
# Build artifacts
target/
*.o
*.a
*.so
*.dylib
init
sunya-shell

# IDE
.vscode/
.idea/
*.swp
*.swo
*~

# OS
.DS_Store
Thumbs.db

# Cargo
Cargo.lock
*.rlib

# Logs
*.log
