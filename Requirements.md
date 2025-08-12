# 🧮 C GUI Calculator – System Requirements

This document outlines the complete system requirements, dependencies, and tools needed to build and run the **C GUI Calculator** project. The calculator is built using **C** and **GTK+ 3**, making it cross-platform compatible.

## 🎯 Overview

The C GUI Calculator requires a C compiler, GTK+ 3 development libraries, and supporting build tools. This guide covers all major operating systems and provides alternative installation methods.

## 📋 System Requirements

### Minimum Hardware Requirements

-   **RAM**: 2GB (4GB recommended for development)
-   **Storage**: 500MB free space (for development tools and dependencies)
-   **Architecture**: x86_64 (64-bit) or x86 (32-bit)

### Supported Operating Systems

-   **Linux**: Ubuntu 18.04+, Debian 10+, Fedora 30+, CentOS 8+, Arch Linux
-   **Windows**: Windows 10/11 (with MSYS2 or MinGW)
-   **macOS**: macOS 10.14 (Mojave) or later

## 📦 Core Dependencies

| Component      | Version | Purpose                                               | Critical    |
| -------------- | ------- | ----------------------------------------------------- | ----------- |
| **gcc**        | 7.0+    | GNU Compiler Collection for compiling C source code   | ✅ Required |
| **pkg-config** | 0.29+   | Manages compiler/linker flags for libraries           | ✅ Required |
| **GTK+ 3**     | 3.22+   | GUI toolkit for creating the calculator interface     | ✅ Required |
| **GLib**       | 2.56+   | Low-level system library (usually included with GTK+) | ✅ Required |
| **make**       | 4.0+    | Build automation tool (optional but recommended)      | 📋 Optional |
| **git**        | 2.0+    | Version control system for cloning the repository     | 📋 Optional |

### Development Dependencies by Platform

#### Linux Packages

| Distribution  | GCC Package                | pkg-config           | GTK+ 3 Dev     |
| ------------- | -------------------------- | -------------------- | -------------- |
| Ubuntu/Debian | `gcc` or `build-essential` | `pkg-config`         | `libgtk-3-dev` |
| Fedora/RHEL   | `gcc`                      | `pkgconf-pkg-config` | `gtk3-devel`   |
| Arch/Manjaro  | `gcc` or `base-devel`      | `pkg-config`         | `gtk3`         |
| openSUSE      | `gcc`                      | `pkg-config`         | `gtk3-devel`   |

#### Windows Packages (MSYS2)

| Component    | MSYS2 Package Name            |
| ------------ | ----------------------------- |
| GCC Compiler | `mingw-w64-x86_64-gcc`        |
| pkg-config   | `mingw-w64-x86_64-pkg-config` |
| GTK+ 3       | `mingw-w64-x86_64-gtk3`       |
| Build Tools  | `base-devel`                  |

#### macOS Packages (Homebrew)

| Component     | Homebrew Formula |
| ------------- | ---------------- |
| GCC Compiler  | `gcc`            |
| pkg-config    | `pkg-config`     |
| GTK+ 3        | `gtk+3`          |
| XQuartz (X11) | `xquartz` (cask) |

## 🖥️ Platform-Specific Installation Instructions

### ✅ Linux (Debian/Ubuntu/Mint)

**Quick Install:**

```bash
sudo apt update && sudo apt upgrade -y
sudo apt install gcc pkg-config libgtk-3-dev build-essential
```

**Verification:**

```bash
gcc --version          # Should show GCC 7.0+
pkg-config --version   # Should show 0.29+
pkg-config --modversion gtk+-3.0  # Should show 3.22+
```

### ✅ Linux (Fedora/CentOS/RHEL)

**Quick Install:**

```bash
sudo dnf update -y
sudo dnf groupinstall "Development Tools" -y
sudo dnf install gcc pkgconf-pkg-config gtk3-devel
```

**Alternative for CentOS/RHEL 7:**

```bash
sudo yum groupinstall "Development Tools"
sudo yum install gcc pkgconfig gtk3-devel
```

### ✅ Linux (Arch/Manjaro)

**Quick Install:**

```bash
sudo pacman -Syu
sudo pacman -S base-devel gtk3 pkg-config
```

