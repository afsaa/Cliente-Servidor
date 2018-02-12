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

    piece_size = 1024*1024 #Partes de 1Megabyte
    while True:
        msg = s.recv_json()
        if msg["op"] == "list":
            s.send_json({"files": list(files.keys())})

        elif msg["op"] == "search_piece":
            filename = msg["file"]
            with open(directory + filename, "rb") as input:
                n = 0
                while True:
                    if n = 0:
                        data = input.read(piece_size)
                    else:
                        piece = input.seek(piece_size*n)
                    if piece == "":
                        break #Fin del archivo
                    else:
                        n = n +1
                        print (n)

        elif msg["op"] == "download_piece":
            filename = msg["file"]
            filepiece = msg["piece"]
            pieces_list = [] #Creamos la lista de piezas
            with open(directory + filename + filepiece) as input, open("out_file", "wb") as out_file:
                while True:
                    piece = input.read(piece_size)
                    if piece == "":
                        break #Fin del archivo
                    else:
                        pieces_list.append(piece) #Agregamos las piezas de la canción a la lista

                out_file.write(pieces_list[filepiece]) #En el archivo de salida se escribirá la pieza de la canción que se busca
                s.send(out_file) #Envío de la pieza
        else:
            print("JAJA!!")
            s.send_string("")
        # else:
        #     print("Unsupported action!")
if __name__ == '__main__':
    main()
