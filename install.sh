#!/bin/bash
set -e
VERSION="0.1.0-alpha"
INSTALL_DIR="$HOME/.sunya"
BIN_DIR="$INSTALL_DIR/bin"
echo "Installing Sunya Linux $VERSION..."
mkdir -p "$BIN_DIR" "$INSTALL_DIR/lib" "$INSTALL_DIR/share"
echo "✓ Installation complete!"
