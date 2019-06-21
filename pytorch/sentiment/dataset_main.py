#!/usr/bin/python2.7
# -*- coding: utf-8 -*-

"""Improved dataset loader for Toxic Comment dataset from Kaggle
Tested against:
* Python 3.6
* Numpy 1.14.0
* Pandas 0.22.0
* PyTorch 0.4.0a0+f83ca63 (should be very close to 0.3.0)
* torchtext 0.2.1
* spacy 2.0.5
* joblib 0.11
"""
import re
import sys
import logging

import numpy as np
import pandas as pd
import spacy
import torch
import joblib
from joblib import Memory
from torchtext import data
from sklearn.model_selection import KFold

# import imp
# imp.reload(sys)

NLP = spacy.load('en')
MAX_CHARS = 20000

logging.basicConfig(filename="dataset.log", filemode="w", format="%(asctime)s %(name)s:%(levelname)s:%(message)s", datefmt="%d-%M-%Y %H:%M:%S", level=logging.DEBUG)
LOGGER = logging.getLogger()

handler = logging.StreamHandler(sys.stdout)
handler.setLevel(logging.DEBUG)
formatter = logging.Formatter("%(asctime)s %(name)s:%(levelname)s:%(message)s")
handler.setFormatter(formatter)
LOGGER.addHandler(handler)

MEMORY = Memory(cachedir="data/toxic/cache/", verbose=1)
VAL_RATIO=0.2

def tokenizer(comment):
    comment = re.sub(
        r"[\*\"“”\n\\…\+\-\/\=\(\)‘•:\[\]\|’\!;]", " ", str(comment))
    comment = re.sub(r"[ ]+", " ", comment)
    comment = re.sub(r"\!+", "!", comment)
    comment = re.sub(r"\,+", ",", comment)
    comment = re.sub(r"\?+", "?", comment)
    if (len(comment) > MAX_CHARS):
        comment = comment[:MAX_CHARS]
    return [x.text for x in NLP.tokenizer(comment) if x.text != " "]

def prepare_csv(seed=999):
    df_train = pd.read_csv("data/toxic/train.csv")
    df_train["comment_text"] = \
        df_train.comment_text.str.replace("\n", " ")
    idx = np.arange(df_train.shape[0])
    np.random.seed(seed)
    np.random.shuffle(idx)
    val_size = int(len(idx) * VAL_RATIO)
    df_train.iloc[idx[val_size:], :].to_csv(
        "data/toxic/cache/dataset_train.csv", index=False)
    df_train.iloc[idx[:val_size], :].to_csv(
        "data/toxic/cache/dataset_val.csv", index=False)
    df_test = pd.read_csv("data/toxic/test.csv")
    df_test["comment_text"] = \
        df_test.comment_text.str.replace("\n", " ")
    df_test.to_csv("data/toxic/cache/dataset_test.csv", index=False)

def restore_dataset(train_examples, test_examples, comment):
    train = data.Dataset()
    test = data.Dataset()
    return train, test

@MEMORY.cache
def read_files(fix_length=30, lower=False, vectors=None):
    if vectors is not None:
        # pretrain vectors only support all lower case
        lower = True
    LOGGER.info("Preparing CSV files...")
    prepare_csv()
    comment = data.Field(
        sequential=True,
        fix_length=fix_length,
        tokenize=tokenizer,
        pad_first=True,
        dtype=torch.long,
        lower=lower
    )
    LOGGER.info("Reading train csv file...")
    train = data.TabularDataset(
        path='data/toxic/cache/dataset_train.csv', format='csv', skip_header=True,
        fields=[
            ('id', None),
            ('comment_text', comment),
            ('toxic', data.Field(
                use_vocab=False, sequential=False, dtype=torch.uint8)),
            ('severe_toxic', data.Field(
                use_vocab=False, sequential=False, dtype=torch.uint8)),
            ('obscene', data.Field(
                use_vocab=False, sequential=False, dtype=torch.uint8)),
            ('threat', data.Field(
                use_vocab=False, sequential=False, dtype=torch.uint8)),
            ('insult', data.Field(
                use_vocab=False, sequential=False, dtype=torch.uint8)),
            ('identity_hate', data.Field(
                use_vocab=False, sequential=False, dtype=torch.uint8)),
        ])
    LOGGER.info("Reading test csv file...")
    test = data.TabularDataset(
        path='data/toxic/cache/dataset_test.csv', format='csv', skip_header=True,
        fields=[
            ('id', None),
            ('comment_text', comment)
        ])
    LOGGER.info("Building vocabulary...")
    comment.build_vocab(
        train, test,
        max_size=20000,
        min_freq=20,
        vectors=vectors
    )
    LOGGER.info("Done preparing the datasets")
    return train.examples, test.examples, comment


