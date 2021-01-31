def outer():
     x = 1
     def inner():
          print(x)
     return inner
foo = outer()
foo()
print(foo.__closure__)

print("==============")

class entryExit(object):
    def __init__(self, f):
        self.f = f
        print("calling entryExit.init()")

    def __call__(self):
        print("Entering", self.f.__name__)
        self.f()
        print("Exited", self.f.__name__)

@entryExit
def func1():
    print("inside func1()")

@entryExit
def func2():
    print("inside func2()")

func1()
func2()
