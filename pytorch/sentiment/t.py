from torchtext import data

from fastai.nlp import *



PATH = 'data/aclImdb/'



TRN_PATH = 'train/all/'

VAL_PATH = 'test/all/'

TRN = f'{PATH}{TRN_PATH}'

VAL = f'{PATH}{VAL_PATH}'



TEXT = data.Field(lower=True, tokenize="spacy")



bs = 64;

bptt = 70



FILES = dict(train=TRN_PATH, validation=VAL_PATH, test=VAL_PATH)

md = LanguageModelData.from_text_files(PATH, TEXT, **FILES, bs=bs, bptt=bptt, min_freq=10)



with open("md.pkl", "wb") as file:

    pickle.dump(md, file)
