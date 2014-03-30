#!/usr/bin/python3
li=[1,2,3,4,5]

print(li[1:3])
print(li[-3:-1])

print(li[3:1])


dict={"name":"dyc", "gender":"man", "age":"27"}

vs=[v for k,v in dict.items()]
print(vs)
print("xx".join(vs))
print("xx".join(vs).split("xx"))


dyc="dyc"
str="name=%s age=%d" % (dyc, 12)

print("print str: %s" % str, end='')

print()
print()

if __name__ == "__main__":
    import getopt
    import sys
    print(sys.argv)
    opts,args = getopt.getopt(sys.argv,"ch",["configure", "help"])
    print(opts)
    print(args)

