#!/usr/bin/python2.7
# -*- coding: utf-8 -*-

# from :
#     https://github.com/bentrevett/pytorch-sentiment-analysis

import sys
import os
import logging
import time
from joblib import Memory

import numpy as np

import torch
import torch.nn as nn
import torch.nn.functional as F
import torch.optim as optim

from torchtext import data

MEMORY = Memory(cachedir="data/aclImdb/cache/", verbose=1)

# run as:
# LD_LIBRARY_PATH=/usr/lib64/nvidia:/home/dingyc/tmp/ext/cuda-toolkit/targets/x86_64-linux/lib/ python main.py

# python -m spacy download en
TEXT = data.Field(tokenize = 'spacy')
LABEL = data.LabelField(dtype = torch.float)

N_EPOCHS = 100
MAX_VOCAB_SIZE = 25000
BATCH_SIZE = 64

logging.basicConfig(filename="main.log", filemode="w", format="%(asctime)s %(name)s:%(levelname)s:%(message)s", datefmt="%d-%M-%Y %H:%M:%S", level=logging.DEBUG)
LOGGER = logging.getLogger()

handler = logging.StreamHandler(sys.stdout)
handler.setLevel(logging.DEBUG)
formatter = logging.Formatter("%(asctime)s %(name)s:%(levelname)s:%(message)s")
handler.setFormatter(formatter)
LOGGER.addHandler(handler)


MEMORY = Memory(cachedir="data/aclImdb/cache/", verbose=1)

@MEMORY.cache
def createData(dataroot="data/aclImdb_small"):
    from torchtext import datasets
    import random
    LOGGER.info("begin to split train/test")
    train_data, test_data = datasets.IMDB.splits(TEXT, LABEL, root=dataroot)
    LOGGER.info("train/test split done")
    train_data, valid_data = train_data.split(random_state = random.seed(SEED))
    LOGGER.info("train/valid split done")
    return train_data.examples, test_data.examples, valid_data.examples

LOGGER.info("cuda: %s" % torch.cuda.is_available())

SEED = 1234

torch.manual_seed(SEED)
torch.backends.cudnn.deterministic = True

LOGGER.info("begin to createData")
train_examples, test_examples, valid_examples = createData()
LOGGER.info("createData done")

# print(TEXT.vocab.freqs.most_common(20))
# print(LABEL.vocab.stoi)


class RNN(nn.Module):
    def __init__(self, input_dim, embedding_dim, hidden_dim, output_dim):
        super().__init__()
        self.embedding = nn.Embedding(input_dim, embedding_dim)
        self.rnn = nn.RNN(embedding_dim, hidden_dim)
        self.fc = nn.Linear(hidden_dim, output_dim)

    def forward(self, text):
        #text = [sent len, batch size]
        embedded = self.embedding(text)
        #embedded = [sent len, batch size, emb dim]
        output, hidden = self.rnn(embedded)

        #output = [sent len, batch size, hid dim]
        #hidden = [1, batch size, hid dim]
        assert torch.equal(output[-1,:,:], hidden.squeeze(0))
        return self.fc(hidden.squeeze(0))


class BOW(nn.Module):
    def __init__(self, input_dim, embedding_dim, output_dim):
        super().__init__()
        self.embedding = nn.Embedding(input_dim, embedding_dim)
        self.fc = nn.Linear(embedding_dim, output_dim)

    def forward(self, text):
        #text = [sent len, batch size]
        #embedded = [sent len, batch size, emb dim]
        embedded = self.embedding(text)
        #embedded = [batch size, emb dim]
        embedded = embedded.sum(0)
        #output = [batch size, output_dim]
        output = self.fc(embedded)
        return output


def count_parameters(model):
    return sum(p.numel() for p in model.parameters() if p.requires_grad)

def binary_accuracy(preds, y):
    """
    Returns accuracy per batch, i.e. if you get 8/10 right, this returns 0.8, NOT 8
    """
    #round predictions to the closest integer
    rounded_preds = torch.round(torch.sigmoid(preds))
    correct = (rounded_preds == y).float() #convert into float for division
    acc = correct.sum() / len(correct)
    return acc

