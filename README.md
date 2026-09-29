# SiWG917-Random-Password-Generator
🔐 Random Password Generator is an embedded-system project developed using the Silicon Labs SiWG917 BRD2605A development kit  for generating strong and customizable passwords.# 🔐 Random Password Generator

An embedded **random password generator** built on the **Silicon Labs SiWG917 Wi-Fi SoC** using the **BRD2605A Dev Kit**. The system uses the onboard push buttons as user input and generates a random password containing uppercase letters, lowercase letters, numbers, and special characters. The generated password is displayed through the serial terminal.
This project demonstrates practical embedded-system concepts including **GPIO/button handling, manual button initialization, random number generation, string manipulation, and UART-based output**.

---


# 🛠️ Hardware

- **Silicon Labs BRD2605A Dev Kit**
- **SiWG917M111MGTBA Wi-Fi SoC**
- Onboard **BTN0**
- Onboard **BTN1**
- USB cable for power and programming
- Computer for development and serial monitoring

---

# 💻 Software 

- **Simplicity Studio 6** — project configuration and software components
- **Visual Studio Code** + Silicon Labs extension — firmware development
- **WiSeConnect 3 SDK**
- **Embedded C**
- **GCC**
- Serial terminal — Simplicity Studio console / PuTTY / Tera Term

---

# 📁 Project Structure

```text
random_password_generator/
│
├── app.c / app.h
│   └── Application logic and password generation
│
├── main.c
│   └── Generated application entry point
│
├── gpio_uulp_example.c/.h
│   └── Manual button initialization and button-state handling
│
├── config/
│   └── Auto-generated component configuration
│
├── random_password_generator.slcp
│   └── Simplicity Studio project/component definition
│
└── README.md
```

---

# ⚙️ Password Configuration

The password length can be configured using:

```c
#define PASSWORD_LENGTH 12
```

For example:

```c
#define PASSWORD_LENGTH 16
```

will generate a 16-character password.

The character set contains:

```text
ABCDEFGHIJKLMNOPQRSTUVWXYZ
abcdefghijklmnopqrstuvwxyz
0123456789
!@#$%&*
```

Therefore, a generated password can look like:

```text
G7@kP2!xQ9#m
```

or:

```text
aT8$Lm2&Qp7!
```

> ⚠️ The actual password changes with each generation.

---

# 🎛️ Button Configuration

The project uses the onboard physical buttons as the user interface.

### BTN0

```text
BTN0 → Generate Password
```

### BTN1

```text
BTN1 → Generate Password
```

The buttons are **manually initialized** by the application instead of relying entirely on automatic button initialization.

This provides direct control over the GPIO configuration and button-state handling.

---

# 🔄 WORKING PRINCIPLE

The Project operates as follows:


                START
                |
                v
       Initialize SiWG917
                |
                v
       Manually initialize
          BTN0 and BTN1
                |
                v
        Display project menu
                |
                v
        Read button states
                |
          +-----+-----+
          |           |
       BTN0         BTN1
          |           |
          v           v
     Generate      Generate
     password      password
          |           |
          +-----+-----+
                |
                v
      Display password
                |
                v
          Continue loop          
              

---

# 🧠 Password Generation Algorithm

The password generator follows a simple algorithm.

START
   │
   ↓
Initialize system
   │
   ↓
Initialize BTN0 and BTN1
   │
   ↓
Create character set
   │
   ↓
Wait for button press
   │
   ↓
Generate random index
   │
   ↓
Select character from character set
   │
   ↓
Repeat until password length is reached
   │
   ↓
Add string terminator '\0'
   │
   ↓
Display password
   │
   ↓
Wait for next button press


---

# 🔢 Random Character Selection

The generator maintains a character set containing all allowed characters:

```c
const char charset[] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789"
    "!@#$%&*";
```

For every password position, a random index is generated.



# 🖥️ Serial Terminal Output

After flashing the board, open a serial terminal at:

```text
Baud Rate : 115200
```
===========================================
            PASSWORD GENERATOR
===========================================
SiWG917 System Started Successfully

BUTTON CONTROL
---------------------
BTN0 = Generate Password
BTN1 = Generate New Password

Password Length : 12

Initializing BTN0...
Initializing BTN1...
Manual button initialization complete.

READY
Press BTN0 or BTN1 to generate a password.
===========================================

BTN0 PRESSED
Generating Password...

===========================================
            PASSWORD GENERATOR
===========================================
Generated Password : Zq3!mA7#Lp2@
Password Length     : 12
===========================================

BTN1 PRESSED
Generating New Password...
            
---

# 🔐 Character Categories

Each password can contain four categories of characters:

| Category | Characters |
|---|---|
| 🔠 Uppercase | `A-Z` |
| 🔡 Lowercase | `a-z` |
| 🔢 Numbers | `0-9` |
| 🔣 Special | `! @ # $ % & *` |

