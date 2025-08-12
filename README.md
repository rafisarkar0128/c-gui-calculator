# 🧮 C GUI Calculator

A beginner-friendly project developed as part of the **CSE115 course** in the **Department of Electrical & Computer Engineering** in **North South University**. This GUI-based calculator performs both **basic arithmetic** and **scientific operations** using the **C programming language** with a graphical interface powered by `GTK`.

## 🧪 Project Reactor Status

[![Issues][issues-shield]][issues-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Contributors][contributors-shield]][contributors-url]
[![MIT License][license-shield]][license-url]
[![Last Commit][commit-shield]][commit-url]

## 🗂️ Project Structure

```
c-gui-calculator/
├── main.c              # Main code file to run the project
├── README.md           # Project documentation
├── requirements.txt    # List of required tools/libraries
├── .github/            # GitHub workflows and issue templates
├── .gitignore          # Ignore unnecessary files
├── LICENSE             # Project license
├── SECURITY.md         # Security policy
├── _config.yml         # Configuration file (for GitHub Pages)
├── data/               # Datasets (images, etc.)
├── support/            # Other code files
├── others/             # Final & update presentations, reports, and demo video
│   ├── final_presentation.pptx
│   ├── final_report.pdf
│   ├── update_presentation.pptx
│   ├── update_report.pdf
│   └── demo_video.mp4
```

## 🚀 Features

### 📊 Basic Operations

-   Addition (+), Subtraction (-), Multiplication (\*), Division (/)
-   Exponentiation (^) with right-associative evaluation
-   Parentheses support for complex expressions
-   Decimal numbers and percentage calculations

### 🔬 Scientific Functions

-   **Square Root**: `sqrt(x)` - calculates √x with domain validation
-   **Logarithmic**: `log(x)` (base-10) and `ln(x)` (natural log)
-   **Trigonometric**: `sin(x)`, `cos(x)`, `tan(x)` - accepts degrees
-   All functions include proper domain checking and error handling

### 🧠 Advanced Features

-   **Expression Parsing**: Uses Shunting Yard algorithm for proper operator precedence
-   **Unary Operators**: Handles negative numbers (-5, -(3+2))
-   **Auto-Clear Behavior**: Smart input clearing after calculations
-   **Memory Management**: Dynamic stacks with automatic cleanup
-   **Error Recovery**: Comprehensive error messages for invalid operations

## 📝 Usage Examples

### Basic Arithmetic

```
2 + 3 * 4 = 14          # Respects operator precedence
(2 + 3) * 4 = 20        # Parentheses override precedence
15 / 3 + 2 = 7          # Left-to-right evaluation for same precedence
50% = 0.5               # Percentage conversion
```

### Scientific Functions

```
sqrt(16) = 4            # Square root
sqrt(2) = 1.414...      # Works with non-perfect squares
log(100) = 2            # Base-10 logarithm
ln(2.718) = 1           # Natural logarithm (approximately e)
sin(30) = 0.5           # Sine in degrees
cos(60) = 0.5           # Cosine in degrees
tan(45) = 1             # Tangent in degrees
```

### Power Operations

```
2^3 = 8                 # Basic exponentiation
2^3^2 = 512             # Right associative: 2^(3^2), not (2^3)^2
(-2)^3 = -8             # Negative base with integer exponent
4^0.5 = 2               # Fractional exponents (same as sqrt)
```

### Complex Expressions

```
sin(90) + sqrt(cos(0) * 4) = 3     # Mixed functions: 1 + sqrt(1 * 4) = 1 + 2 = 3
(5 + 3) * sqrt(16) / 2 = 16        # Multiple operations: 8 * 4 / 2 = 16
log(10^3) = 3                      # Logarithm of power: log(1000) = 3
2 * sin(30) + cos(60) = 1.5        # Multiple trig functions: 2 * 0.5 + 0.5 = 1.5
```

## ⌨️ Keyboard Shortcuts

| Key           | Action    | Description                      |
| ------------- | --------- | -------------------------------- |
| `Enter`       | Calculate | Same as pressing the = button    |
| `Backspace`   | Delete    | Remove last character from input |
| `Numbers 0-9` | Input     | Use on-screen buttons only       |
| `Operators`   | Input     | Use on-screen buttons only       |

> **Note**: Most input requires using the on-screen buttons to ensure proper token recognition by the expression parser.

## ❌ Error Handling

The calculator provides comprehensive error checking for mathematical edge cases:

### Domain Errors

```
sqrt(-4)        → "Cannot take square root of negative number"
log(0)          → "Logarithm undefined for zero or negative numbers"
log(-5)         → "Logarithm undefined for zero or negative numbers"
ln(0)           → "Natural log undefined for zero or negative numbers"
```

### Division Errors

```
5 / 0           → "Division by zero"
1 / (2-2)       → "Division by zero"
0^(-2)          → "Cannot raise zero to negative power"
```

### Power Function Errors

```
(-2)^1.5        → "Cannot raise negative number to non-integer power"
(-3)^0.333      → "Cannot raise negative number to non-integer power"
```

### Trigonometric Errors

```
tan(90)         → "Tangent undefined at 90° and odd multiples"
tan(270)        → "Tangent undefined at 90° and odd multiples"
tan(-90)        → "Tangent undefined at 90° and odd multiples"
```

### Syntax Errors

```
((2+3)          → "Mismatched parentheses"
2++)            → "Invalid character in expression"
sin(            → "Function 'sin' requires an argument"
+ * 2           → "Not enough operands for operator"
```

## 🤝 Team Members

This project was collaboratively developed by:

