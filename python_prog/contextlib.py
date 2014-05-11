#!/usr/bin/python
import time

class demo:
    def __init__(self, label):
        self.label = label

    def __enter__(self):
        self.start = time.time()

    def __exit__(self, exc_ty, exc_val, exc_tb):
        end = time.time()
        print('{}: {}'.format(self.label, end - self.start))

with demo('counting'):
    n = 10000000
    while n > 0:
        n -= 1


## for python3.4
# from contextlib import contextmanager
# @contextmanager
# def demo(label):
#     start = time.time()
#     try:
#         yield
#     finally:
#         end = time.time()
#         print('{}: {}'.format(label, end - start))
#
# with demo('counting'):
#     n = 10000000
#     while n > 0:
#         n -= 1