#!/usr/bin/python

# just use "*" to collect all remaining arguments into a tuple
def foo(*args):
    numargs = len(args)
    print "Number of arguments: {0}".format(numargs)
    for i, x in enumerate(args):
        print "Argument {0} is: {1}".format(i,x)
foo("hello", "world", "again")

import glob
# get all py files
files = glob.glob('*.py')
print files

import itertools as it, glob, os
def multiple_file_types(*patterns):
    return it.chain.from_iterable(glob.glob(pattern) for pattern in patterns)
for filename in multiple_file_types("*t", "*.py"):
    realpath = os.path.realpath(filename)
    print realpath


import logging, inspect
logging.basicConfig(level=logging.INFO,
        format='%(asctime)s %(levelname)-8s %(filename)s:%(lineno)-4d: %(message)s',
            datefmt='%m-%d %H:%M',
                )
logging.debug('A debug message')
logging.info('Some information')
logging.warning('A shot across the bow')

def test():
    frame,filename,line_number,function_name,lines,index=\
                        inspect.getouterframes(inspect.currentframe())[1]
    print(frame,filename,line_number,function_name,lines,index)

test()


import pickle
variable = ['hello', 42, [1,'two'],'apple']

# serialize content
file = open('serial.txt','w')
serialized_obj = pickle.dumps(variable)
file.write(serialized_obj)
file.close()

# unserialize to produce original content
target = open('serial.txt','r')
myObj = pickle.load(target)

print "serialized file content:", serialized_obj
print "obj in memory:", myObj


import json
## serialize with json
variable = ['hello', 42, [1,'two'],'apple']
print "Original {0} - {1}".format(variable,type(variable))

# encoding
encode = json.dumps(variable)
print "Encoded {0} - {1}".format(encode,type(encode))

#deccoding
decoded = json.loads(encode)
print "Decoded {0} - {1}".format(decoded,type(decoded))


import zlib

string =  """   Lorem ipsum dolor sit amet, consectetur
                adipiscing elit. Nunc ut elit id mi ultricies
                adipiscing. Nulla facilisi. Praesent pulvinar,
                sapien vel feugiat vestibulum, nulla dui pretium orci,
                non ultricies elit lacus quis ante. Lorem ipsum dolor
                sit amet, consectetur adipiscing elit. Aliquam
                pretium ullamcorper urna quis iaculis. Etiam ac massa
                sed turpis tempor luctus. Curabitur sed nibh eu elit
                mollis congue. Praesent ipsum diam, consectetur vitae
                ornare a, aliquam a nunc. In id magna pellentesque
                tellus posuere adipiscing. Sed non mi metus, at lacinia
                augue. Sed magna nisi, ornare in mollis in, mollis
                sed nunc. Etiam at justo in leo congue mollis.
                Nullam in neque eget metus hendrerit scelerisque
                eu non enim. Ut malesuada lacus eu nulla bibendum
                id euismod urna sodales. """

print "Original Size: {0}".format(len(string))

compressed = zlib.compress(string)
print "Compressed Size: {0}".format(len(compressed))

decompressed = zlib.decompress(compressed)
print "Decompressed Size: {0}".format(len(decompressed))


import atexit
import time
import math

def microtime(get_as_float = False) :
    if get_as_float:
        return time.time()
    else:
        return '%f %d' % math.modf(time.time())
start_time = microtime(False)

def shutdown():
    global start_time
    print "Execution took: {0} seconds".format(start_time)

atexit.register(shutdown)