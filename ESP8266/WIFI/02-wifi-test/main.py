import socket

def send_command(command):
    host = '192.168.137.104'  # Replace with the IP address of your ESP8266
    port = 80
    
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((host, port))
        s.sendall(command.encode())
        response = s.recv(1024)
        print('Received:', response.decode())

# Example usage:
send_command('1')  # Turn LED on
send_command('0')  # Turn LED off
