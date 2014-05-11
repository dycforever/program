#!/usr/bin/python
import os

#generator use () instead of [], don't need to load all list items in to memory
num = [1, 4, -5, 10, -7, 2, 3, -1]
def filtered_and_squared(optional_parameter):
    return [x ** 2 for x in num if x > optional_parameter]
def filtered_and_squared_generator(optional_parameter):
    return (x ** 2 for x in num if x > optional_parameter)

for item in filtered_and_squared(0):
    print(item)
print("")
for item in filtered_and_squared_generator(0):
    print(item)

even_set = { x for x in num if x % 2 == 0 }
print even_set


# generator is implemented by yield, such as:

# os.walk(top, topdown=True, onerror=None, followlinks=False)
# when topdown is False, in bottom-up mode the directories in dirnames are generated before dirpath itself is generated
def tree(top):
    for dirpath, dirnames, filenames in os.walk(top, topdown=False):
        for filename in filenames:
            yield os.path.join(dirpath, filename)

for name in tree("/home/dyc/github/program/python_prog"):
    print name