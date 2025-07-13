# 💡 Getting Started – C GUI Calculator

Welcome! This guide will help you get up and running with the C GUI Calculator built using GTK+ 3. Follow the platform-specific instructions below to clone, install dependencies, compile, and run the calculator.

## 📦 Prerequisites

Before compiling, ensure the following packages are installed:

-   `gcc` – C compiler
-   `pkg-config` – Compiler and linker configuration helper
-   `libgtk-3-dev` – GTK+ 3 development files

See the [Requirements Guide](./Requirements.md) for full details and installation commands for all platforms.

## 🚀 Setup & Compilation

### 🔹 1. Clone the Repository

```bash
git clone https://github.com/rafisarkar0128/c-gui-calculator.git
cd c-gui-calculator
```

### 🔹 2. Install GTK and Dependencies

#### 📍 Linux (Debian/Ubuntu)

```bash
sudo apt update
sudo apt install gcc pkg-config libgtk-3-dev
```

#### 📍 Fedora/CentOS/RHEL

```bash
sudo dnf install gcc pkgconf-pkg-config gtk3-devel
```

#### 📍 macOS (Homebrew)

```bash
brew install gcc pkg-config gtk+3
```

> ⚠️ Additional setup like XQuartz may be required to run GUI apps on macOS.

#### 📍 Windows (MSYS2)

```bash
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-pkg-config mingw-w64-x86_64-gtk3
```

> 💡 Alternatively, you may use Code::Blocks with proper GTK+ configuration.

### 🔹 3. Compile the Project

```bash
gcc -o calculator main.c `pkg-config --cflags --libs gtk+-3.0` -lm
./calculator
```

> 🧠 `-lm` is included for linking math functions if your calculator uses them.

## 🛠️ Troubleshooting

-   Ensure your system’s package manager is up to date.
-   If `pkg-config` reports missing paths, verify GTK installation.
-   Windows users: Make sure MSYS2’s shell uses the `mingw-w64` environment, not the default `msys`.

## 📚 Resources

-   [GTK+ 3 Documentation](https://docs.gtk.org/gtk3/)
-   [MSYS2 Setup Guide](https://www.msys2.org/)
-   [Homebrew Guide](https://brew.sh/)
