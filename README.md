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
- **OpenSSL** (for sha3 and shake)
- **CMake** (for cross-platform builds)

  *This project uses BoringSSL's RNG function, since Configuring OpenSSL for fips mode is complicated.**
- **BoringSSL** (for secure RNG)

### Installing Dependencies
**Windows**
Install OpenSSL from [Shining Light Productions](https://slproweb.com/products/Win32OpenSSL.html).
Install the full version, not the Light version as the Light version does not include /lib and /include that 
CMake uses

Once OpenSSL is installed, add its path to your PATH environment variable

**Linux**
```sh
sudo apt update
sudo apt install openssl libssl-dev cmake g++
```

## 🚀 Build Instructions
Follow these steps to build the project:

1. **Clone the Repository**
```sh
git clone git@github.com:KaiGVilbig/MLKEM.git
cd MLKEM
```

2. **Clone the BoringSSL Repository into `external/boringssl`
```sh
git clone https://github.com/google/boringssl.git external/boringssl
```

3. **Configure the Build System**
```sh
cmake -B build
```

4. **Build the Project**
```sh
cmake --build build --config Debug
```

5. **(Optional) Clean the Build**
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
===============================
 ML-KEM Library Test Suite
===============================

Test Support Functions
-------------------------------

[TEST] Running Bits to Bytes conversion function Test...
[PASS] Bits to Bytes conversion executed successfully

[TEST] Running Bytes to Bits conversion function Test...
[PASS] Bytes to Bits conversion executed successfully

[TEST] Running Byte Encode/Decode function Test...
[PASS] ByteEncode/Decode round-trip passed for d = 1
[PASS] ByteEncode/Decode round-trip passed for d = 2
[PASS] ByteEncode/Decode round-trip passed for d = 3
[PASS] ByteEncode/Decode round-trip passed for d = 4
[PASS] ByteEncode/Decode round-trip passed for d = 5
[PASS] ByteEncode/Decode round-trip passed for d = 6
[PASS] ByteEncode/Decode round-trip passed for d = 7
[PASS] ByteEncode/Decode round-trip passed for d = 8
[PASS] ByteEncode/Decode round-trip passed for d = 9
[PASS] ByteEncode/Decode round-trip passed for d = 10
[PASS] ByteEncode/Decode round-trip passed for d = 11
[PASS] ByteEncode/Decode round-trip passed for d = 12

[TEST] Running Hash function H Test...
[PASS] Hash function H executed successfully
[TEST] Running Hash function J Test...
[PASS] Hash function J executed successfully
[TEST] Running Hash function G Test...
[PASS] Hash function G executed successfully

[TEST] Running NTT and inverseNTT function Test...
[PASS] NTT and inverseNTT executed successfully

[TEST] Running NTT and inverseNTT function Test...
[PASS] multiplyNTT returned executed size successfully
[PASS] multiplyNTT returned executed output successfully

Support Functions Tests Completed
9 tests passed, 0 tests failed
-------------------------------

Test Main Functions
-------------------------------

[PASS] K-PKE.KeyGen(MLKEM512) completed!
[PASS] K-PKE.Encrypt(MLKEM512) completed!
[PASS] K-PKE.Decrypt(MLKEM512): shared secret key K successfully recovered.

[PASS] K-PKE.KeyGen(MLKEM768) completed!
[PASS] K-PKE.Encrypt(MLKEM768) completed!
[PASS] K-PKE.Decrypt(MLKEM768): shared secret key K successfully recovered.

[PASS] K-PKE.KeyGen(MLKEM1024) completed!
[PASS] K-PKE.Encrypt(MLKEM1024) completed!
[PASS] K-PKE.Decrypt(MLKEM1024): shared secret key K successfully recovered.

-------------------------------

All tests passed

===============================
```

## 📄 Known Issues
- have not tested other methods of building on windows such as g++, or build systems like Ninja