# McJava Test Generator

McJava Test Generator automatically creates test cases for the McJava compiler.  
It helps verify if the compiler works correctly before committing changes.

---

## 🧪 Overview

- **What it does:**  
  Generates various tests to validate the McJava compiler.

- **Can I run it in Minecraft?**  
  It can generate Minecraft datapack-compatible `.mcfunction` tests.  
  However, some tests may fail due to missing `advancements`, `predictions`, or unavailable commands like `/op`.

- **Can I test only specific commands?**  
  Yes!  
  ```bash
  ./main.exe -cmd=<command>
  ```

- **Can I generate only commands allowed in Minecraft functions?**
  Yes, by limiting the permission level (functions have permission level 2):
  ```bash
  ./main.exe -perm_lvl=<permission level>
  ```
<br>

## ⚙️ Installation (Windows / MinGW-w64)

1. **Install MinGW-w64**  
   - Download from [https://www.mingw-w64.org/downloads/](https://www.mingw-w64.org/downloads/)
   - During installation, choose architecture **x86_64** and make sure to add `mingw64/bin` to your system PATH.

2. **Clone the repository**
   ```bash
   git clone https://github.com/Skubiak0903/McJava-Test-Gen.git
   cd McJava-Test-Gen
   ```

3. **Compile using g++**
    ```bash
    g++ -std=c++17 -O2 -Wall -Wextra -o main.exe src/*.cpp
    ```
    (Adjust the path to your .cpp files if needed)

4. **Run the program**<br>
    Examples:
    ```bash
    ./main.exe
    ./main.exe -cmd=<command>
    ./main.exe -perm_lvl=<permission level>
    ./main.exe -cmd=<command> -perm_lvl=<permission level>
    ```
<br>

## 💬 Feedback

Found a bug or have a suggestion?  
Please open an [issue](https://github.com/Skubiak0903/McJava-Test-Gen/issues) — all feedback is welcome!
<br><br>

## 👤 Authors

[@Skubiak0903](https://github.com/Skubiak0903)

---
