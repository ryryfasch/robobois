import bluetooth
import serial

socket = bluetooth.BluetoothSocket( bluetooth.RFCOMM )

try :
    # Replace the MAC address
    socket.connect(("98:D3:A1:FD:35:E4", 1))
    print("connected")
except bluetooth.BluetoothError : raise

try:
    while True:
        # data = socket.recv(1024)
        # if len(data) == 0: break
        # print("received [%s]" % data.encode("hex"))
        # send LifeSign message
        socket.send("a");
except IOError:
    pass

print("disconnected")

socket.close()
print("all done")