### ✅ Windows (MSYS2) - Recommended

**Prerequisites:** Download and install MSYS2 from [msys2.org](https://www.msys2.org/)

**Step-by-step installation:**

```bash
# 1. Update MSYS2
pacman -Syu

# 2. Install development tools
pacman -S base-devel
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-pkg-config mingw-w64-x86_64-gtk3

# 3. Verify installation (in MinGW64 terminal)
gcc --version
pkg-config --modversion gtk+-3.0
```

**Important:** Always use the **MSYS2 MinGW 64-bit** terminal, not the default MSYS2 terminal.

### ✅ Windows (Alternative Methods)

#### Visual Studio with vcpkg

```bash
# Install vcpkg
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
./bootstrap-vcpkg.bat

# Install GTK+ 3
./vcpkg install gtk:x64-windows
```

#### Code::Blocks with MinGW

1. Download Code::Blocks with MinGW from [codeblocks.org](http://www.codeblocks.org/)
2. Install GTK+ 3 development libraries manually
3. Configure include/library paths in project settings

### ✅ macOS (Homebrew) - Recommended

**Prerequisites:** Install Homebrew if not present:

```bash
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

**Installation:**

```bash
# Install Xcode command line tools
xcode-select --install

# Install required packages
brew install gcc pkg-config gtk+3

# Install XQuartz for X11 support (required for GTK+ GUI)
brew install --cask xquartz
```

**Post-installation:**

-   Log out and back in (or restart) after installing XQuartz
-   Launch XQuartz before running the calculator

### ✅ macOS (MacPorts) - Alternative

```bash
# Install MacPorts packages
sudo port install gcc12 pkgconfig gtk3

# Set GCC as default compiler
sudo port select --set gcc mp-gcc12
```

## 🧪 Verification Commands

After installation, verify your development environment:

```bash
# Check GCC compiler
gcc --version
# Expected output: gcc (GCC) 7.0.0 or higher

# Check pkg-config
pkg-config --version
# Expected output: 0.29.0 or higher

# Check GTK+ 3 availability
pkg-config --exists gtk+-3.0 && echo "✅ GTK+ 3 found" || echo "❌ GTK+ 3 missing"

# Get GTK+ version
pkg-config --modversion gtk+-3.0
# Expected output: 3.22.0 or higher

# Test compiler flags (should show multiple -I paths)
pkg-config --cflags gtk+-3.0

# Test linker flags (should show multiple -l libraries)
pkg-config --libs gtk+-3.0

# Test basic compilation
echo '#include <gtk/gtk.h>
int main(){return 0;}' > test_gtk.c
gcc test_gtk.c $(pkg-config --cflags --libs gtk+-3.0) && echo "✅ GTK+ compilation works"
rm test_gtk.c a.out 2>/dev/null
```

## ⚠️ Common Issues & Solutions

### Issue: "Package gtk+-3.0 was not found"

**Solution:** GTK+ development packages not installed

```bash
# Linux (Ubuntu/Debian)
sudo apt install libgtk-3-dev

# Linux (Fedora/RHEL)
sudo dnf install gtk3-devel

# macOS
brew install gtk+3

# Windows (MSYS2)
pacman -S mingw-w64-x86_64-gtk3
```

### Issue: "pkg-config: command not found"

**Solution:** pkg-config not installed or not in PATH

```bash
# Linux (Most distributions)
sudo apt install pkg-config  # or dnf/pacman equivalent

# macOS
brew install pkg-config

# Windows (MSYS2)
pacman -S mingw-w64-x86_64-pkg-config
```

### Issue: GTK+ app doesn't display on macOS

**Solution:** XQuartz (X11) required for GTK+ GUI

```bash
brew install --cask xquartz
# Then log out/in or restart macOS
```

### Issue: Wrong MSYS2 environment on Windows

**Solution:** Use MinGW64 terminal, not default MSYS2

-   Launch "MSYS2 MinGW 64-bit" from Start Menu
-   Verify prompt shows "MINGW64" not "MSYS"

## 📘 Important Notes

### For Students/Beginners

-   **Ubuntu/Debian users**: The `build-essential` package includes GCC and other essential tools
-   **First-time developers**: Consider installing a code editor like VS Code with C/C++ extensions
-   **Git users**: Install git to clone the repository: `sudo apt install git` (Linux) or `brew install git` (macOS)

### For Advanced Users

-   **Custom GTK+ builds**: You can compile GTK+ from source for specific requirements
-   **Cross-compilation**: Use appropriate MinGW toolchains for Windows cross-compilation on Linux
-   **Static linking**: Add `-static` flag for standalone executables (increases file size)

### Platform-Specific Considerations

#### Linux

-   **Wayland vs X11**: GTK+ 3 works with both display servers
-   **Different distributions**: Package names may vary slightly
-   **Minimal installations**: Ensure development packages are installed

#### Windows

-   **MSYS2 vs MinGW**: MSYS2 provides better package management
-   **Path issues**: Ensure MinGW64 bin directory is in PATH
-   **DLL dependencies**: Runtime may require GTK+ DLLs in same directory

#### macOS

-   **Homebrew vs MacPorts**: Both work, but don't mix them
-   **XQuartz required**: GTK+ needs X11 server on macOS
-   **Apple Silicon**: Use native ARM64 packages when available

## 🔗 Additional Resources & Documentation

### Official Documentation

-   **[GTK+ 3 Reference Manual](https://docs.gtk.org/gtk3/)** - Complete API documentation
-   **[GCC Manual](https://gcc.gnu.org/onlinedocs/gcc/)** - Compiler documentation and options
-   **[pkg-config Guide](https://www.freedesktop.org/wiki/Software/pkg-config/)** - Package configuration system

### Platform Setup Guides

-   **[MSYS2 Documentation](https://www.msys2.org/)** - Windows development environment
-   **[Homebrew Documentation](https://docs.brew.sh/)** - macOS package manager
-   **[Ubuntu Development Setup](https://help.ubuntu.com/community/CompilingEasyHowTo)** - Linux compilation basics

### Development Tools

-   **[Visual Studio Code](https://code.visualstudio.com/)** - Popular code editor with C/C++ support
-   **[Code::Blocks](http://www.codeblocks.org/)** - Cross-platform C/C++ IDE
-   **[CLion](https://www.jetbrains.com/clion/)** - Professional C/C++ IDE (paid)

### Learning Resources

-   **[GTK+ 3 Tutorial](https://developer.gnome.org/gtk3/stable/gtk-getting-started.html)** - Official getting started guide
-   **[C Programming Course](https://www.learn-c.org/)** - Interactive C programming lessons
-   **[GUI Development Basics](https://developer.gnome.org/documentation/tutorials/beginners.html)** - Introduction to GUI programming

---

## ✅ Quick Reference

**Most Common Installation Commands:**

```bash
# Ubuntu/Debian
sudo apt install gcc pkg-config libgtk-3-dev

# Fedora/RHEL
sudo dnf install gcc pkgconf-pkg-config gtk3-devel

# Arch Linux
sudo pacman -S base-devel gtk3 pkg-config

# macOS (Homebrew)
brew install gcc pkg-config gtk+3
brew install --cask xquartz

# Windows (MSYS2 MinGW64)
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-pkg-config mingw-w64-x86_64-gtk3
```

**Next Steps:**

1. ✅ Install the requirements above
2. 📖 Follow the [Getting Started Guide](./Getting-Started.md) for detailed setup
3. 🚀 Compile and run the calculator
4. 📚 Read the [README](./README.md) for project overview and features

**Need Help?**

-   🐛 Report issues: [GitHub Issues](https://github.com/rafisarkar0128/c-gui-calculator/issues)
-   💬 Ask questions: [GitHub Discussions](https://github.com/rafisarkar0128/c-gui-calculator/discussions)
-   📧 Contact maintainer: [rafisarkar0128@proton.me](mailto:rafisarkar0128@proton.me)

### ✅ Windows (MSYS2) - Recommended

**Prerequisites:** Download and install MSYS2 from [msys2.org](https://www.msys2.org/)

**Step-by-step installation:**

```bash
# 1. Update MSYS2
pacman -Syu

# 2. Install development tools
pacman -S base-devel
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-pkg-config mingw-w64-x86_64-gtk3

# 3. Verify installation (in MinGW64 terminal)
gcc --version
pkg-config --modversion gtk+-3.0
```

**Important:** Always use the **MSYS2 MinGW 64-bit** terminal, not the default MSYS2 terminal.

### ✅ Windows (Alternative Methods)

#### Visual Studio with vcpkg

```bash
# Install vcpkg
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
./bootstrap-vcpkg.bat

# Install GTK+ 3
./vcpkg install gtk:x64-windows
```

#### Code::Blocks with MinGW

1. Download Code::Blocks with MinGW from [codeblocks.org](http://www.codeblocks.org/)
2. Install GTK+ 3 development libraries manually
3. Configure include/library paths in project settings

### ✅ macOS (Homebrew) - Recommended

**Prerequisites:** Install Homebrew if not present:

```bash
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

**Installation:**

```bash
# Install Xcode command line tools
xcode-select --install

# Install required packages
brew install gcc pkg-config gtk+3

# Install XQuartz for X11 support (required for GTK+ GUI)
brew install --cask xquartz
```

**Post-installation:**

-   Log out and back in (or restart) after installing XQuartz
-   Launch XQuartz before running the calculator

### ✅ macOS (MacPorts) - Alternative

```bash
# Install MacPorts packages
sudo port install gcc12 pkgconfig gtk3

# Set GCC as default compiler
sudo port select --set gcc mp-gcc12
```

## 📘 Notes

-   Ensure your system’s package manager is up to date before installing.
-   For Windows users, MSYS2 must be properly configured with MinGW environment.
-   On macOS, GUI apps may require additional XQuartz setup for GTK.

## 🔗 Additional Resources & Documentation

### Official Documentation

-   **[GTK+ 3 Reference Manual](https://docs.gtk.org/gtk3/)** - Complete API documentation
-   **[GCC Manual](https://gcc.gnu.org/onlinedocs/gcc/)** - Compiler documentation and options
-   **[pkg-config Guide](https://www.freedesktop.org/wiki/Software/pkg-config/)** - Package configuration system

### Platform Setup Guides

-   **[MSYS2 Documentation](https://www.msys2.org/)** - Windows development environment
-   **[Homebrew Documentation](https://docs.brew.sh/)** - macOS package manager
-   **[Ubuntu Development Setup](https://help.ubuntu.com/community/CompilingEasyHowTo)** - Linux compilation basics

### Development Tools

-   **[Visual Studio Code](https://code.visualstudio.com/)** - Popular code editor with C/C++ support
-   **[Code::Blocks](http://www.codeblocks.org/)** - Cross-platform C/C++ IDE
-   **[CLion](https://www.jetbrains.com/clion/)** - Professional C/C++ IDE (paid)

### Learning Resources

-   **[GTK+ 3 Tutorial](https://developer.gnome.org/gtk3/stable/gtk-getting-started.html)** - Official getting started guide
-   **[C Programming Course](https://www.learn-c.org/)** - Interactive C programming lessons
-   **[GUI Development Basics](https://developer.gnome.org/documentation/tutorials/beginners.html)** - Introduction to GUI programming

---

## ✅ Quick Reference

**Most Common Installation Commands:**

```bash
# Ubuntu/Debian
sudo apt install gcc pkg-config libgtk-3-dev

# Fedora/RHEL
sudo dnf install gcc pkgconf-pkg-config gtk3-devel

# Arch Linux
sudo pacman -S base-devel gtk3 pkg-config

# macOS (Homebrew)
brew install gcc pkg-config gtk+3
brew install --cask xquartz

# Windows (MSYS2 MinGW64)
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-pkg-config mingw-w64-x86_64-gtk3
```

**Next Steps:**

1. ✅ Install the requirements above
2. 📖 Follow the [Getting Started Guide](./Getting-Started.md) for detailed setup
3. 🚀 Compile and run the calculator
4. 📚 Read the [README](./README.md) for project overview and features

**Need Help?**

-   🐛 Report issues: [GitHub Issues](https://github.com/rafisarkar0128/c-gui-calculator/issues)
-   💬 Ask questions: [GitHub Discussions](https://github.com/rafisarkar0128/c-gui-calculator/discussions)
-   📧 Contact maintainer: [rafisarkar0128@proton.me](mailto:rafisarkar0128@proton.me)
