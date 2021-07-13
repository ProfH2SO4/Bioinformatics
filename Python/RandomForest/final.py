"""
DATE: 15.12.2020
Task:
Here are the two files (Class T, Class I) that you can use to learn the different sequences.

Class T contains random positions from human Transcripts.
Class I contains random positions from human Intergenic regions.

Characteristics of the files:

a) Class I has 10k sequences, Class T has 1k sequences. The same ration 10:1 will be present in the EVAL dataset

b) All sequences are 200nt long

c) The EVAL dataset will come from the same dataset (i.e. you can expect very similar data)

d) Evaluation will be performed as area under the Precision-Sensitivity curve (use Class T as the positive class).
You must make a script that runs on such files and produces this result.
"""

import itertools
import re


#
# Input: takes two .txt files(i_train = Intergenic region, t_train = Transcript)
# count all kmer3( i.e AAA,ACC) 64 permutations for each line
# Output: one .csv file with kmer3 frequencies in each line
# Data structure: Hashing, Collision solved by linear probing
class KmerArray:
    def __init__(self):
        # numbers of permutations
        self.count_array_3 = [(0, 0) for a in range(64)]
        self.kmer_3 = []
        self.count_nuc = 0  # count nucleotides in file
        self.template_kmer_3 = [None for k in range(64)]


def hash_it(hash_kmer: int, opt):  # collisions solved by using linear probing
    lin_prob = 0
    pos = hash_kmer % 64
    while opt.count_array_3[pos][0] != 0 and opt.count_array_3[pos][0] != hash_kmer:
        lin_prob += 1
        pos = (hash_kmer + lin_prob) % 64

    if opt.count_array_3[pos][0] == 0 or opt.count_array_3[pos][0] == hash_kmer:
        opt.count_array_3[pos] = list(opt.count_array_3[pos])
        opt.count_array_3[pos][0] = hash_kmer
        opt.count_array_3[pos][1] += 1
        opt.count_array_3[pos] = tuple(opt.count_array_3[pos])


# from seq makes specific number
def hash_kmer_seq(seq_kmer: [str]) -> int:
    # distinct_num
    g = 31
    hashed_kmer = 0
    for i in range(len(seq_kmer)):
        hashed_kmer = g * hashed_kmer + ord(seq_kmer[i])
    return hashed_kmer


# move seq -1 and del first element
def move_del_seq(seq) -> [str]:
    for i in range(len(seq) - 1):
        seq[i] = seq[i + 1]
    seq = seq[:-1]
    return seq


def make_arr_empty(opt: int):
    if opt == first_data:
        opt = first_data
    if opt == second_data:
        opt = second_data
    opt.kmer_3 = []
    opt.count_array_3 = [(0, 0) for a in range(64)]


def add_to_hash_ar(opt: int):
    if opt == first_data:  # if 1. file then ka if 2. ka2
        opt = first_data
    if opt == second_data:
        opt = second_data
    if len(opt.kmer_3) == 3:
        hash_it(hash_kmer_seq(''.join(opt.kmer_3)), opt)
        opt.kmer_3 = move_del_seq(opt.kmer_3)


def read_fasta(file: str, opt: int):
    if opt == 1:
        opt = first_data
    if opt == 2:
        opt = second_data
    with open(file, 'r') as fasta_f:
        lines = fasta_f.readlines()
        for i, line in enumerate(lines):
            if re.match("(seq)", line): continue
            mov_index = 0
            count_nuc = 0
            for nucleotide in range(mov_index, len(line)):
                if line[nucleotide] != '\n':
                    opt.kmer_3.append(line[nucleotide])

                add_to_hash_ar(opt)
                mov_index += 1
            for cn in range(len(line)):  # count all nucleotides
                count_nuc += 1
            w_to_file(count_nuc, opt)

            make_arr_empty(opt)


def file_header():
    data_file = open("data.csv", 'w')
    j = 0
    data_file.writelines(("Category", ''))

    for p in itertools.product(['A', 'C', 'G', 'T'], repeat=3):
        first_data.template_kmer_3[j] = ''.join(p)
        data_file.writelines((',', first_data.template_kmer_3[j]))
        j += 1
    data_file.writelines('\n')
    data_file.close()


def show_print(array: [str]):
    print(array)


def find_kmer(hash_seq: [str], opt: KmerArray) -> int:
    lin_prob = 0
    pos = hash_seq % 64
    while opt.count_array_3[pos][0] != 0 and opt.count_array_3[pos][0] != hash_seq:
        lin_prob += 1
        pos = (hash_seq + lin_prob) % 64
    if opt.count_array_3[pos][0] == 0:
        return 0
    if opt.count_array_3[pos][0] == hash_seq:
        return int(opt.count_array_3[pos][1])


def w_to_file(count_nuc, opt: KmerArray):
    freq_val = [0 for i in range(64)]
    data_file = open("data.csv", 'a')
    for kmer_pos in range(len(first_data.template_kmer_3)):
        kmer_count = find_kmer(hash_kmer_seq(first_data.template_kmer_3[kmer_pos]), opt)
        # print(ka.template_kmer_3[kmer_pos], kmer_count)
        freq_val[kmer_pos] = round(kmer_count / count_nuc, 3)
        # print(opt.template_kmer_3[kmer_pos], freq_val[kmer_pos])

    if opt == first_data:
        data_file.writelines((str(0), ''))
    else:
        data_file.writelines((str(1), ''))
    for k in range(len(freq_val)):
        data_file.writelines((',', str(freq_val[k])))
    data_file.writelines('\n')
    data_file.close()


if __name__ == "__main__":
    first_data = KmerArray()
    second_data = KmerArray()
    file_header()
    read_fasta("i_train.txt", 1)
    read_fasta("t_train.txt", 2)
