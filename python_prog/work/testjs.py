
import json

fp=open("condition.json", "r")
cont = fp.read()
print json.dumps(cont)