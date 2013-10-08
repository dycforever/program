#!/usr/bin/python
def myabs(num):
	print("deal num")
	print(num)
	return num if num >= 0 else -num

def mymap(func, *seqs):
	res = []
	for args in zip(*seqs):
		print("deal args:")
		print(args)
		res.append(func(*args))
	return res

# 
#	can also be:
#
#def mymap(func, *seqs):
#	res = []
#	for args in list(*seqs):
#		print("deal args:")
#		print(args)
#		res.append(func(args))
#	return res

print(mymap(myabs,[-2,-1,0,1,2]))