This provides a larger character pool compared with generating passwords using only letters or numbers.

---

# 🏗️ Project Architecture

The project can be viewed as four functional modules:

```text
┌──────────────────────────┐
│      Button Interface    │
│       BTN0 / BTN1        │
└────────────┬─────────────┘
             ↓
┌──────────────────────────┐
│    Button State Logic    │
│  Press Detection / GPIO  │
└────────────┬─────────────┘
             ↓
┌──────────────────────────┐
│   Password Generator     │
│ Random Character Select  │
└────────────┬─────────────┘
             ↓
┌──────────────────────────┐
│     UART / Terminal      │
│   Generated Password     │
└──────────────────────────┘
```

---

# 🚀 Setup Instructions

## 1. Open the Project

Open the project in **Simplicity Studio 6** and select:

```text
Target: BRD2605A
```

---

## 2. Verify Software Components

Make sure the required GPIO/button components and other project dependencies are available.

The project uses the SiWG917 GPIO functionality for onboard button control.

---

## 3. Open in VS Code

Open the project using the Silicon Labs extension in **Visual Studio Code**.

Select the appropriate GCC configuration.

---

## 4. Build

Perform:

```text
Clean
   ↓
Build
```

If the build completes successfully, the firmware is ready to flash.

---

# ⚡ Flashing

1. Connect the **BRD2605A Dev Kit** to the computer using USB.
2. Open the project in Simplicity Studio or VS Code.
3. Build the project.
4. Flash the firmware to the board.
5. Open the serial terminal.
6. Set the baud rate to:

```text
115200
```

7. Reset the board.

---

# 🧪 Testing

### Test 1 — Board Startup

After reset, verify that the terminal displays:

```text
RANDOM PASSWORD GENERATOR
SiWG917 System Started Successfully
```

---

### Test 2 — BTN0

Press **BTN0**.

Expected result:

```text
BTN0 PRESSED
NEW PASSWORD GENERATED
Password : X7@kP2!mQ9#
```

---

### Test 3 — BTN1

Press **BTN1**.

Expected result:

```text
BTN1 PRESSED
NEW PASSWORD GENERATED
Password : pT8$Lm2&Zq7!
```

---

### Test 4 — Multiple Generations

Press the button multiple times.

The terminal should display a new password for each valid button press.

---

# 🌟 Key Embedded Concepts Demonstrated

This project provides practical exposure to:

- **GPIO configuration**
- **Push-button interfacing**
- **Manual peripheral initialization**
- **Button-state detection**
- **Debouncing / press handling**
- **Random number generation**
- **Arrays**
- **Character strings**
- **Loops**
- **Conditional statements**
- **UART / serial communication**
- **Embedded C programming**
- **Silicon Labs SiWG917 development**

---

# 📌 Applications

The concept can be extended to:

- 🔐 IoT device credential generation
- 🏠 Smart-home access systems
- 🚪 Electronic door-lock systems
- 📡 Wi-Fi device provisioning
- 🔑 Temporary access credentials
- 🖥️ Embedded security demonstrations
- 📱 Device pairing systems
- 🏭 Industrial device authentication

---

# ⚠️ Security Note

This project is primarily an **embedded-system demonstration**.

If the generated passwords are intended for real authentication or security-critical applications, a **cryptographically secure random-number source** should be used instead of relying solely on a basic `rand()` implementation.

Passwords should also not be stored or transmitted insecurely.

---

# 🔮 Future Enhancements

Possible improvements include:

- 🔢 User-selectable password length
- 🔠 Individual enable/disable controls for character types
- 🖥️ OLED/LCD password display
- 📋 Password copy/export functionality
- 🔐 Hardware-based cryptographically secure random generation
- 💾 Secure password storage
- 📶 Wi-Fi-based password delivery
- 📱 Mobile/web interface
- ⏱️ Automatic password expiry
- 🔄 Password regeneration using a dedicated button
- 🔒 Secure device provisioning

---

# 📈 Future Version 

A more advanced version could work like this:

```text
             ┌──────────────┐
             │   SiWG917    │
             └──────┬───────┘
                    │
       ┌────────────┼────────────┐
       ↓            ↓            ↓
   Push Button    Secure RNG   Wi-Fi
       │            │            │
       └────────────┼────────────┘
                    ↓
          ┌─────────────────┐
          │ Password Engine │
          └────────┬────────┘
                   ↓
          ┌─────────────────┐
          │ OLED / Web App  │
          └─────────────────┘
```

---

# 📄 License

This project may include portions based on Silicon Labs WiSeConnect 3 SDK example projects.

Any adapted source files should retain the applicable **Silicon Labs Master Software License Agreement / Zlib license notices** included in their original source headers.

---
