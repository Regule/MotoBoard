import argparse
import serial
import time
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
    readouts = 0
    print('Starting encoder readout.')
    for i in range(readout_count):
        print(f'Starting readout {i}')
        moto_board.write(bytes('<', encoding))
        response = moto_board.readline().decode(encoding)
        if len(response)!=0:
            response = response.split('#')
            left_readout += float(response[0])
            right_readout += float(response[1])
            readouts += 1
            print(f'Readout no.{i} completed ({left_readout} {right_readout}).')
        else:
            print('Readout failed due to timeout.')
        sleep(delay)
    left_readout /= readouts
    right_readout /= readouts
    print(f'Avarage readout left={left_readout} right={right_readout}')
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
    moto_board = serial.Serial(args.port, args.baudrate, timeout=args.timeout)
    sleep(2)
    moto_board.write(bytes('<', args.encoding))
    print(moto_board.readline().decode(args.encoding))
    print('Initializing motors')
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
    parser.add_argument('-t', '--timeout',
            type=int,
            default=1,
            help='Timeout in serial communication')
    return parser.parse_args()

if __name__ == '__main__':
    main(parse_arguments())
