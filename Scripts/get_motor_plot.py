import argparse
import serial
import pandas as pd
from serial.tools import list_ports
from time import sleep

def set_pwm(left_pwm, right_pwm, moto_board, encoding):
    left_dir = 0 if left_pwm>=0 else 1
    right_dir = 0 if right_pwm>=0 else 1
    left_pwm = abs(left_pwm)
    right_pwm = abs(right_pwm)
    moto_board.write('>{left_dir}#{left_pwm}#{right_pwm}#{right_dir}'.encode(encoding))


def get_encoder_readouts(moto_board, encoding, readout_count, delay):
    left_readout = 0.0
    right_readout = 0.0
    for _ in range(readout_count):
        moto_board.write('<'.encode(encoding))
        response = moto_board.readline().split('#')
        left_readout += float(response[0])
        right_readout += float(response[1])
        sleep(delay)
    left_readout /= readout_count
    right_readout /= readout_count
    return left_readout, right_readout



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
    moto_board.write(bytes('<', args.encoding))
    print(moto_board.readline().decode(args.encoding))
    set_pwm(125,125,moto_board,args.encoding)
    left, right = get_encoder_readouts(moto_board, args.encoding,
            args.readout_count, args.readout_delay)
    print(f'{left} {right}')

def parse_arguments():
    parser = argparse.ArgumentParser()
    parser.add_argument('-p', '--port',
            type=str,
            default=None,
            help='Serial port at wchich MotoBoard is connected')
    parser.add_argument('-b', '--baudrate', 
            type=int,
            default=9600,
            help='Baudrate for serial communication')
    parser.add_argument('-e', '--encoding',
            type=str,
            default='utf-8',
            help='String encoding for serial comunication')
    parser.add_argument('-c', '--readout_count',
            type=int,
            default=5,
            help='Number of readouts for single pwm setting')
    parser.add_argument('-d', '--readout_delay',
            type=int,
            default=2,
            help='Delay, in seconds, between two readouts.')
    return parser.parse_args()

if __name__ == '__main__':
    main(parse_arguments())