def train(model, iterator, optimizer, criterion):
    epoch_loss = 0
    epoch_acc = 0
    model.train()

    for batch in iterator:
        optimizer.zero_grad()
        predictions = model(batch.text[:100]).squeeze(1)
        loss = criterion(predictions, batch.label)
        acc = binary_accuracy(predictions, batch.label)
        loss.backward()
        optimizer.step()
        epoch_loss += loss.item()
        epoch_acc += acc.item()

    return epoch_loss / len(iterator), epoch_acc / len(iterator)

def evaluate(model, iterator, criterion):
    epoch_loss = 0
    epoch_acc = 0

    model.eval()
    with torch.no_grad():
        for batch in iterator:
            predictions = model(batch.text).squeeze(1)
            loss = criterion(predictions, batch.label)
            acc = binary_accuracy(predictions, batch.label)
            epoch_loss += loss.item()
            epoch_acc += acc.item()

    return epoch_loss / len(iterator), epoch_acc / len(iterator)


def epoch_time(start_time, end_time):
    elapsed_time = end_time - start_time
    elapsed_mins = int(elapsed_time / 60)
    elapsed_secs = int(elapsed_time - (elapsed_mins * 60))
    return elapsed_mins, elapsed_secs

def run(model, train_iterator, optimizer, criterion):
    best_valid_loss = float('inf')
    for epoch in range(N_EPOCHS):
        start_time = time.time()
        train_loss, train_acc = train(model, train_iterator, optimizer, criterion)
        valid_loss, valid_acc = evaluate(model, valid_iterator, criterion)
        end_time = time.time()

        epoch_mins, epoch_secs = epoch_time(start_time, end_time)

        if valid_loss < best_valid_loss:
            best_valid_loss = valid_loss
            torch.save(model.state_dict(), 'tut1-model.pt')

        LOGGER.info(f'Epoch: {epoch+1:02} | Epoch Time: {epoch_mins}m {epoch_secs}s')
        LOGGER.info(f'\tTrain Loss: {train_loss:.3f} | Train Acc: {train_acc*100:.2f}%')
        LOGGER.info(f'\t Val. Loss: {valid_loss:.3f} |  Val. Acc: {valid_acc*100:.2f}%')


device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')

fields = [
        ('text', TEXT),
        ('label', LABEL),
        ]
train_data = data.Dataset(train_examples, fields)
test_data = data.Dataset(test_examples, fields)
valid_data = data.Dataset(valid_examples, fields)

LOGGER.info(f'Number of training examples: {len(train_data)}')
LOGGER.info(f'Number of validation examples: {len(valid_data)}')
LOGGER.info(f'Number of testing examples: {len(test_data)}')


TEXT.build_vocab(train_data,
        vectors = "glove.6B.100d",
        max_size = MAX_VOCAB_SIZE)
LABEL.build_vocab(train_data)

LOGGER.info(f"Unique tokens in TEXT vocabulary: {len(TEXT.vocab)}")
LOGGER.info(f"Unique tokens in LABEL vocabulary: {len(LABEL.vocab)}")

train_iterator, valid_iterator, test_iterator = data.BucketIterator.splits(
    (train_data, valid_data, test_data),
    batch_size = BATCH_SIZE,
    sort=False,
    device = device)

INPUT_DIM = len(TEXT.vocab)
EMBEDDING_DIM = 100
HIDDEN_DIM = 256
OUTPUT_DIM = 1

rnn_model = RNN(INPUT_DIM, EMBEDDING_DIM, HIDDEN_DIM, OUTPUT_DIM)
rnn_model = rnn_model.to(device)

bow_model = BOW(INPUT_DIM, EMBEDDING_DIM, OUTPUT_DIM)
bow_model = bow_model.to(device)

model = bow_model
model = rnn_model
LOGGER.info(f'The model has {count_parameters(model):,} trainable parameters')

optimizer = optim.SGD(model.parameters(), lr=1e-3)
optimizer = optim.Adam(model.parameters())
#if torch.cuda.device_count() > 1:
#  print("Let's use", torch.cuda.device_count(), "GPUs!")
#  model = nn.DataParallel(model)

criterion = nn.BCEWithLogitsLoss()
criterion = criterion.to(device)

run(model, train_iterator, optimizer, criterion)

# model.load_state_dict(torch.load('tut1-model.pt'))
# test_loss, test_acc = evaluate(model, test_iterator, criterion)
# LOGGER.info(f'Test Loss: {test_loss:.3f} | Test Acc: {test_acc*100:.2f}%')

