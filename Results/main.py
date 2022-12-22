import numpy as np


def format_results(fn_ref, fn_res):
    line = 0

    final_file = open(r"D:\Documents\GitHub\gui-lf\out_res\res.txt", 'w')

    file_ref = open(fn_ref, 'r')
    lines_ref = file_ref.readlines()

    file_res = open(fn_res, 'r')
    lines_res = file_res.readlines()

    while line < 272:
        tmp = lines_ref[line].split(";")
        final_file.write(tmp[0] + "  " + lines_res[line].removesuffix("\n") + "  " + tmp[1])
        line += 1


if __name__ == '__main__':
    format_results(r"D:\Documents\GitHub\gui-lf\order_R1.txt", r"C:\Users\Asus\Temp\tests_R1_22_12_2022_50.txt")
