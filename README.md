# 🧮 C GUI Calculator

A beginner-friendly project developed as part of the **CSE115 course** in the **Department of Electrical & Computer Engineering** in **North South University**. This GUI-based calculator performs both **basic arithmetic** and **scientific operations** using the **C programming language** with a graphical interface powered by `GTK`.

## Status

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

-   [x] Basic arithmetic: Add, Subtract, Multiply, Divide
-   [ ] Scientific functions: Power, Square Root, log, ln, Trigonometric operations (sin, cos, etc.)
-   [ ] Interactive buttons and display
-   [ ] Keyboard support for input (optional)
-   [ ] Error handling (e.g., divide-by-zero)

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

-   [Md. Rafi Sarkar](https://github.com/rafisarkar0128)
-   [Ainul Huque](https://github.com/ainul10222)
-   [Md. Ahasanul Kabir Tahsin](https://github.com/Tahsin99x)
-   [Md. Hasibul Halim](https://github.com/HHHasibCSE)
-   [Md. Rahat Sarkar](https://github.com/rahat7100)

## 📚 Learning Outcomes

-   Hands-on experience with **C fundamentals**
-   Introduction to **GUI development** using C and GTK
-   Modular programming and event-driven design
-   Collaborative software development and Git usage

## 📚 References

-   [GTK Documentation](https://www.gtk.org/docs/)
-   [C Programming Language](<https://en.wikipedia.org/wiki/C_(programming_language)/>)

## 🧠 Acknowledgments

Thanks to our instructor and the CSE115 course staff for their guidance and resources, and to the open-source community for tools and inspiration.

## 📄 License

This project is licensed under the [MIT License](https://github.com/rafisarkar0128/c-gui-calculator/blob/master/LICENSE).

## 📞 Contact

For any questions or contributions, feel free to reach out:

-   **Gravatar:** [https://gravatar.com/rafisarkar0128](https://gravatar.com/rafisarkar0128)
-   **Email:** [rafisarkar0128@gmail.com](mailto:rafisarkar0128@gmail.com)

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
