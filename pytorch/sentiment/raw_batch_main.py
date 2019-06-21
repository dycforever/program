#!/usr/bin/python2.7
# -*- coding: utf-8 -*-

import torch
import numpy as np
import torch.nn.functional as F

# 0 - negative
# 1 - somewhat negative
# 2 - neutral
# 3 - somewhat positive
# 4 - positive

# from https://towardsdatascience.com/speed-up-your-algorithms-part-1-pytorch-56d8a4ae7051
# print(torch.cuda.is_available())

twoGram2IdDict = {}
id2TwoGramDict = {}

torch.manual_seed(0)

trainDataOf2Gram = []
trainDataLabel = []

def parts2Gram(words):
    lineOf2Gram = []
    for i in range(len(words) - 1):
        itemPair = (words[i], words[i+1])
        lineOf2Gram.append(itemPair)
        if itemPair in twoGram2IdDict:
            continue
        else:
            twoGramId = len(id2TwoGramDict)
            id2TwoGramDict[twoGramId] = itemPair
            twoGram2IdDict[itemPair] = twoGramId
    trainDataOf2Gram.append(lineOf2Gram)

def constructGramDict():
    with open("./data/train.tsv") as fp:
        lines = fp.readlines()
        batch = 0
        for line in lines[1:]:
            parts = line.split()
            phraseId = parts[0]
            sentenceId = parts[1]
            label = parts[-1]
            words = parts[2:-1]
            words.insert(0, "<BOS>")
            words.append("<EOS>")
            parts2Gram(words)
            trainDataLabel.append(float(label))

constructGramDict()
# from torch.utils.data import TensorDataset

vocabSize = len(twoGram2IdDict)
#print(len(id2TwoGramDict))

def toNumpyBatch(batchData):
    batchSize = len(batchData)
    #batchArray = np.arange(batchSize * vocabSize).reshape(batchSize, vocabSize)
    batchArray = np.zeros((batchSize, vocabSize), dtype=np.float32)
    batchId = 0
    for batch in batchData:
        for itemId in batch:
            batchArray[batchId][itemId] = 1
        batchId += 1
    return batchArray

def printNumpyBatch(numpyBatch):
    for row in batch:
        for i in range(len(row)):
            if row[i] != 0:
                print(" %s : %s " % (i, row[i]))


def getBatch(maxBatchSize):
    with open("./data/train.tsv") as fp:
        lines = fp.readlines()
        batchSize = 0
        batchData = []
        batchLabel = []
        for offset, instance in enumerate(trainDataOf2Gram):
            itemIdSet = set()
            for item in instance:
                itemIdSet.add(twoGram2IdDict[item])
            batchData.append(itemIdSet)
            batchSize += 1
            batchLabel.append(trainDataLabel[offset])
            if batchSize == maxBatchSize:
                yield (toNumpyBatch(batchData), np.array(batchLabel, dtype=np.float32))
                batchData = []
                batchLabel = []
                batchSize = 0
        yield (toNumpyBatch(batchData), np.array(batchLabel, dtype=np.float32))

maxBatchSize = 10

def main():
    w = torch.randn(1, vocabSize, requires_grad=True)
    b = torch.randn(1, requires_grad=True)
    torch.nn.init.xavier_uniform_(w)
    step = 0
    opt = torch.optim.SGD([w, b], lr = 1e-5)
    for epoch in range(100):
        batchGenerator = getBatch(maxBatchSize)
        while True:
            try:
                batch = next(batchGenerator)
                x = torch.from_numpy(batch[0])
                labels = batch[1]
                y = torch.from_numpy(labels).reshape(labels.shape[0], 1)
                # w is [1 * vocabSize]
                # x is [batchSize * vocabSize]
                # y is [batchSize * 1]
                # preds is [1, vocabSize]
                preds = w @ x.t() + b
                probs = F.softmax(preds, dim=1)
                #print(x)
                #print(w)
                #print(b)
                #print(preds)
                diff = preds - y.t()
                loss = torch.sum(diff * diff)/diff.numel()
                if step % 1000 == 0:
                    print("run step, loss: %s" % loss)

                loss.backward()
                opt.step()
                opt.zero_grad()

                step += 1

            except StopIteration as e:
                print("epoch[%s] done" % epoch)
                break

    #except Exception as e:
    #    print("catch Exception : %s" % str(e))
    exit(0)

main()

labels = torch.tensor([[1]])
one_hot = torch.FloatTensor(5, 1).zero_()
one_hot.scatter_(0, labels, 1.0)

w = torch.randn(1, 5, requires_grad=True)
torch.nn.init.xavier_uniform_(w)
print(one_hot)
print(w)

print(type(one_hot))
print(type(w))
y = one_hot @ w

print(y)
#print(w.grad)
#y.backward()
#print(w.grad)


