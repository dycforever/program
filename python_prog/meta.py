#!/usr/bin/python

def echo(obj):
    print(obj)

class ObjectCreator():
    pass

myObject = ObjectCreator()
echo(myObject)
echo(myObject)

def classCreator():
    class Sub(object):
        pass
    return Sub

MyClass = classCreator()
echo(MyClass)

def pself(self):
    echo(self.string)

MyClass2 = type("MyClass2", (), {"pself": pself, "string":"my class2"})
echo(MyClass2)
obj = MyClass2
obj.pself()

#print ("%d  %s   %f" % 12, "dyc", 0.5)
