import argparse
import serial
import pandas as pd
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

def main(args):
    if args.port is None:
        args.port = interactive_port_selection()
    if args.port is None:
        return
    moto_board = serial.Serial(args.port, args.baudrate)
    sleep(2)
    print('WRITING')
    moto_board.write(bytes('<', args.encoding))
    print('READING')
    print(moto_board.readline().decode(args.encoding))

def parse_arguments():
    parser = argparse.ArgumentParser()
    parser.add_argument('-p',
            '--port',
            type=str,
            default=None,
            help='Serial port at wchich MotoBoard is connected')
    parser.add_argument('-b', 
            '--baudrate', 
            type=int,
            default=9600,
            help='Baudrate for serial communication')
    parser.add_argument('-e', '--encoding', type=str, default='utf-8',
            help='String encoding for serial comunication')

    return parser.parse_args()

if __name__ == '__main__':
    main(parse_arguments())
