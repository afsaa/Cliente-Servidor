import zmq
import sys
import os
from math import ceil

def loadFiles(path):
    files = {}
    dataDir = os.fsencode(path)
    for file in os.listdir(dataDir):
        filename = os.fsdecode(file)
        print("Loading {}".format(filename))
        files[filename] = file
    return files


def get_size_file(filename):
	sz =int(os.path.getsize("music/" + filename))
	#print(sz)
	return(sz)

def get_parts(filename):
	sz = get_size_file(filename)
	mega = sz / (1024*1024)
	partes = ceil(mega)
	print(partes)
	return(partes)

def main():
	if len(sys.argv) != 3:
	    print("Error!!!")
	    exit()


	directory = sys.argv[2]
	port = sys.argv[1]

	context = zmq.Context()
	s = context.socket(zmq.REP)
	s.bind("tcp://*:{}".format(port))

	files = loadFiles(directory)

	print(files)

	piece_size = 1024 * 1024 #1mb

	while True:
		msg = s.recv_json()

		#operacion listar
		if msg["op"] == "list":
			s.send_json({"files": list(files.keys())})

		#operacion descargar
		elif msg["op"] == "search_piece":
			filename = msg["file"]
			partes = get_parts(filename)
			s.send_json({"parts":partes})
			with open(directory + filename, "rb") as input:
				n=0
				input.seek(0)
				while True:
					s.recv_json()
					if n > partes:
						break
					piece_size=(1024*1024)
					data = input.read(piece_size)
					n = n + 1
					s.send(data)
					
		else:
			print("Unsupported action!")

if __name__ == '__main__':
    main()