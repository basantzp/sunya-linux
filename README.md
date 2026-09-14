# Sunya Linux

**Sunya Linux** is a lightweight, fast, and open-source Linux distribution designed for performance, simplicity, and developer productivity. Built with modern languages (Rust, C) and minimal bloat.

## Key Features

- **Fast Boot**: < 2 seconds to ready state
- **Low Resource Usage**: Minimal RAM and CPU requirements
- **Battery Efficient**: Optimized for laptops and mobile devices
- **Developer Friendly**: Built by developers, for developers
- **Open Source**: 100% GPL-3.0 licensed
- **Modern Tooling**: Rust package manager, C init system, POSIX shell

## Quick Start

### Clone & Build
```bash
git clone https://github.com/basantpz/sunya-linux.git
cd sunya-linux
make build
make test
sudo make install
cd ~/sunya-linux && git log --oneline -10
cat > ~/sunya-linux/config/sunya.conf <<'EOF'
# Sunya Linux System Configuration
# Version: 0.1.0

[system]
name = Sunya Linux
version = 0.1.0-alpha
hostname = sunya-linux
timezone = UTC

[boot]
timeout = 5
default_entry = 0
graphics_mode = auto
quiet = true

[performance]
cpu_scaling = powersave
swap_enabled = true
memory_limit = auto
io_scheduler = mq-deadline

[network]
dhcp_enabled = true
ipv6_enabled = true
dns_servers = 8.8.8.8, 8.8.4.4

[security]
selinux = disabled
apparmor = disabled
firewall = enabled

[logging]
log_level = info
log_file = /var/log/sunya.log
max_log_size = 10M
