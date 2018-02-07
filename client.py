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
    else:
        print("Error!!! unsupported operation")
        
    print("Connecting to server {} at {}".format(ip, port))

if __name__ == '__main__':
    main()
