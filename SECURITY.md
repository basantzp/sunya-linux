# Sunya Linux Security Policy

## Reporting Security Issues

If you discover a security vulnerability in Sunya Linux, please email:
**basantpz@github.com** with subject line: `[SECURITY] Sunya Linux Vulnerability`

Do **not** open public GitHub issues for security vulnerabilities.

## Security Guidelines

### For Users
- Keep Sunya Linux updated with `sunya-pkg update`
- Use strong passwords
- Enable firewall with `sysctl net.ipv4.firewall=1`
- Review package sources before installation

### For Developers
- Follow secure coding practices
- Use static analysis tools: `cargo clippy`, `gcc -Wall -Wextra`
- Validate all user input
- Use memory-safe languages (Rust) where possible
- Keep dependencies updated

## Security Roadmap

### v0.2.0
- [ ] SELinux support
- [ ] AppArmor profiles
- [ ] Secure boot support

### v0.3.0
- [ ] Automatic security updates
- [ ] Vulnerability scanning
- [ ] Signed packages

### v1.0.0
- [ ] Full security audit
- [ ] Cryptographic verification
- [ ] Security hardening guide

## Supported Versions

| Version | Status | Support Until |
|---------|--------|---------------|
| 1.0.x | Stable | TBD |
| 0.3.x | Beta | v1.0 release |
| 0.2.x | Alpha | v0.3 release |
| 0.1.x | Pre-alpha | v0.2 release |

## Security Best Practices

1. **Principle of Least Privilege**: Run services with minimal permissions
2. **Defense in Depth**: Use multiple security layers
3. **Secure by Default**: Security is enabled by default
4. **Regular Updates**: Stay current with security patches
5. **Transparency**: Security policies are public and auditable

## License

This security policy is licensed under GPL-3.0.
