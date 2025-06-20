# 🧮 C GUI Calculator

A beginner-friendly project developed as part of the **CSE115 course** in the **Department of Electrical & Computer Engineering** in **North South University**. This GUI-based calculator performs both **basic arithmetic** and **scientific operations** using the **C programming language** with a graphical interface powered by `GTK`.

## 🚀 Features

- Basic arithmetic: Add, Subtract, Multiply, Divide
- Scientific functions: Power, Square Root, Trigonometric operations (sin, cos, etc.)
- Interactive buttons and display
- Keyboard support for input (optional)
- Error handling (e.g., divide-by-zero)

## 📚 Learning Outcomes

- Hands-on experience with **C fundamentals**
- Introduction to **GUI development** using C and GTK
- Modular programming and event-driven design
- Collaborative software development and Git usage

## 🛠️ Tech Stack

- **Language:** C
- **GUI Library:** GTK
- **Compiler:** GCC
- **Version Control:** Git & GitHub

## 🗂️ Project Structure

```
c-gui-calculator/
├── main.c           # Core logic
├── gui.c/h          # GUI-related code (if separated)
├── Makefile         # For build automation
├── .gitignore       # For ignoring unnecessary files
├── LICENSE          # Project license (if applicable)
├── README.md        # Project documentation
└── assets/          # Icons, themes (optional)
```

## 💡 Getting Started

### 1. Clone the repository

```bash
git clone https://github.com/rafisarkar0128/c-gui-calculator.git
cd c-gui-calculator
```

### 2. Install GTK (Linux)

```bash
sudo apt update
sudo apt install libgtk-3-dev
```

### 3. Compile the project

```bash
gcc -o calculator main.c `pkg-config --cflags --libs gtk+-3.0` -lm
./calculator
```

> 💡 Windows users can use MSYS2 or Code::Blocks with GTK setup.

## 🤝 Team Members

- Md. Rafi Sarkar - [GitHub Profile](https://github.com/rafisarkar0128)
- [Other Team Member 1]
- [Other Team Member 2]

## 📄 License

This project is for educational purposes only. You're welcome to fork or use parts of it in your own learning.

## 🧠 Acknowledgments

Thanks to our instructor and the CSE115 course staff for their guidance and resources, and to the open-source community for tools and inspiration.
