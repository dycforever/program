#!/usr/bin/python2.7
# -*- coding: utf-8 -*-

import torch
torch.manual_seed(0)
x = torch.rand(2, 5)
print(x)
# tensor([[0.4963, 0.7682, 0.0885, 0.1320, 0.3074],
#         [0.6341, 0.4901, 0.8964, 0.4556, 0.6323]])

# def scatter_(dim, index, src) → Tensor
# 循环 i,j 把 src 中的值散落到 self 中，当 dim = 0 时:
# self[index[i][j]][j] = src[i][j]
# 所以 index 和 src 形状相同，self 和 src 的列数要相同，self 中每一列要替换多少个，src 也就要有多少列
y=torch.zeros(3, 5).scatter_(0, torch.LongTensor([[0, 1, 2, 0, 0], [2, 0, 0, 1, 2]]), x)
# tensor([[0.4963, 0.4901, 0.8964, 0.1320, 0.3074],
#         [0.0000, 0.7682, 0.0000, 0.4556, 0.0000],
#         [0.6341, 0.0000, 0.0885, 0.0000, 0.6323]])
print(y)

# z = torch.zeros(2, 4).scatter_(1, torch.LongTensor([[2], [3]]), 1.23)

