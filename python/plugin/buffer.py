import ctypes
from ctypes import *
from . import lib


def PointBuffer(wkt, distance, segments):

    PointBuffer = lib.c_PointBuffer
    PointBuffer.argtypes = [c_char_p, c_double, c_int]
    PointBuffer.restype = c_char_p

    geom = wkt.encode()
    result = PointBuffer(geom, distance, segments)
    print(result.decode())
    return result.decode()
def LineBuffer(wkt, distance, segments):

    LineBuffer = lib.c_LineBuffer
    LineBuffer.argtypes = [c_char_p, c_double, c_int]
    LineBuffer.restype = c_char_p

    geom = wkt.encode()
    result = LineBuffer(geom, distance, segments)
    print(result.decode())
    return result.decode()

def AreaBuffer(wkt, distance, segments):

    AreaBuffer = lib.c_AreaBuffer
    AreaBuffer.argtypes = [c_char_p, c_double, c_int]
    AreaBuffer.restype = c_char_p

    geom = wkt.encode()
    result = AreaBuffer(geom, distance, segments)
    print(result.decode())
    return result.decode()


def BufferMerger(wkts, num):
    BufferMerger = lib.c_BufferMerger
    BufferMerger.argtypes = [POINTER(c_char_p), c_int]
    BufferMerger.restype = c_char_p
    wkts_bytes = [wkt.encode() for wkt in wkts]
    wkts_ptr = (c_char_p * num)(*wkts_bytes)
    result = BufferMerger(wkts_ptr, num)
    print(result.decode())
    return result.decode()