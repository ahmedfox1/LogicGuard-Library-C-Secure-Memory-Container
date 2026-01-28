# 🛡️ LogicGuard: The Ultimate C++ Secure Memory Container

![License](https://img.shields.io/badge/license-MIT-blue.svg) ![C++](https://img.shields.io/badge/std-C%2B%2B17-orange) ![Status](https://img.shields.io/badge/status-stable-green)

**LogicGuard** is a lightweight, header-only C++ library designed to protect sensitive data (passwords, API keys, tokens) from memory dumping attacks and runtime inspection tools like Cheat Engine.

Unlike standard `std::string` or `std::cin` which leave plaintext traces in RAM and Console History, **LogicGuard** ensures your data is encrypted, obfuscated, and wiped instantly.

## 🚀 Why LogicGuard?

In standard C++:
* `std::string s = "Secret";` -> Stored as **Plaintext** in `.rdata` section (Visible in Hex Editors).
* `std::cin >> s;` -> Leaves traces in **Console Input History** and **RAM**.
* **Result:** Any script kiddie with Cheat Engine can steal your data in seconds.

**LogicGuard solves this by providing:**
1.  **Compile-Time Obfuscation:** Hides hardcoded strings from binary analysis.
2.  **Secure Runtime Input:** Bypasses console buffer and encrypts keystrokes instantly.
3.  **Automatic Wiping:** Uses `volatile` destructors to zero-out memory upon scope exit.

## 🛠️ Key Features

* 🔒 **Zero-Trace Input:** Reads directly from keyboard (no buffer residue).
* 🎭 **Polymorphic Encryption:** Every variable gets a unique random key at runtime.
* 👻 **Compile-Time Obfuscation:** Use the `_S()` macro to hide string literals from the `.exe`.
* 🧹 **Secure Erasure:** Auto-wipes memory to prevent cold-boot attacks or dumps.
* 📦 **Header-Only:** No complex build systems. Just `#include "LogicGuard.h"`.

## 📦 Installation

Just copy `LogicGuard.h` to your project folder. That's it!

```cpp
#include "LogicGuard.h"
