import sys;
import getopt
import time

from log_parser import Executor
from log_parser import DefaultCollector

class InfoCollector(DefaultCollector):
    def init(self, output):
        self.outFile = open("normal.data", "w")
        self.countMap = {}

    def put(self, record):
        self.outFile.write(record.originLine)
        if (record.urlObj.fr not in self.countMap.keys()):
            self.countMap[record.urlObj.fr] = 1
        else:
            self.countMap[record.urlObj.fr] += 1

    def dump(self):
        for k, v in self.countMap.items():
            print "%s : %d" %(k, v)
        self.outFile.close()


if len(sys.argv) < 2:
    print "Usage:", sys.argv[0], "-i inputfile -c condition.json -o output_file"
    sys.exit(-1)

inputFile = ""
outputFile = ""
conditionFile = ""
try:
    options,args = getopt.getopt(sys.argv[1:], "hi:c:o:", ["help"])
    for name,value in options:
        if name in ("-h","--help"):
            print "Usage:", sys.argv[0], "-i inputfile -c condition.json -o output_file"
            sys.exit(1)
        if name in ("-i"):
            inputFile = value
        if name in ("-o"):
            outputFile = value
        if name in ("-c"):
            conditionFile = value
except getopt.GetoptError, e:
    print "error:", e, str(getopt.GetoptError)
    sys.exit(1)

if inputFile == "":
    print "inputFile is null "
    sys.exit(-1)

e = Executor()
e.mCollector = InfoCollector()
if e.init(inputFile, outputFile, conditionFile) == False:
    print "init executor failed"

begin = time.time()
if e.run() == False :
    print "run failed"
e.info()

end = time.time()
print end - begin


