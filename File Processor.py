# need to comment the line "import imp" in a package file after python 3.4

import os
import string
from nltk.stem.porter import PorterStemmer  # word stemming, need to install package "nltk"

porter_stemmer = PorterStemmer() # initialize PorterStemmer object

path = "./shakespeare" # original files' path
new_path = "./shakespeare_dealt" # new files' path

def remove_symbols(sentence): # eliminate the punctuation function
    del_estr = string.punctuation + string.digits
    replace = " "*len(del_estr)
    tran_tab = str.maketrans(del_estr, replace)
    sentence = sentence.translate(tran_tab)
    return sentence

word_stem_file = open("./stem.txt", 'w')

for dirpath, dirnames, filenames in os.walk(path): # eliminate the punctuation function, remaining space and do the word stemming
    for file in filenames: # loop among every file 
        fp = open(path + "/" + file, "r")
        temp_str = fp.read()
        temp_str = remove_symbols(temp_str)
        temp_str = temp_str.lower()
        temp_list = temp_str.split()
        for i, item in enumerate(temp_list): # store the original word and the result after word stemming
            temp_stem_word = porter_stemmer.stem(temp_list[i])
            word_stem_file.write(temp_list[i] + " " + temp_stem_word + " ")
            temp_list[i] = temp_stem_word
        temp_str=' '.join(temp_list)
        new_file = open(new_path + "/" + file, 'w')
        new_file.write(temp_str)