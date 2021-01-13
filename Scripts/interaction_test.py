import serial
from serial.tools import list_ports
from time import sleep

def interactive_port_selection():
    ports = list(map(str,list_ports.comports()))
    if len(ports) == 0:
        print('No serial ports avaialble.')
        return None
    print('Ports available :')
    for choice, port in enumerate(ports):
        print(f'{choice} -> {port}')
    choice = int(input('Select port >'))
    try:
        return ports[choice].split()[0]
    except IndexError:
        print(f'No port at number {choice}')
        return None

if __name__ == '__main__':
    port = interactive_port_selection()
    port = serial.Serial(port, 9600, timeout=1)
    if port is not None:
        if port.is_open:
            print('Port open, wiriting.')
            port.write('>0#150#0#150'.encode('ASCII'))
            sleep(1)
            port.write('>0#150#0#150'.encode('ASCII'))
            sleep(1)
            port.write('>0#150#0#150'.encode('ASCII'))
            sleep(1)
            port.write('>0#150#0#150'.encode('ASCII'))
            sleep(1)
            port.write('>0#150#0#150'.encode('ASCII'))
            sleep(10)
            print('Now stopping')
            port.write('>0#000#0#000'.encode('ASCII'))
        else:
            print('Port is not open')

