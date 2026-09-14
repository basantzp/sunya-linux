# Sunya Linux Architecture

## Core Components
1. **Bootloader** (Assembly) - x86_64 minimal boot
2. **Init System** (C) - PID 1, service manager
3. **Package Manager** (Rust) - sunya-pkg
4. **Shell** (C) - sunya-shell
5. **Kernel** (C) - Linux base

## Design Philosophy
- Simplicity first
- Fast boot and runtime
- Low battery usage
- Developer-friendly
- Open source (GPL-3.0)
