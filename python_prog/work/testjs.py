
import json

fp=open("condition.json", "r")
cont = fp.read()
#print json.dumps(cont)
mmap = json.loads(cont)
for key in mmap:
    for item in mmap[key]:
        item = item.decode("utf-8").encode("ascii")

print mmap
print mmap["fr"][0] == "iphone"
print mmap["fr"][0] == u"iphone"