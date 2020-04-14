import socket
import hashlib
import struct
import time


def getFile(sock):
    hashDict = {1: hashlib.md5,
                2: hashlib.sha1,
                3: hashlib.sha224,
                4: hashlib.sha256,
                5: hashlib.sha384,
                6: hashlib.sha512,
                7: hashlib.shake_128,
                8: hashlib.shake_256,
                9: hashlib.blake2b}

    f = open(time.time(), "wb")
    data = sock.recv(8)
    num, flen = struct.unpack("ii", data)
    if num not in hashDict.keys():
        return -1
    recvlen = 0
    while True:
        if recvlen == flen:
            break
        data = sock.recv(1024)
        recvlen += len(data)
        f.write(data)
    f.seek(0)
    if num == 7 or num == 8:
        output = hashDict[num](open(f, "rb").read()).hexdigest(255)
    else:
        output = hashDict[num](open(f, "rb").read()).hexdigest()
    sendOutput(sock, output)


def sendOutput(sock, output):
    pass


def serverLoop(sock):
    sock.listen(1)
    while True:
        conn, addr = sock.accept()
        getFile(conn)
    pass


def main():
    HOST = "127.0.0.1"
    PORT = 1234
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.bind((HOST, PORT))
    serverLoop(sock)
