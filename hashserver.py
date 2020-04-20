#!/usr/bin/python3
import socket
import hashlib
import struct
import time
import argparse
import sys

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
	fname = "{}".format(time.time())
	f = open(fname, "wb")
	data = sock.recv(16)
	num, flen = struct.unpack("iq", data)
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
	f.close()
	if num == 7 or num == 8:
		output = hashDict[num](open(fname, "rb").read()).hexdigest(255)
	else:
		output = hashDict[num](open(fname, "rb").read()).hexdigest()
	f.close()
	sendOutput(sock, output)
	return 1


def sendOutput(sock, output):
	outlen = struct.pack("i", len(output))
	sock.send(outlen)
	sock.send(output.encode())


def serverLoop(sock):
	sock.listen(1)
	while True:
		print("waiting for connection")
		conn, addr = sock.accept()
		print("connected to {}".format(addr[0]))
		while True:
			if getFile(conn) == -1:
				break
			data = conn.recv(1024)
			num, flen = struct.unpack("iq", data)
			if num == 0:
				break
	pass


def main():
	parser = argparse.ArgumentParser()
	parser.add_argument("--port", type=int, default=1234, dest="PORT")
	parser.add_argument("--host", type=str, default="127.0.0.1", dest="HOST")
	args = parser.parse_args()
	sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	sock.bind((args.HOST, args.PORT))
	serverLoop(sock)


if __name__ == "__main__":
	if sys.version_info.major != 3:
		print("This script requirres python version 3.X")
		exit()
	main()
