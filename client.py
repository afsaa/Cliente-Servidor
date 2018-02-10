import zmq
import sys

def main():
    if len(sys.argv) != 4:
        print("Error!!!")
        exit()
    ip = sys.argv[1] #Server´s IP
    port = sys.argv[2] #Server´s port
    operation = sys.argv[3] #Operation to perform

    context = zmq.Context() #Realiza el proceso de encolamiento de las solicitudes de los clientes
    s = context.socket(zmq.REQ)
    s.connect("tcp://{}:{}".format(ip, port)) #Conexión del socket

    if operation == "list":
        s.send_json({"op":"list"})
        files = s.recv_json()
        print(files)

    elif operation == "download":
        name = input("File to download? ")
        s.send_json({"op": "download", "file": name})
        file = s.recv()
        with open("descarga.algo", "wb") as output:
            output.write(file)

    elif operation == "search_piece": #Buscar el número de partes de una canción
        name = input("Whats the name of the song? ")
        s.send_json({"op": "search_piece", "file": name})

    elif operation == "download_piece": #Descarga de partes específicas
        name = input("Whats the name of the song? ")
        piece = input("Number of piece to download? ")
        s.send_json({"op": "download_piece", "file": name, "piece": piece})
        file = s.recv()
        with open("descarga_parte.algo", "wb") as output:
            output.write(file)

    else:
        print("Error!!! unsupported operation")

    print("Connecting to server {} at {}".format(ip, port))

if __name__ == '__main__':
    main()
