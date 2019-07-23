import argparse
import shutil
import sys
from time import sleep

def tfill(text, delay):
    cols, rows = shutil.get_terminal_size((80, 20))

    text_len = len(text)
    num_texts = int(cols / text_len)
    for num_drawn in range(num_texts):
        fixed = num_drawn * text_len
        for right_edge in range(1, cols - fixed):
            visible = text[-right_edge:]
            s = ' ' * (right_edge - len(visible)) + visible
            
            print(f'\r{s}\r', end='')
            sleep(delay)
    print()


if __name__ == '__main__':
    parser = argparse.ArgumentParser('Fills the console with a piece of text '
                                     'as many times as it will fit.')
    parser.add_argument('-t', '--text', default=r'  ¯\_(ツ)_/¯',
                        help='The text that will be printed.')
    parser.add_argument('-d', '--delay', type=float, default=0.01,
                        help='How long to delay between printing each character.')
    
    args = parser.parse_args()
    tfill(args.text, args.delay)
