import ctypes
from ctypes import CDLL, Structure, c_uint8

# Load the DLL
mlkem = CDLL("./mlkem.dll")

# MLKEM 512 structs
class Keys512(Structure):
    # Try with _pack_ = 1 and without it
    # _pack_ = 1
    _fields_ = [("ek", c_uint8 * 800),
                ("dk", c_uint8 * 1632)]
    
class KeyCipher512(Structure):
    _fields_ = [("key", c_uint8 * 32),
                ("c", c_uint8 * 768)]
    
# MLKEM 768 structs
class Keys768(Structure):
    # Try with _pack_ = 1 and without it
    # _pack_ = 1
    _fields_ = [("ek", c_uint8 * 1184),
                ("dk", c_uint8 * 2400)]
    
class KeyCipher768(Structure):
    _fields_ = [("key", c_uint8 * 32),
                ("c", c_uint8 * 1088)]

# MLKEM 1024 structs
class Keys1024(Structure):
    # Try with _pack_ = 1 and without it
    # _pack_ = 1
    _fields_ = [("ek", c_uint8 * 1568),
                ("dk", c_uint8 * 3168)]
    
class KeyCipher1024(Structure):
    _fields_ = [("key", c_uint8 * 32),
                ("c", c_uint8 * 1568)]
    
# Shared Key struct
class Key(Structure):
    _fields_ = [("K", c_uint8 * 32)]

# Declare function signatures BEFORE the first call
mlkem.mlkemKeyGen_512.restype = Keys512
mlkem.mlkemEncaps_512.restype = KeyCipher512
mlkem.mlkemEncaps_512.argtypes = [c_uint8 * 800]
mlkem.mlkemDecaps_512.restype = Key
mlkem.mlkemDecaps_512.argtypes = [c_uint8 * 1632, c_uint8 * 768]

mlkem.mlkemKeyGen_768.restype = Keys768
mlkem.mlkemEncaps_768.restype = KeyCipher768
mlkem.mlkemEncaps_768.argtypes = [c_uint8 * 1184]
mlkem.mlkemDecaps_768.restype = Key
mlkem.mlkemDecaps_768.argtypes = [c_uint8 * 2400, c_uint8 * 1088]

mlkem.mlkemKeyGen_1024.restype = Keys1024
mlkem.mlkemEncaps_1024.restype = KeyCipher1024
mlkem.mlkemEncaps_1024.argtypes = [c_uint8 * 1568]
mlkem.mlkemDecaps_1024.restype = Key
mlkem.mlkemDecaps_1024.argtypes = [c_uint8 * 3168, c_uint8 * 1568]

def mlkemKeyGen512():
    keys = mlkem.mlkemKeyGen_512()
    return keys.ek, keys.dk

def mlkemEncaps512(ek):
    kc = mlkem.mlkemEncaps_512(ek)
    return kc.key, kc.c

def mlkemDecaps512(dk, c):
    k = mlkem.mlkemDecaps_512(dk, c)
    return k.K

def mlkemKeyGen768():
    keys = mlkem.mlkemKeyGen_768()
    return keys.ek, keys.dk

def mlkemEncaps768(ek):
    kc = mlkem.mlkemEncaps_768(ek)
    return kc.key, kc.c

def mlkemDecaps768(dk, c):
    k = mlkem.mlkemDecaps_768(dk, c)
    return k.K

def mlkemKeyGen1024():
    keys = mlkem.mlkemKeyGen_1024()
    return keys.ek, keys.dk

def mlkemEncaps1024(ek):
    kc = mlkem.mlkemEncaps_1024(ek)
    return kc.key, kc.c

def mlkemDecaps1024(dk, c):
    k = mlkem.mlkemDecaps_1024(dk, c)
    return k.K

class MLKEM512:
    def __init__(self):
        self._ek = ""
        self._dk = ""
        self._c = ""
        self._K = ""
    
    def keyGen(self):
        self._ek, self._dk = mlkemKeyGen512()
        return self._dk

    def encaps(self):
        self._K, self._c = mlkemEncaps512(self._ek)
        return self._K, self._c

    def decaps(self, dk, c):
        self._K = mlkemDecaps512(dk, c)
        return self._K
    
class MLKEM768:
    def __init__(self):
        self._ek = ""
        self._dk = ""
        self._c = ""
        self._K = ""
    
    def keyGen(self):
        self._ek, self._dk = mlkemKeyGen768()
        return self._dk

    def encaps(self):
        self._K, self._c = mlkemEncaps768(self._ek)
        return self._K, self._c

    def decaps(self, dk, c):
        self._K = mlkemDecaps768(dk, c)
        return self._K
    
class MLKEM1024:
    def __init__(self):
        self._ek = ""
        self._dk = ""
        self._c = ""
        self._K = ""
    
    def keyGen(self):
        self._ek, self._dk = mlkemKeyGen1024()
        return self._dk

    def encaps(self):
        self._K, self._c = mlkemEncaps1024(self._ek)
        return self._K, self._c

    def decaps(self, dk, c):
        self._K = mlkemDecaps1024(dk, c)
        return self._K