#!/usr/bin/python
import time
from functools import wraps

print("example1: decorator function")
print("###########################")
def timethis(func):
    '''
    Decorator that reports the execution time.
    '''
    @wraps(func)
    def wrapper(*args, **kwargs):
        start = time.time()
        result = func(*args, **kwargs)
        end = time.time()
        print(func.__name__, end-start)
        return result
    return wrapper

@timethis
def countdown(n):
    while n > 0:
        n -= 1

countdown(100000)

print("\nexample2: decorator class")
print("###########################")
class decorator(object):
    def __init__(self, f):
        print("inside decorator.__init__()")
        f() # Prove that function definition has completed

    def __call__(self):
        print("inside decorator.__call__(), without calling function()")

# equals to function=decorator(function), so __init__() be called
@decorator
def function():
    print("inside function()")

print("Finished decorating function()")

# just call decorator's__call__()
function()

print("\nexample3: decorator function with parameters")
print("###########################")

def decorate_A(function):
    def wrap_function(*args, **kwargs):
        kwargs['str'] = 'Hello!'
        return function(*args, **kwargs)
    return wrap_function

@decorate_A
def print_message_A(*args, **kwargs):
    print(kwargs['str'])

print_message_A()


def decorate_B(function):
    def wrap_function(*args, **kwargs):
        str = 'Hello!'
        return function(str, *args, **kwargs)
    return wrap_function

@decorate_B
def print_message_B(str, *args, **kwargs):
    print(str)

print_message_B()


def decorate_C(function):
    def wrap_function(*args, **kwargs):
        str = 'Hello!'
        #args.insert(1, str)
        args = args +(str,)
        return function(*args, **kwargs)
    return wrap_function

class Printer:
    @decorate_C
    def print_message(self, str, *args, **kwargs):
        print(str)

p = Printer()
p.print_message()