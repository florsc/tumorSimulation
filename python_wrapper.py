
import ctypes


lib = ctypes.cdll['./cmake-build-debug/libtest.so']
test = lib['test']
print(test())
print("abcd")