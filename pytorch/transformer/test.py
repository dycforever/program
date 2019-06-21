
import numpy as np

import torch
from torch.autograd import Variable

V = 11
data = torch.from_numpy(np.random.randint(1, V, size=(3, 2)))
data[:, 0] = 1
src = Variable(data, requires_grad=False)
newSrc = src.view(3,1,2)
print(src)
mask = ((src != 0).unsqueeze(-2))

print(mask)
newSrc = newSrc.masked_fill(mask == 0, -1e9)
print(newSrc)

