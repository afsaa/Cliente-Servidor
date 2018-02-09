import zmq
import sys
import os

def loadFiles(path):
    files = {}
    dataDir = os.fsencode(path)
    for file in os.listdir(dataDir):
        filename = os.fsdecode(file)
        print("Loading {}".format(filename))
        files[filename] = file
    return files

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

    piece_size = 1024 #Partes de 1Megabyte
    while True:
        msg = s.recv_json()
        if msg["op"] == "list":
            s.send_json({"files": list(files.keys())})
        elif msg["op"] == "download":
            filename = msg["file"]
            with open(directory + filename) as input, open("out_file", "wb") as out_file:
                while True
                    piece = input.read(piece_size)

                    if piece == "":
                        break #Fin del archivo
                    out_file.write(piece)
                s.send(out_file) #Envío del archivo completo
        else:
            print("JAJA!!")
            s.send_string("")
        else:
            print("Unsupported action!")
if __name__ == '__main__':
    main()