def get_dataset(fix_length=30, lower=False, vectors=None, n_folds=5, seed=999):
    train_exs, test_exs, comment = read_files(
        fix_length=fix_length, lower=lower, vectors=vectors)
    kf = KFold(n_splits=n_folds, random_state=seed)

    fields = [
        ('id', None),
        ('comment_text', comment),
        ('toxic', data.Field(
            use_vocab=False, sequential=False, dtype=torch.uint8)),
        ('severe_toxic', data.Field(
            use_vocab=False, sequential=False, dtype=torch.uint8)),
        ('obscene', data.Field(
            use_vocab=False, sequential=False, dtype=torch.uint8)),
        ('threat', data.Field(
            use_vocab=False, sequential=False, dtype=torch.uint8)),
        ('insult', data.Field(
            use_vocab=False, sequential=False, dtype=torch.uint8)),
        ('identity_hate', data.Field(
            use_vocab=False, sequential=False, dtype=torch.uint8)),
    ]

    def iter_folds():
        train_exs_arr = np.array(train_exs)
        for train_idx, val_idx in kf.split(train_exs_arr):
            yield (
                data.Dataset(train_exs_arr[train_idx], fields),
                data.Dataset(train_exs_arr[val_idx], fields),
            )

    test = data.Dataset(test_exs, fields[:2])
    return iter_folds(), test, comment


def get_iterator(dataset, batch_size, train=True, shuffle=True, repeat=False):
    dataset_iter = data.Iterator(
        dataset, batch_size=batch_size, device="cuda:0",
        train=train, shuffle=shuffle, repeat=repeat,
        sort=False
    )
    return dataset_iter

batch_size = 13
fix_length = 10

train_val_generator, test_dataset, commentField = get_dataset(fix_length=fix_length)
vocab_size = len(commentField.vocab)
print("vocab_size : %s" % vocab_size)

for fold, (train_dataset, val_dataset) in enumerate(train_val_generator):
    dataset_iter = get_iterator(
                train_dataset, batch_size, train=True,
                shuffle=True, repeat=False)
    #### one dataset/epoch
    for examples in dataset_iter:
        x = examples.comment_text # (fix_length, batch_size) Tensor
        # x = x.transpose() # (batch_size, fix_length)
        ones = torch.ones(fix_length, batch_size).cuda()

        x_bow = torch.zeros(vocab_size, batch_size).cuda().scatter_(0, x, ones)
        # print(x)
        # print(x_bow.shape)
        # for i in range(len(x_bow.data)):
        #     if x_bow.numpy()[i][0] != 0:
        #         print(i)

        ###### shape [batch, 6]
        y = torch.stack([
            examples.toxic, examples.severe_toxic,
            examples.obscene,
            examples.threat, examples.insult,
            examples.identity_hate
        ], dim=1)

        # ar = x.cpu().numpy()
        # for i in range(len(x.data)):
        #     print("%s => %s" % (ar[i][0], commentField.vocab.itos[ar[i][0]]))
        print(y.shape)
        break

    break


