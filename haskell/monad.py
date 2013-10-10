# Demonstration of monads, to accompany http://lukeplant.me.uk/blog.php?id=1107301643
# 2006-09-11:
#  - Fixed bug in concat
#  - Added lifting functions and examples
#  - Fixed Just.__repr__()

import operator

# Need compose to create concatMap
def compose(f, g):
    def _inner(*args, **kwargs):
        return f(g(*args, **kwargs))
    return _inner

def concat(seq):
    return reduce(operator.add, seq, [])

concatMap = compose(concat, map)

# In ruby we would just add this behaviour to the 'list' builtin,
# not dissimilar to adding a type class 'instance' declaration in Haskell.
# But in Python we have to subclass.
class ListMonad(list):
    def bind(self, func):
        # have to wrap it in ListMonad, since
        # concatMap just returns straight lists
        return ListMonad(concatMap(func, self))

    @staticmethod
    def return_(data):
        return ListMonad([data])

    def __repr__(self):
        return "ListMonad(%s)" % list.__repr__(self)

class Maybe(object):
    def set_val(self, val):
        self.val = val
        self.has_val = True
    
    def bind(self, func):
        if not self.has_val:
            return Nothing
        else:
            return func(self.val)

    @staticmethod
    def return_(val):
        return Just(val)

class Just(Maybe):
    def __init__(self, val):
        self.set_val(val)
        
    def __repr__(self):
        return "Just(%r)" % self.val

class Nothing(Maybe):
    def __init__(self):
        self.has_val = False
        
    def __repr__(self):
        return "Nothing"
Nothing = Nothing() # singleton value

def double(val):
    return val.bind(lambda x: val.return_(x*2))

print double(ListMonad([0,1,2]))
print double(Just(1.5))
print double(Nothing)

# Lifting functions:
# liftM 'lifts' a function from one that takes normal
# values to one that takes monadic values.  
def liftM(f):
    def _f(mval):
        return mval.bind(lambda a: mval.return_(f(a)))
    return _f

# Note that map can be considered as a special case of liftM for
# lists.  liftM works for any monad. (liftM is defined here as
# taking a single argument, while map takes two.  In Haskell, the
# syntax makes partial application trivial, so the distinction
# is a moot point).

# We can use liftM to define double more easily
double2 = liftM(lambda x: x*2)
print double2(ListMonad([1,2,3]))
print double2(Just(5))

# Using liftM on a built-in callable:
print liftM(str)(Just(1))
print liftM(str)(ListMonad([1,2,3]))

# Monadic functions are composable, like normal ones.
# Here we'll compose two lifted functions and map them
# over a list of monadic values.
print map(compose(liftM(str), double2), [Just(1), Just(2), Nothing])

# In ghci/hugs you would do this:
#   map (liftM show . liftM (*2)) [Just 1, Just 2, Nothing]
# or
#   map (liftM $ show . (*2)) [Just 1, Just 2, Nothing]
