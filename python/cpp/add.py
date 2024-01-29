import ctypes

add = ctypes.cdll.LoadLibrary('./add.c.so')
print("4 + 5 = " + str(add.add_int(4,5)))
add.add_float.restype = ctypes.c_float
print("5.5 + 4.1 = " + str(add.add_float(ctypes.c_float(5.5), ctypes.c_float(4.1))))


lib = ctypes.cdll.LoadLibrary("./add.cpp.so")
print(lib.add(1, 2))
lib.add.argtypes = [ctypes.c_int, ctypes.c_int]
lib.add.restype = ctypes.c_int
print(lib.add(1, 2))
