#!/usr/bin/python
def func1():
    print("func1")
    func2()

def func2():
    print("func2")

def main():
    func1()

main()
