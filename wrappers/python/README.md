# Python Wrapper for MLKEM Library

This Python script (`pythonWrapper.py`) provides a wrapper for the MLKEM (Module-Lattice based Key Encapsulation Mechanism) cryptographic library. It allows you to use MLKEM's key generation, encapsulation, and decapsulation functions within your Python projects.

## Prerequisites

* **MLKEM Library:** You need to have the compiled MLKEM library (`mlkem.dll` on Windows or `libmlkem.so` on Linux) in the same directory as this Python script.  Ensure the library is built for your system's architecture (32-bit or 64-bit) and is compatible with Python.
* **Python:** Python 3.x is recommended.

## Installation

1.  **Place the Library:** Copy the `mlkem.dll` (Windows) or `libmlkem.so` (Linux) file into the same directory as `pythonWrapper.py`.
2.  **No further installation is required** as it's a single Python script.

## Usage

1.  **Import the wrapper:**

    ```python
    from pythonWrapper import MLKEM512, MLKEM768, MLKEM1024
    ```

2.  **Choose an MLKEM variant:** The wrapper supports MLKEM-512, MLKEM-768, and MLKEM-1024.  Select the class corresponding to the variant you want to use.

3.  **Use the functions:** Each class provides the following methods:

    * `keyGen()`:  Generates the public and private keys.
    * `encaps()`:   Encapsulates a shared key using the public key.
    * `decaps(dk, c)`: Decapsulates the shared key using the private key and the encapsulated ciphertext.

## Class Details

### `MLKEM512`

* Provides access to the MLKEM-512 variant.
* `keyGen()`:
    * Returns: The decryption key (`dk`) as a c_uint8 array.
* `encaps()`:
    * Returns: A tuple containing the shared key (`K`) as a c_uint8 array and the ciphertext (`c`) as a c_uint8 array.
* `decaps(dk, c)`:
    * Parameters:
        * `dk`: The decryption key (private key) as a c_uint8 array.
        * `c`:  The ciphertext as a c_uint8 array.
    * Returns: The shared key (`K`) as a c_uint8 array.

### `MLKEM768`

* Provides access to the MLKEM-768 variant.
* Function signatures are the same as `MLKEM512`.

### `MLKEM1024`

* Provides access to the MLKEM-1024 variant.
* Function signatures are the same as `MLKEM512`.

## Example

```python
from pythonWrapper import MLKEM512

# Initialize MLKEM-512
kem = MLKEM512()

# Key Generation
private_key = kem.keyGen()
print(f"Private Key (dk): {private_key}")

# Encapsulation
shared_key, ciphertext = kem.encaps()
print(f"Shared Key (K): {shared_key}")
print(f"Ciphertext (c): {ciphertext}")

# Decapsulation
derived_shared_key = kem.decaps(private_key, ciphertext)
print(f"Derived Shared Key: {derived_shared_key}")

# Verify that the shared keys match
assert shared_key == derived_shared_key
print("Key exchange successful!")