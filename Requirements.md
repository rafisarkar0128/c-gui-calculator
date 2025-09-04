# 🧮 C GUI Calculator – System Requirements

This document outlines the requirements, dependencies, and tools needed to build and run the C GUI Calculator project, a cross-platform calculator built using C and GTK+ 3.

## 🎯 Overview

The C GUI Calculator requires:

-   A C compiler
-   GTK+ 3 development libraries
-   Supporting build tools

## 📋 System Requirements

### Minimum Hardware

-   **RAM**: 2GB (4GB recommended for development)
-   **Storage**: 500MB free space
-   **Architecture**: x86_64 (64-bit) or x86 (32-bit)

### Supported Operating Systems

-   **Linux**: Ubuntu 18.04+, Debian 10+, Fedora 30+, CentOS 8+, Arch Linux
-   **Windows**: Windows 10/11 (with MSYS2 or MinGW)
-   **macOS**: macOS 10.14 (Mojave) or later

## 📦 Core Dependencies

| Component      | Version | Purpose                                             | Status      |
| -------------- | ------- | --------------------------------------------------- | ----------- |
| **gcc**        | 7.0+    | GNU Compiler Collection for compiling C source code | ✅ Required |
| **pkg-config** | 0.29+   | Manages compiler/linker flags for libraries         | ✅ Required |
| **GTK+ 3**     | 3.22+   | GUI toolkit for creating the calculator interface   | ✅ Required |
| **GLib**       | 2.56+   | Low-level system library (included with GTK+)       | ✅ Required |
| **make**       | 4.0+    | Build automation tool                               | 📋 Optional |
| **git**        | 2.0+    | Version control system                              | 📋 Optional |

## 🖥️ Platform-Specific Installation Instructions

### Linux

#### Ubuntu/Debian/Mint

```bash
sudo apt update && sudo apt upgrade -y
sudo apt install gcc pkg-config libgtk-3-dev build-essential
```

#### Fedora/RHEL/CentOS

```bash
# Fedora/RHEL 8+
sudo dnf update -y
sudo dnf groupinstall "Development Tools" -y
sudo dnf install gcc pkgconf-pkg-config gtk3-devel

# CentOS/RHEL 7
sudo yum groupinstall "Development Tools"
sudo yum install gcc pkgconfig gtk3-devel
```

#### Arch/Manjaro

```bash
sudo pacman -Syu
sudo pacman -S base-devel gtk3 pkg-config
```

### Windows

#### MSYS2 (Recommended)

1. Download and install MSYS2 from [msys2.org](https://www.msys2.org/)
2. Open the **MSYS2 MinGW 64-bit** terminal
3. Run:

```bash
pacman -Syu
pacman -S base-devel mingw-w64-x86_64-gcc mingw-w64-x86_64-pkg-config mingw-w64-x86_64-gtk3
```

**Important:** Always use the **MSYS2 MinGW 64-bit** terminal, not the default MSYS2 terminal.

#### Alternative Methods

-   **Visual Studio with vcpkg**:
    ```bash
    git clone https://github.com/Microsoft/vcpkg.git
    cd vcpkg
    ./bootstrap-vcpkg.bat
    ./vcpkg install gtk:x64-windows
    ```
-   **Code::Blocks with MinGW**:
    1. Download Code::Blocks with MinGW from [codeblocks.org](http://www.codeblocks.org/)
    2. Install GTK+ 3 development libraries manually
    3. Configure include/library paths in project settings

### macOS

#### Homebrew (Recommended)

1. Install Homebrew if not present:

```bash
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

2. Install required packages:

```bash
xcode-select --install
brew install gcc pkg-config gtk+3
brew install --cask xquartz
```

3. Log out and back in (or restart) after installing XQuartz
4. Launch XQuartz before running the calculator

#### MacPorts (Alternative)

```bash
sudo port install gcc12 pkgconfig gtk3
sudo port select --set gcc mp-gcc12
```

## 🧪 Verification Steps

After installation, verify your environment:

```bash
# Check compiler
gcc --version                    # Should show GCC 7.0+

# Check pkg-config
pkg-config --version             # Should show 0.29+

# Check GTK+ 3
pkg-config --exists gtk+-3.0 && echo "✅ GTK+ 3 found" || echo "❌ GTK+ 3 missing"
pkg-config --modversion gtk+-3.0 # Should show 3.22+

# Test compilation
echo '#include <gtk/gtk.h>\nint main(){return 0;}' > test_gtk.c
gcc test_gtk.c $(pkg-config --cflags --libs gtk+-3.0) && echo "✅ GTK+ compilation works"
rm test_gtk.c a.out 2>/dev/null
```

## ⚠️ Common Issues & Solutions

| Issue                              | Solution                                                       |
| ---------------------------------- | -------------------------------------------------------------- |
| "Package gtk+-3.0 was not found"   | Install GTK+ development packages for your OS                  |
| "pkg-config: command not found"    | Install pkg-config package for your OS                         |
| GTK+ app doesn't display on macOS  | Install and launch XQuartz (X11)                               |
| Wrong MSYS2 environment on Windows | Use MinGW64 terminal, verify prompt shows "MINGW64" not "MSYS" |

## 📘 Notes & Resources

### For Beginners

-   **Ubuntu/Debian users**: The `build-essential` package includes GCC and other essential tools
-   **First-time developers**: Consider installing VS Code with C/C++ extensions
-   **Git users**: Install git to clone the repository: `sudo apt install git` (Linux) or `brew install git` (macOS)

### Platform-Specific

-   **Linux**: GTK+ 3 works with both Wayland and X11 display servers
-   **Windows**: Ensure MinGW64 bin directory is in PATH, runtime may require GTK+ DLLs in same directory
-   **macOS**: XQuartz is required for GTK+; don't mix Homebrew and MacPorts

### Documentation & Learning Resources

-   [GTK+ 3 Reference Manual](https://docs.gtk.org/gtk3/)
-   [GCC Manual](https://gcc.gnu.org/onlinedocs/gcc/)
-   [pkg-config Guide](https://www.freedesktop.org/wiki/Software/pkg-config/)
-   [MSYS2 Documentation](https://www.msys2.org/)
-   [Homebrew Documentation](https://docs.brew.sh/)
-   [GTK+ 3 Tutorial](https://developer.gnome.org/gtk3/stable/gtk-getting-started.html)
-   [C Programming Course](https://www.learn-c.org/)

---

## ✅ Next Steps

1. Install the requirements above
2. Follow the [Getting Started Guide](./Getting-Started.md) for detailed setup
3. Compile and run the calculator
4. Read the [README](./README.md) for project overview and features

**Need Help?**

-   🐛 Report issues: [GitHub Issues](https://github.com/rafisarkar0128/c-gui-calculator/issues)
-   💬 Ask questions: [GitHub Discussions](https://github.com/rafisarkar0128/c-gui-calculator/discussions)
-   📧 Contact maintainer: [rafisarkar0128@proton.me](mailto:rafisarkar0128@proton.me)