-   **[Md. Rafi Sarkar](https://github.com/rafisarkar0128)** - Lead Developer & Project Coordinator
-   **[Ainul Huque](https://github.com/ainul10222)** - Core Developer
-   **[Md. Ahasanul Kabir Tahsin](https://github.com/Tahsin99x)** - Core Developer
-   **[Md. Hasibul Halim](https://github.com/HHHasibCSE)** - Core Developer
-   **[Md. Rahat Sarkar](https://github.com/rahat7100)** - Core Developer

## 🚀 Quick Start

### Prerequisites

Ensure you have the following installed:

-   `gcc` (GNU Compiler Collection)
-   `pkg-config` (Build configuration tool)
-   `libgtk-3-dev` (GTK+ 3 development files)

### Installation & Setup

1. **Clone the repository**

    ```bash
    git clone https://github.com/rafisarkar0128/c-gui-calculator.git
    cd c-gui-calculator
    ```

2. **Install dependencies**

    **Linux (Ubuntu/Debian):**

    ```bash
    sudo apt update
    sudo apt install gcc pkg-config libgtk-3-dev
    ```

    **Linux (Fedora/CentOS/RHEL):**

    ```bash
    sudo dnf install gcc pkgconf-pkg-config gtk3-devel
    ```

    **Windows (MSYS2):**

    ```bash
    pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-pkg-config mingw-w64-x86_64-gtk3
    ```

    **macOS (Homebrew):**

    ```bash
    brew install gcc pkg-config gtk+3
    ```

3. **Compile & Run**
    ```bash
    gcc -o calculator main.c `pkg-config --cflags --libs gtk+-3.0` -lm
    ./calculator
    ```

> 📖 **Need help?** See our comprehensive [Getting Started Guide](./Getting-Started.md) for detailed setup instructions, troubleshooting tips, and platform-specific notes.

## 🏗️ Technical Architecture

The calculator implements several advanced computer science concepts:

### Expression Parsing

-   **Lexical Analysis**: Tokenizes input into numbers, operators, functions, and parentheses
-   **Shunting Yard Algorithm**: Converts infix expressions to Reverse Polish Notation (RPN)
-   **Stack-Based Evaluation**: Evaluates RPN expressions using dynamic stacks

### Memory Management

-   **Dynamic Arrays**: Self-resizing stacks for tokens and numbers
-   **Automatic Cleanup**: Proper memory deallocation to prevent leaks
-   **Error Recovery**: Graceful handling of allocation failures

### GUI Architecture

-   **Event-Driven Design**: GTK signal/callback system
-   **State Management**: Centralized calculator state with input buffering
-   **CSS Styling**: Custom appearance for better user experience

## 📚 Learning Outcomes

-   Hands-on experience with **C fundamentals** and advanced concepts
-   Introduction to **GUI development** using C and GTK
-   **Algorithm implementation**: Expression parsing and evaluation
-   **Data structures**: Dynamic stacks and memory management
-   **Mathematical programming**: Safe function implementations with domain validation
-   **Software engineering**: Modular design, error handling, and documentation
-   Collaborative software development and Git usage

## 🤝 Contributing

We welcome contributions! Here's how you can help:

1. **Fork the repository** and create your feature branch
2. **Follow our coding standards** - consistent formatting and documentation
3. **Test thoroughly** - ensure all features work across platforms
4. **Submit a pull request** with a clear description of changes

### Development Setup

1. Follow the [Quick Start](#-quick-start) guide above
2. Make your changes in a feature branch
3. Test compilation and functionality
4. Submit your pull request

## 📞 Contact & Support

For questions, bug reports, or contributions:

-   📧 **Email**: [rafisarkar0128@proton.me](mailto:rafisarkar0128@proton.me)
-   🐛 **Issues**: [GitHub Issues](https://github.com/rafisarkar0128/c-gui-calculator/issues)
-   💬 **Discussions**: [GitHub Discussions](https://github.com/rafisarkar0128/c-gui-calculator/discussions)

## 📚 References & Resources

-   [GTK Documentation](https://www.gtk.org/docs/)
-   [C Programming Language](<https://en.wikipedia.org/wiki/C_(programming_language)/>)
-   [Shunting Yard Algorithm](https://en.wikipedia.org/wiki/Shunting_yard_algorithm)
-   [Reverse Polish Notation](https://en.wikipedia.org/wiki/Reverse_Polish_notation)

## 🧠 Acknowledgments

Thanks to our instructor and the CSE115 course staff for their guidance and resources, and to the open-source community for tools and inspiration.

## 📄 License

This project is licensed under the [MIT License](./LICENSE).

[issues-shield]: https://img.shields.io/github/issues/rafisarkar0128/c-gui-calculator?style=for-the-badge
[issues-url]: https://github.com/rafisarkar0128/c-gui-calculator/issues
[forks-shield]: https://img.shields.io/github/forks/rafisarkar0128/c-gui-calculator?style=for-the-badge
[forks-url]: https://github.com/rafisarkar0128/c-gui-calculator/network/members
[stars-shield]: https://img.shields.io/github/stars/rafisarkar0128/c-gui-calculator?style=for-the-badge
[stars-url]: https://github.com/rafisarkar0128/c-gui-calculator/stargazers
[contributors-shield]: https://img.shields.io/github/contributors/rafisarkar0128/c-gui-calculator?style=for-the-badge
[contributors-url]: https://github.com/rafisarkar0128/c-gui-calculator/graphs/contributors
[license-shield]: https://img.shields.io/github/license/rafisarkar0128/c-gui-calculator?style=for-the-badge
[license-url]: https://github.com/rafisarkar0128/c-gui-calculator/blob/master/LICENSE
[commit-shield]: https://img.shields.io/github/last-commit/rafisarkar0128/c-gui-calculator?style=for-the-badge
[commit-url]: https://github.com/rafisarkar0128/c-gui-calculator/commits/main
