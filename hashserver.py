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
	fname = "{}".format(time.time())
	f = open(fname, "wb")
	data = sock.recv(1024)
	print(data)
	num, flen = struct.unpack("iq", data)
	print("num is: ", num, " flen is: ",flen)
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
	print(num)
	if num == 7 or num == 8:
		output = hashDict[num](open(fname, "rb").read()).hexdigest(255)
	else:
		output = hashDict[num](open(fname, "rb").read()).hexdigest()
	print(output)
	f.close()
	sendOutput(sock, output)


def sendOutput(sock, output):
	outlen = struct.pack("i", len(output))
	sock.send(outlen)
	sock.send(output.encode())
	pass


def serverLoop(sock):
	sock.listen(1)
	print(1)
	while True:
		print(2)
		conn, addr = sock.accept()
		print(3)
		getFile(conn)
		print(4)
	pass


def main():
	HOST = "127.0.0.1"
	PORT = 1234
	print("-1")
	sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	sock.bind((HOST, PORT))
	print("0")
	serverLoop(sock)


if __name__ == "__main__":
	main()
