#!/usr/bin/python3

class MyDict() :
    def __init__(self):
        print("call __init__()");
    def __setitem__(self, k,v):
        print("call __setitem__(), k:%s  v:%s" % (str(k), str(v)));
    def __getitem__(self, k):
        print("call __getitem__(), k:%s " % str(k));
    def __str__(self):
        return "Mydict.__str__() "
    def __repr__(self):
        return "Mydict.__repr__() ";
    def __cmp__(self, dict):
        print("call __cmp__(), dict: %s", str(dict));
        return true
    def __len__(self):
        print("call __len__()");
        return 0
    def __delitem__(self, k):
        print("call __delitem__(), k: %s" % str(k));


def info(object, spacing=10, collapse=1):
    """Print methods and doc strings.

    Takes module, class, list, dictionary, or string."""
    methodList = [e for e in dir(object) if callable(getattr(object, e))]
    print(methodList)
#    processFunc = collapse and (lambda s: " ".join(s.split())) or (lambda s: s)
#    print("\n".join(["%s %s" % (method.ljust(spacing), processFunc(str(getattr(object, method).__doc__)))
#        for method in methodList]))


def foo(arg):
    x=gx=1
    print(locals())
    locals()["x"]=2
    globals()["gx"]=2
    print("x=%d gx=%d" % (x,gx))

li=[]
info(li)

dict=MyDict();
dict[1];
dict[2]=2;

dict2=MyDict();
dict==dict2
len(dict)
print(str(dict))
print(repr(dict))
del dict[1]

gx=1
print("=========")
foo(3)
