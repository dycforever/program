#!/usr/bin/python
class Celsius(object):
    def __init__(self, value=0.0):
        self.value = float(value)
    def __get__(self, instance, owner):
        print("call get()")
        return self.value
    def __set__(self, instance, value):
        self.value = float(value)

class Temperature(object):
    celsius = Celsius()

temp=Temperature()
#calls Celsius.__get__
temp.celsius


import weakref

class lazyattribute(object):
    def __init__(self, f):
        self.data = weakref.WeakKeyDictionary()
        self.f = f
    def __get__(self, obj, cls):
        if obj not in self.data:
            self.data[obj] = self.f(obj)
        return self.data[obj]

class Foo(object):
    @lazyattribute
    def bar(self):
        print "Being lazy"
        return 42

f = Foo()

print f.bar


class Movie(object):
    def __init__(self, title, rating, runtime, budget, gross):
        self._budget = None
        self.title = title
        self.rating = rating
        self.runtime = runtime
        self.gross = gross
        self.budget = budget

    @property
    def budget(self):
        return self._budget

    @budget.setter
    def budget(self, value):
        if value < 0:
            raise ValueError("Negative value not allowed: %s" % value)
        self._budget = value

    def profit(self):
        return self.gross - self.budget

m = Movie('Casablanca', 97, 102, 964000, 1300000)
# calls m.budget(), returns result
print 'Movie.budget: ', m.budget
try:
    m.budget = -100  # calls budget.setter(-100), and raises ValueError
except ValueError:
    print "Woops. Not allowed"


class NonNegative(object):
    """A descriptor that forbids negative values"""
    def __init__(self, default):
        print("calling NonNegative.__init__()")
        self.default = default
        self.data = weakref.WeakKeyDictionary()

    def __get__(self, instance, owner):
        # we get here when someone calls x.d, and d is a NonNegative instance
        # instance = x
        # owner = type(x)
        print("calling NonNegative.__get__()")
        return self.data.get(instance, self.default)

    def __set__(self, instance, value):
        # we get here when someone calls x.d = val, and d is a NonNegative instance
        # instance = x
        # value = val
        print("calling NonNegative.__set__(), value: ", value)
        if value < 0:
            raise ValueError("Negative value not allowed: %s" % value)
        self.data[instance] = value

class Movie2(object):
    # must put descriptors at the class-level
    # if move statements below into __init__, it won't work
    rating = NonNegative(0)
    runtime = NonNegative(0)
    budget = NonNegative(0)
    gross = NonNegative(0)

    def __init__(self, title, rating, runtime, budget, gross):
        self.title = NonNegative(0)
        self.rating = rating
        self.runtime = runtime
        self.budget = budget
        self.gross = gross

    def profit(self):
        return self.gross - self.budget

m = Movie2('Casablanca', 97, 102, 964000, 1300000)
print m.budget  # calls Movie.budget.__get__(m, Movie)
print m.title   # return a NonNegative object
m.rating = 100  # calls Movie.budget.__set__(m, 100)
try:
    m.rating = -1   # calls Movie.budget.__set__(m, -100)
except ValueError:
    print "Woops, not allow negative value"


class Descriptor(object):
    def __init__(self, label):
        self.label = label

    def __get__(self, instance, owner):
        print '__get__', instance, owner
        return instance.__dict__.get(self.label)

    def __set__(self, instance, value):
        print '__set__'
        instance.__dict__[self.label] = value

class Foo(list):
    x = Descriptor('x')
    y = Descriptor('y')

f = Foo()
f.x = 5
print "f: ", f
print "f.x: ", f.x



class CallbackProperty(object):
    """A property that will alert observers when upon updates"""
    def __init__(self, default=None):
        self.data = weakref.WeakKeyDictionary()
        self.default = default
        self.callbacks = weakref.WeakKeyDictionary()

    def __get__(self, instance, owner):
        if instance is None:
            return self
        return self.data.get(instance, self.default)

    def __set__(self, instance, value):
        for callback in self.callbacks.get(instance, []):
                        # alert callback function of new value
            callback(value)
        self.data[instance] = value

    def add_callback(self, instance, callback):
        """Add a new function to call everytime the descriptor within instance updates"""
        if instance not in self.callbacks:
            self.callbacks[instance] = []
        self.callbacks[instance].append(callback)

class BankAccount(object):
    balance = CallbackProperty(0)

def low_balance_warning(value):
    if value < 100:
        print "You are now poor"

ba = BankAccount()
BankAccount.balance.add_callback(ba, low_balance_warning)

ba.balance = 5000
print "Balance is %s" % ba.balance
ba.balance = 99
print "Balance is %s" % ba.balance

