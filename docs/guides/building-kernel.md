# Building Sunya Linux Kernel

## Prerequisites

- Kernel source code (latest stable from kernel.org)
- Build tools: gcc, make, binutils
- ~2GB disk space for kernel build

## Download Kernel Source

```bash
cd ~/sunya-linux/kernel
wget https://cdn.kernel.org/pub/linux/kernel/v6.x/linux-6.1.tar.xz
tar -xf linux-6.1.tar.xz
cd linux-6.1
cp ../kernel-config.txt .config
make olddefconfig
make menuconfig
make -j1 bzImage modules
make -j$(nproc) bzImage modules
sudo make modules_install
sudo cp arch/x86/boot/bzImage /boot/vmlinuz-sunya-6.1
sudo cp System.map /boot/System.map-sunya-6.1
sudo grub-mkconfig -o /boot/grub/grub.cfg
menuentry 'Sunya Linux' {
    insmod gzio
    insmod part_msdos
    insmod ext2
    set root='(hd0,msdos1)'
    linux /vmlinuz-sunya-6.1 root=/dev/sda1 ro quiet
    initrd /initrd.img-sunya-6.1
}
uname -r
cat /proc/version
dmesg | head -20
strip arch/x86/boot/bzImage
ls -lh arch/x86/boot/bzImage
cat > ~/sunya-linux/docs/INSTALLATION_COMPLETE.md <<'EOF'
# Sunya Linux Complete Installation and Setup Guide

## Phase 1: Pre-Installation Requirements

### System Requirements
- CPU: x86_64 processor (Intel/AMD, 64-bit)
- RAM: Minimum 2GB (4GB recommended for development)
- Disk: 10GB minimum (20GB recommended)
- Firmware: UEFI or BIOS with boot support
- Internet: Required for downloading packages and updates

### Supported Hardware
- Desktop computers (2010+)
- Laptops (2012+)
- Virtual machines (VirtualBox, KVM, VMware)
- Cloud instances (AWS, DigitalOcean, Linode, etc.)
- Single-board computers (Raspberry Pi 4+)

### Pre-Installation Checklist
- [ ] Backup important data
- [ ] Download Sunya Linux ISO
- [ ] Create bootable USB drive
- [ ] Disable Secure Boot (if needed)
- [ ] Set BIOS boot order
- [ ] Test ISO on virtual machine first

## Phase 2: Creating Bootable Installation Media

### On Linux
```bash
# Download ISO
wget https://github.com/basantpz/sunya-linux/releases/download/v0.1.0/sunya-linux-0.1.0.iso

# Identify USB device
lsblk
# or
sudo fdisk -l

# Write ISO to USB (replace sdX with your device)
sudo dd if=sunya-linux-0.1.0.iso of=/dev/sdX bs=4M status=progress
sudo sync

# Eject USB
sudo eject /dev/sdX
# Download ISO
curl -L -o sunya-linux-0.1.0.iso https://github.com/basantpz/sunya-linux/releases/download/v0.1.0/sunya-linux-0.1.0.iso

# Identify USB device
diskutil list

# Unmount USB
diskutil unmountDisk /dev/diskN

# Write ISO
sudo dd if=sunya-linux-0.1.0.iso of=/dev/rdiskN bs=4m
sudo diskutil eject /dev/diskN
sunya-pkg update
sunya-pkg upgrade
sunya-pkg install base-devel
sunya-pkg install git curl wget
sunya-pkg install vim nano
sunya-pkg install gcc make
sunya-pkg install rust cargo
# Set timezone
sudo timedatectl set-timezone UTC

# Set hostname
sudo hostnamectl set-hostname my-hostname

# Update system clock
sudo ntpd -q -g

# Configure locale
sudo localectl set-locale LANG=en_US.UTF-8
sudo useradd -m -G wheel newuser
sudo passwd newuser
sudo systemctl enable syslogd
sudo systemctl enable udevd
sudo systemctl start syslogd
sudo systemctl start udevd
# Minimal Wayland desktop
sunya-pkg install wayland weston

# Or lightweight X11
sunya-pkg install xorg-server openbox
# Programming languages
sunya-pkg install python3 nodejs ruby

# Version control
sunya-pkg install git

# Editors
sunya-pkg install vim emacs vscode

# Build tools
sunya-pkg install cmake ninja meson
sunya-pkg install openssh
sudo systemctl enable sshd
sudo systemctl start sshd

# Generate SSH keys
ssh-keygen -t ed25519 -C "your-email@example.com"
sudo systemctl enable ufw
sudo systemctl start ufw
sudo ufw default deny incoming
sudo ufw default allow outgoing
sudo ufw allow 22/tcp
sudo ufw enable
sudo systemctl enable sunya-update.timer
sudo systemctl start sunya-update.timer
# Check current CPU frequency
cat /proc/cpuinfo | grep MHz

# Set CPU governor to powersave
echo powersave | sudo tee /sys/devices/system/cpu/cpu*/cpufreq/scaling_governor

