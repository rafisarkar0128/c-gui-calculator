# 🧮 C GUI Calculator – Project Requirements

This project requires several development tools and libraries to compile and run a graphical calculator built using C and GTK+ 3.

## 📦 Required Packages

| Package        | Description                                                            |
| -------------- | ---------------------------------------------------------------------- |
| `gcc`          | GNU Compiler Collection – Required to compile C source code            |
| `pkg-config`   | Tool to manage compiler/linker flags for libraries like GTK            |
| `libgtk-3-dev` | Development files for GTK+ 3 – Required to build GUI applications in C |

## 🖥️ Installation Instructions by Platform

### ✅ Linux (Debian/Ubuntu)

```bash
sudo apt update
sudo apt install gcc pkg-config libgtk-3-dev
```

### ✅ Linux (Fedora/CentOS/RHEL)

```bash
sudo dnf install gcc pkgconf-pkg-config gtk3-devel
```

### ✅ Windows (MSYS2)

```bash
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-pkg-config mingw-w64-x86_64-gtk3
```

### ✅ macOS (Homebrew)

```bash
brew install gcc pkg-config gtk+3
```

## 📘 Notes

-   Ensure your system’s package manager is up to date before installing.
-   For Windows users, MSYS2 must be properly configured with MinGW environment.
-   On macOS, GUI apps may require additional XQuartz setup for GTK.

## 🔗 Resources

-   [GTK+ 3 Documentation](https://docs.gtk.org/gtk3/)
-   [MSYS2 Setup Guide](https://www.msys2.org/)
-   [Homebrew Documentation](https://brew.sh/)
