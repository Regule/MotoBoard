import argparse
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt


def main(args):
    dataset = pd.read_csv(args.input_file)
    pwm = pd['pwm'].to_numpy()
    left = pd['left'].to_numpy()
    right = pd['right'].to_numpy()
    plt.plot(pwm, left)
    plt.plot(pwm, right)
    plt.show()

def parse_arguments():
    parser = argparse.ArgumentParser()
    parser.add_argument('-i', '--input_file', type=str, required=True)
    return parser.parse_args()

if __name__ == '__main__':
    main(parse_arguments)