# Check disk scheduler
cat /sys/block/sda/queue/scheduler

# Set disk scheduler to mq-deadline
echo mq-deadline | sudo tee /sys/block/sda/queue/scheduler
# Check swap
free -h

# Create additional swap if needed
sudo fallocate -l 2G /swapfile
sudo chmod 600 /swapfile
sudo mkswap /swapfile
sudo swapon /swapfile

# Make permanent by adding to /etc/fstab
echo '/swapfile none swap sw 0 0' | sudo tee -a /etc/fstab
# Install power management tools
sunya-pkg install tlp tlp-rdw

# Enable TLP
sudo systemctl enable tlp
sudo systemctl start tlp

# Check battery status
tlp-stat -b
# Check for updates
sunya-pkg update

# Install updates
sunya-pkg upgrade

# Full system upgrade
sunya-pkg dist-upgrade
# Check disk usage
df -h

# Check memory usage
free -h

# Check system load
uptime

# List running processes
ps aux

# Real-time monitoring
top
# View system logs
sudo journalctl -xe

# View kernel messages
dmesg

# View package manager logs
cat /var/log/sunya-pkg.log
# Create system backup
sudo tar -czf /backup/sunya-backup-$(date +%Y%m%d).tar.gz \
  --exclude=/proc --exclude=/sys --exclude=/dev /

# Restore from backup
sudo tar -xzf /backup/sunya-backup-YYYYMMDD.tar.gz -C /
ls -la          # List files with details
cp file1 file2  # Copy file
mv file1 file2  # Move/rename file
rm file         # Delete file
mkdir dir       # Create directory
cd dir          # Change directory
pwd             # Print working directory
uname -a        # System information
lsb_release -a  # OS information
df -h           # Disk usage
free -h         # Memory usage
uptime          # System uptime
whoami          # Current user
sunya-pkg update      # Update package database
sunya-pkg install pkg # Install package
sunya-pkg remove pkg  # Remove package
sunya-pkg search term # Search packages
sunya-pkg list        # List installed packages
sudo fsck -y /dev/sda1
sudo grub-install /dev/sda
sudo grub-mkconfig -o /boot/grub/grub.cfg
# Boot into recovery mode
# Mount filesystem as read-write
mount -o remount,rw /

# Reset password
passwd root

# Reboot
reboot
chmod +x ~/sunya-linux/scripts/system-benchmark.sh
cat > ~/sunya-linux/scripts/system-info.sh <<'EOF'
#!/bin/bash
# Sunya Linux System Information Script

echo "╔════════════════════════════════════════════╗"
echo "║   Sunya Linux System Information          ║"
echo "╚════════════════════════════════════════════╝"
echo ""

echo "=== System ==="
echo "Hostname: $(hostname)"
echo "Kernel: $(uname -r)"
echo "Architecture: $(uname -m)"
echo "Uptime: $(uptime -p)"
echo ""

echo "=== Hardware ==="
echo "CPU: $(grep 'model name' /proc/cpuinfo | head -1 | cut -d':' -f2 | xargs)"
echo "Cores: $(nproc)"
echo "Memory: $(free -h | grep Mem | awk '{print "Total:", $2, "Used:", $3, "Free:", $4}')"
echo "Disk: $(df -h / | tail -1 | awk '{print "Total:", $2, "Used:", $3, "Free:", $4}')"
echo ""

echo "=== Network ==="
echo "Interfaces:"
ip link show | grep -E '^[0-9]+:' | while read line; do
    iface=$(echo $line | awk -F':' '{print $2}' | xargs)
    ip=$(ip addr show $iface | grep 'inet ' | awk '{print $2}' | head -1)
    echo "  $iface: $ip"
done
echo ""

echo "=== Users ==="
echo "Current User: $(whoami)"
echo "Logged In Users:"
w -h | awk '{print "  " $1 " (" $3 ")"}'
echo ""

echo "=== Services ==="
echo "Running Services:"
systemctl list-units --type=service --state=running --no-pager 2>/dev/null | grep -E '\.service' | awk '{print "  " $1}' | head -10
echo ""

echo "=== Packages ==="
echo "Total Installed: $(sunya-pkg list 2>/dev/null | wc -l) packages"
echo ""

echo "=== Disk Usage ==="
df -h | tail -n +2 | awk '{printf "  %-20s %10s %10s %10s %5s\n", $6, $2, $3, $4, $5}'
echo ""

echo "=== Memory Usage ==="
free -h | awk 'NR==2 {printf "  Used: %s / Total: %s (%.1f%%)\n", $3, $2, ($3/$2)*100}'
echo ""

echo "=== CPU Usage ==="
echo "  Load Average: $(uptime | awk -F'load average:' '{print $2}')"
echo ""

echo "=== Sunya Linux Version ==="
if [ -f /etc/sunya-release ]; then
    cat /etc/sunya-release
else
    echo "  Sunya Linux 0.1.0-alpha"
fi
