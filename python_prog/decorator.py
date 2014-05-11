#!/usr/bin/python
import time

print("example1: decorator function")
print("###########################")
def timethis(func):
    '''
    Decorator that reports the execution time.
    '''
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


#print("\nexample4: @wrapper for name")
from functools import wraps
#def hello(fn):
#    @wraps(fn)
#    def wrapper():
#        print("hello, %s" % fn.__name__)
#        fn()
#        print("goodby, %s" % fn.__name__)
#    return wrapper
#
#@hello
#def foo():
#    '''foo help doc'''
#    print("I am foo")
#    pass
#
#foo()
## because of @wraps(fn) above
#print(foo.__name__)#outpu foo
#print(foo.__doc__ )#output foo help doc
#
#print("\nexample5: for cache")
#def memo(fn):
#    cache = {}
#    miss = -1
#
#    @wraps(fn)
#    def wrapper(*args):
#        result = cache.get(args, miss)
#        if result is miss:
#            result = fn(*args)
#            cache[args] = result
#        return result
#    return wrapper
#
#@memo
#def fib(n):
#    if n < 2:
#        return n
#    return fib(n - 1) + fib(n - 2)
#
#for i in range(0,10):
#    print(i, end=" ")
#print("")

import inspect
print("\nexample6: advanced example")
def advance_logger(loglevel):

    def get_line_number():
        return inspect.currentframe().f_back.f_back.f_lineno

    def _basic_log(fn, result, *args, **kwargs):
        print("function   = " + fn.__name__,)
        print("    arguments = {0} {1}".format(args, kwargs))
        print("    return    = {0}".format(result))

    def info_log_decorator(fn):
        @wraps(fn)
        def wrapper(*args, **kwargs):
            result = fn(*args, **kwargs)
            _basic_log(fn, result, args, kwargs)
        return wrapper

    def debug_log_decorator(fn):
        @wraps(fn)
        def wrapper(*args, **kwargs):
            ts = time.time()
            result = fn(*args, **kwargs)
            te = time.time()
            _basic_log(fn, result, args, kwargs)
            print("    time      = %.6f sec" % (te-ts))
            print("    called_from_line : " + str(get_line_number()))
        return wrapper

    if loglevel is "debug":
        return debug_log_decorator
    else:
        return info_log_decorator

@advance_logger(loglevel="debug")
def add_sum(x, y):
    return x+y

add_sum(1, 2)
add_sum(3, 4)