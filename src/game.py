from ctypes import CDLL, CFUNCTYPE, POINTER, Structure, c_char, c_bool, c_int, c_void_p, c_wchar_p

class Piece(Structure):
    _fields_ = [
        ("pieceType", c_char),
        ("moveType", c_int),
        ("side", c_int),
        ("prefix", c_wchar_p),
        ("suffix", c_wchar_p),
        ("movements", c_void_p)  # Placeholder for movements (not sure how to handle it)
    ]

class Node(Structure):
    pass

class Node(Structure):
    _fields_ = [
        ("info", c_char),
        ("piecePresent", c_bool),
        ("pieceHeld", POINTER(Piece)),
        ("xOffset", c_int),
        ("yOffset", c_int),
        ("landingSpot", c_bool),
        ("up", POINTER(Node)),
        ("down", POINTER(Node)),
        ("left", POINTER(Node)),
        ("right", POINTER(Node))
    ]

libboard = CDLL('./game.so')

printMap = libboard.printMap
printMap.restype = None  # Assumes printMap returns void

nodeDataPrintout = libboard.nodeDataPrintout
nodeDataPrintout.argtypes = [POINTER(Node)]  # Assuming Node* is a typedef or struct

movingAround = libboard.movingAround
movingAround.argtypes = [POINTER(Node)]
movingAround.restype = POINTER(Node)

nodePopulation = libboard.nodePopulation
nodePopulation.restype = None  # Assumes nodePopulation returns void

usePiece = libboard.usePiece
usePiece.argtypes = [POINTER(Node)]

nodeCreation = libboard.nodeCreation
nodeCreation.restype = POINTER(Node)

inPath = libboard.inPath
inPath.argtypes = [POINTER(Node)]
inPath.restype = c_bool

movedPiece = libboard.movedPiece
movedPiece.restype = None


tL = libboard.getTL
tL.restype = POINTER(Node)
tR = libboard.getTR
tR.restype = POINTER(Node)
bL = libboard.getBL
bL.restype = POINTER(Node)
bR = libboard.getBR
bR.restype = POINTER(Node)

curr = libboard.getCURR
curr.restype = POINTER(Node)
sel = libboard.getSEL
sel.restype = POINTER(Node)


def printMap_wrapper():
    return printMap()

def nodeDataPrintout_wrapper(node_ptr):
    return nodeDataPrintout(node_ptr)

def movingAround_wrapper(node_ptr):
    return movingAround(node_ptr)

def nodePopulation_wrapper():
    return nodePopulation()

def usePiece_wrapper(node_ptr):
    return usePiece(node_ptr)

def nodeCreation_wrapper(node_ptr):
    return nodeCreation()

def inPath_wrapper(node_ptr):
    return inPath(node_ptr)

def movedPiece_wrapper():
    return movedPiece()

def TL_wrapper():
    return tL()
def TR_wrapper():
    return tR()
def BL_wrapper():
    return bL()
def BR_wrapper():
    return bR()
def CURR_wrapper():
    return curr()
def SEL_wrapper():
    return sel()

if __name__ == "__main__":
    nodePopulation_wrapper()
    # printMap_wrapper()
    movingAround_wrapper(TL_wrapper())