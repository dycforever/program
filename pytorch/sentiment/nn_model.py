#!/usr/bin/python2.7
# -*- coding: utf-8 -*-

import torch
import numpy as np
import torch.nn.functional as F
import torch.autograd as autograd
import torch.nn as nn
import torch.optim as optim

# 数据我们使用的是莎士比亚的14行诗
test_sentence = """When forty winters shall besiege thy brow,
And dig deep trenches in thy beauty's field,
Thy youth's proud livery so gazed on now,
Will be a totter'd weed of small worth held:
Then being asked, where all thy beauty lies,
Where all the treasure of thy lusty days;
To say, within thine own deep sunken eyes,
Were an all-eating shame, and thriftless praise.
How much more praise deserv'd thy beauty's use,
If thou couldst answer 'This fair child of mine
Shall sum my count, and make my old excuse,'
Proving his beauty by succession thine!
This were to be new made when thou art old,
And see thy blood warm when thou feel'st it cold.""".split()

# 将单词序列转化为数据元组列表，
# 其中的每个元组格式为([ word_i-2, word_i-1 ], target word)
trigrams = [ ([test_sentence[i], test_sentence[i+1]], test_sentence[i+2]) for i in range(len(test_sentence) - 2) ]
# 给14行诗建立单词表
# set 即去除重复的词
vocab = set(test_sentence)
# 建立词典，它比单词表多了每个词的索引
word_to_ix = { word: i for i, word in enumerate(vocab) }

print(len(vocab))

# 上下文大小
# 即 前两个词
CONTEXT_SIZE = 2
# 嵌入维度
EMBEDDING_DIM = 10

class NGramLanguageModeler(nn.Module):

    # 初始化时需要指定：单词表大小、想要嵌入的维度大小、上下文的长度
    def __init__(self, vocab_size, embedding_dim, context_size):
        # 继承自nn.Module，例行执行父类super 初始化方法
        super(NGramLanguageModeler, self).__init__()
        # 建立词嵌入模块
        self.embeddings = nn.Embedding(vocab_size, embedding_dim)
        # 线性层1
        self.linear1 = nn.Linear(context_size * embedding_dim, 128)
        # 线性层2，隐藏层 hidden_size 为128
        self.linear2 = nn.Linear(128, vocab_size)

    # 重写的网络正向传播方法
    # 只要正确定义了正向传播
    # PyTorch 可以自动进行反向传播
    def forward(self, inputs):
        # 将输入进行“嵌入”，并转化为“行向量”
        embeds = self.embeddings(inputs).view((1, -1))
        # 嵌入后的数据通过线性层1后，进行非线性函数 ReLU 的运算
        out = F.relu(self.linear1(embeds))
        # 通过线性层2后
        out = self.linear2(out)
        # 通过 log_softmax 方法将结果映射为概率的log
        # log 概率是用于下面计算负对数似然损失函数时方便使用的
        log_probs = F.log_softmax(out)
        return log_probs


losses = []
# 损失函数为 负对数似然损失函数(Negative Log Likelihood)
loss_function = nn.NLLLoss()
# 实例化我们的模型，传入：
# 单词表的大小、嵌入维度、上下文长度
model = NGramLanguageModeler(len(vocab), EMBEDDING_DIM, CONTEXT_SIZE)
# 优化函数使用随机梯度下降算法，学习率设置为0.001
optimizer = optim.SGD(model.parameters(), lr=0.001)

for epoch in range(1000):
    total_loss = 0
    # 循环context上下文，比如：['When', 'forty']
    # target，比如：winters
    for context, target in trigrams:

        # 步骤1：准备数据
        # 将context如“['When', 'forty']”
        # 转化为索引，如[68, 15]
        # 再建立为 PyTorch Variable 变量，以计算梯度
        context_idxs = list(map(lambda w: word_to_ix[w], context))
        context_var = autograd.Variable( torch.LongTensor(context_idxs) )

        # 步骤2：清空梯度值，防止上次的梯度累计
        model.zero_grad()

        # 步骤3：运行网络的正向传播，获得 log 概率
        log_probs = model(context_var)

        # 步骤4：计算损失函数
        # 传入 target Variable
        loss = loss_function(log_probs, autograd.Variable(torch.LongTensor([word_to_ix[target]])))

        # 步骤5：进行反向传播并更新梯度
        loss.backward()
        optimizer.step()

        #total_loss += loss.data[0]
        total_loss += loss.item()
    losses.append(total_loss)

print('Finished')
print(losses)
