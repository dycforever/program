#!/usr/bin/python
# -*- coding: utf-8 -*-

def echo(obj):
    print(obj)

class ObjectCreator():
    pass

myObject = ObjectCreator()
echo(myObject)

def classCreator():
    class Sub(object):
        pass
    return Sub

MyClass = classCreator()
echo(MyClass)

def pself(self):
    echo(self.string)

MyClass2 = type("MyClass2", (), {"pself": pself, "string":"I am an instance of class2"})
echo(MyClass2)
obj = MyClass2()
obj.pself()

print obj.__class__


print "########################"

def upperAttrFunc(future_class_name, future_class_parents, future_class_attr):
    print "calling upperAttrFunc()"
    print "future_class_name: ", future_class_name
    print "future_class_parents: ", future_class_parents
    print "future_class_attr: ", future_class_attr

    attrs = ((name, value) for name, value in future_class_attr.items() if not name.startswith('__'))
    uppercase_attr = dict((name.upper(), value) for name, value in attrs)
    return type(future_class_name, future_class_parents, uppercase_attr)


class MyMetaClass:
    __metaclass__ = upperAttrFunc
    member = "member of MyMetaClass"

print hasattr(MyMetaClass, 'member')
print hasattr(MyMetaClass, 'MEMBER')

f = MyMetaClass()
print f.MEMBER

print "########################"

class UpperAttrMetaClass(type):
    # __metaclass__ = upperAttrFunc

    # __new__ 是在__init__之前被调用的static方法，用来创建对象并返回
    def __new__(cls, future_class_name, future_class_parents, future_class_attr):
        print "calling UpperAttrMetaClass.__new__()"
        print "cls: ", cls
        print "future_class_name: ", future_class_name
        print "future_class_parents: ", future_class_parents
        print "future_class_attr: ", future_class_attr
        attrs = ((name, value) for name, value in future_class_attr.items() if not name.startswith('__'))
        uppercase_attr = dict((name.upper(), value) for name, value in attrs)
        print "cls == UpperAttrMetaClass is ", cls == UpperAttrMetaClass
        return super(cls, UpperAttrMetaClass).__new__(cls, future_class_name, future_class_parents, uppercase_attr)

print "will creating MyMetaClass2"

class MyMetaClass2:
    __metaclass__ = UpperAttrMetaClass
    member = "member of MyMetaClass2"

print "after creating MyMetaClass2"
print hasattr(MyMetaClass2, '__metaclass__')
# print MyMetaClass2.__metaclass__
print hasattr(MyMetaClass2, '__METACLASS__')

print hasattr(MyMetaClass2, 'member')
print hasattr(MyMetaClass2, 'MEMBER')

f = MyMetaClass2()
#print f.MEMBER

print hasattr(f, 'member')
f.member = 0
print hasattr(f, 'member')


#print ("%d  %s   %f" % 12, "dyc", 0.5)
