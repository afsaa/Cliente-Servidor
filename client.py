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

    if operation == "list": # operacion listar musica del servidor
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
        partes = s.recv_json()
        print("la cancion contiene {} partes".format(partes))
        s.send_json("")
        m=int(partes["parts"])
        i=0
        while (i < m):
        	file=s.recv()
	        with open( name  + ".mp3", "ab") as output:
	            output.write(file)
	            s.send_json("")
	        i=i+1    


        print("All done!!")

    else: #en caso de escribir una operacion inexistente
        print("Error!!! unsupported operation")

    print("Connecting to server {} at {}".format(ip, port))

if __name__ == '__main__':
    main()
