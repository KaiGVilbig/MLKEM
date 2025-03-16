# ML-KEM Implementation

This project is an implementation of the **Module-Lattice-Based Key Encapsulation Mechanism (ML-KEM)** following the guidelines outlined in **NIST FIPS 203**. The implementation is structured to ensure compliance with post-quantum cryptographic standards while maintaining clean, modular code design.

## 📋 Project Overview
This repository contains:
- **Key Generation (KeyGen)** — Generates secure public and private keys.
- **Polynomial Sampling (SamplePolyCBD)** — Efficient sampling from a centered binomial distribution.
- **Number Theoretic Transform (NTT)** — Efficient polynomial multiplication.
- **Encoding Functions (ByteEncode/ByteDecode)** — Encoding and decoding cryptographic data.
- **Support Utilities** — Secure random number generation and additional helpers.

## ⚙️ System Requirements
- **Operating System:** Windows 10/11 or Linux (Ubuntu 20.04+ recommended)
- **Compiler:** Visual Studio 2022 (Windows) or GCC 9.3+ (Linux)
- **CMake:** Version 3.10 or higher
- **OpenSSL:** Version 3.0 or higher (for cryptographically secure randomness)

## 📦 Project Dependencies
Ensure the following dependencies are installed:
- **OpenSSL** (for secure RNG)
- **CMake** (for cross-platform builds)

### Installing Dependencies
**Windows**
```sh
choco install openssl cmake
```

**Linux**
```sh
sudo apt update
sudo apt install openssl libssl-dev cmake g++
```

## 🚀 Build Instructions
Follow these steps to build the project:

1. **Clone the Repository**
```sh
git clone <repository_url>
cd mlkem_project
```

2. **Configure the Build System**
```sh
cmake -B build
```

3. **Build the Project**
```sh
cmake --build build --config Debug
```

4. **(Optional) Clean the Build**
```sh
cmake --build build --target clean
```

## ▶️ Running the Code
To run the ML-KEM implementation:

```sh
./build/mlkem_tests
```

## 🧪 Testing the Code
The project includes a test suite to ensure functionality.

1. **Build the Tests**
```sh
cmake --build build --config Debug
```

2. **Run the Tests**
```sh
./build/mlkem_tests
```

Expected Output:
```
[INFO] ML-KEM.KeyGen() called
[INFO] ML-KEM.KeyGen_internal() called
[INFO] SamplePolyCBD() called
[INFO] NTT() called
[INFO] inverseNTT() called
[INFO] ByteEncode() called
[INFO] ByteDecode() called
[INFO] ML-KEM.KeyGen_internal() completed
[INFO] ML-KEM.KeyGen() completed
```

## 📄 Known Issues
- Current implementation includes placeholder logic for most cryptographic functions, pending full algorithm integration.
- Ensure OpenSSL libraries are correctly linked when building the project.

## 📬 Contact
For questions, issues, or contributions, feel free to open an issue or submit a pull request.

