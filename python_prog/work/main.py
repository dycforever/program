import sys;
import getopt
from log_parser import Executor
from log_parser import DefaultCollector

class InfoCollector(DefaultCollector):
    def init(self, output):
        self.count = 0

    def put(self, record):
        print "call put"
        if (record.urlObj.fr == "iphone"):
            self.count += 1

    def dump(self):
        print "count: ", self.count



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

if e.run() == False :
    print "run failed"



