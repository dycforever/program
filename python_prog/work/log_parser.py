#!/usr/local/bin/python2.7

import sys;
import getopt
import time
import math

class URLObject:
    def __init__(self):
        self.location = ''
        self.querys = []
        self.fr = ''
        self.ve = ''
        self.q = ''
        self.reqFrom = ''
        self.eid= ''
    def toString(self):
        print "url location", self.location, "ve:", self.ve, "fr:", self.fr


class URLParser:
    def parseURL(self, urlStr):
        urlStr = urlStr.strip()
        url = URLObject()
        locationEnd = urlStr.find('?') + 1
        url.location = urlStr[0:locationEnd]
        url.querys = urlStr[locationEnd:].split('&')
        url.ve = ""
        url.fr = ""
        url.reqFrom = ""
        for q in url.querys:
            if q[0:3] == "fr=":
                url.fr = q[3:]
            if q[0:3] == "ve=":
                url.ve = q[3:]
            if q[0:2] == "q=":
                url.q = q[2:]
            if q[0:4] == "eid=":
                url.eid = q[4:]
            if q[0:5] == "from=":
                url.reqFrom = q[5:]
        return url

class RequestLine:
    def __init__(self, line=""):
        if line == "" :
            return
        urlStart = line.find(' ')+1
        self.httpMethod = line[0: urlStart-1]

        url_end = line.find(' ', urlStart)
        self.url = line[urlStart: url_end]

        self.version = line[url_end+1: ]

# for performance
class TimeStamp:
    def __init__(self, line):
        minStart = line.find(':') + 1
        self.minite = int(line[minStart : minStart + 2]);
        secStart = line.find(':', minStart + 1) + 1
        self.second = int(line[secStart : secStart + 2]);

class Record:
    def __init__(self):
        self.xff = ''
        self.remoteAddr = ''
        self.timestamp = None

        self.requestLineObj = None
        self.requestLineStr = ""
        self.urlObj = None

        self.statusCode = -1
        self.requestTime = -1

        self.host = ""
        self.refer = ""

    def __str__(self):
        desc = "xff ==> %s \ntimestamp ==> %s \n" % (self.xff, str(self.timestamp))
        desc += "requestLineStr ==> %s\n" % (self.requestLineStr)
        desc += "code ==> %d \nrequest_time ==> %f\n" % (self.statusCode, self.requestTime)
        desc += "host ==> %s \nrefer ==> %s" % (self.host, self.refer)
        return desc

class LogParser:
    def __init__(self, needTime=False):
        self.needTime = needTime

    def parse(self, line):
        record = Record()

        # parse xff and remote address
        ipsEnd = line.find("[") - 1
        ips = line[0:ipsEnd]
        xffEnd = ips.rfind(' ')

        record.xff = line[:xffEnd]
        record.remoteAddr = line[xffEnd+1:ipsEnd]

        # parse local time
        if self.needTime:
            timeStrStart = line.find("[") + 1
            timeStrEnd = line.find(" ", timeStrStart)
            timeStr = line[timeStrStart:timeStrEnd]
            #
            record.timestamp = time.mktime(time.strptime(timeStr,"%d/%b/%Y:%H:%M:%S"))
            # record.timestamp = TimeStamp(timeStr)
        timeEnd = line.find('[', ipsEnd)+1

        # parse http request
        reqLineStart = line.find('"', ipsEnd)+1
        reqLineEnd = line.find('"', reqLineStart)
        record.requestLineStr = line[reqLineStart: reqLineEnd]
        record.requestLineObj = RequestLine(record.requestLineStr)

        # parse url in http request
        record.urlObj = URLParser().parseURL(record.requestLineObj.url)

        # parse status code
        statusCodeStart = reqLineEnd + 2
        statusCodeEnd = line.find(' ', statusCodeStart)
        record.statusCode = int(line[statusCodeStart : statusCodeEnd])

        # parse request time
        requestTimeStart = statusCodeEnd + 1
        requestTimeEnd = line.find(" ", requestTimeStart)
        record.requestTime = float(line[requestTimeStart : requestTimeEnd])

        # parse host
        hostStart = requestTimeEnd + 2
        hostEnd = line.find('"', hostStart)
        record.host = line[hostStart: hostEnd]

        # parse referer
        referStart = hostEnd + 3
        referEnd = line.find('"', referStart)
        record.refer = line[referStart: referEnd]

        # $upstream_addr $upstream_status $upstream_response_time can be captured by awk '{ print $(NF-2/1/0) }'

        return record


#return tuple
def ip2net(ip, count):
    ip_int = 0
    for int8 in ip.split('.'):
        ip_int = (ip_int << 8) + int(int8)
    return ip_int & ( ((1 << (count+1))-1) << (32-count) ), count



class FileListReader :
    def init(self, inputFiles):
        self.fileList = inputFiles
        return

    def getLine(self):
        for filename in self.fileList :
            print "open file: %s" % filename
            fp = open(filename, "r")
            for line in fp :
                yield line;
        return


class Collector:
    def init(self):
        self.container = dict()
    def put(self, record):
        count = 0
        if record.remoteAddr in self.container:
            count = self.container[record.remoteAddr]
        self.container[record.remoteAddr] = (count+1)

    def dump(self,outputFile):
        print "begin to dump", outputFile
        fp = open(outputFile, "w")
        for (k,v) in self.container.items():
            output_str = str(v) + " " + k + "\n"
            fp.write(output_str)
        fp.close()

class VeValidator:
    def __init__(self, ve):
        self.ve = ve
    def isValid(self, record):
        return record.urlObj.ve == self.ve
    def __str__(self):
        return "VeValidator " + self.ve + " "

class LocationValidator:
    def __init__(self, location):
        self.location = location
    def isValid(self, record):
        return record.urlObj.location == self.location
    def __str__(self):
        return "LocationValidator " + self.location + " "

class FrValidator:
    def __init__(self, fr):
        self.fr = fr
    def isValid(self, record):
        return record.urlObj.fr == self.fr
    def __str__(self):
        return "FrValidator " + self.fr + " "

class FromValidator:
    def __init__(self, reqFrom):
        self.reqFrom = reqFrom
    def isValid(self, record):
        return record.urlObj.reqFrom == self.reqFrom
    def __str__(self):
        return "FromValidator " + self.reqFrom + " "

class HostValidator:
    def __init__(self, host):
        self.host = host
    def isValid(self, record):
        return record.host == self.host
    def __str__(self):
        return "HostValidator " + self.host + " "

class Executor :
    def __init__(self, ve, fr, host, req_from, location):
        self.conditions = set()
        if ve != "":
            print "add condition: ve = ", ve
            self.conditions.add(VeValidator(ve))

        if fr != "":
            print "add condition: fr = ", fr
            self.conditions.add(FrValidator(fr))

        if host != "":
            print "add condition: host = ", host
            self.conditions.add(HostValidator(host))

        if req_from != "":
            print "add condition: req_from = ", req_from
            self.conditions.add(FromValidator(req_from))

        if location != "/?":
            print "add condition: location = ", location
            self.conditions.add(LocationValidator(location))

    def init(self, ipListFile, inputFiles, outputFile) :
        print "input files:", inputFiles
        self.outputFile = outputFile
        ipReader = FileListReader()
        ipReader.init([ipListFile])
        self.buildIpSet(ipReader)

        self.logReader = FileListReader()
        self.logReader.init(inputFiles)

    def buildIpSet(self, ipReader):
        self.set = set()
        for line in ipReader.getLine():
            ip, count = line.split('/')
            self.set.add(ip2net(ip, int(count)))

    def valid(self, record):
        for cond in self.conditions:
            if not cond.isValid(record):
                print "record[", record,"] failed at [", cond, "]"
                return False
        return True

    def belong(self, record):
        for i in range(0,32):
            ip_int_tuple = ip2net(record.remoteAddr, i)
            if ip_int_tuple in self.set:
                return True
        return False

    def run(self):
        log_parser = LogParser()
        collector = Collector()
        collector.init()
        i=0
        for line in self.logReader.getLine():
            i += 1
            if i%10000 == 0:
                print "i:", i, "\r",
            record = log_parser.parse(line)

            if not self.valid(record) :
                print "discard line:", line
                continue
            if self.belong(record) :
                collector.put(record)
        collector.dump(self.outputFile)




def toList(filelist):
    return filelist.split('\n')

def read_ip_list(filename):
    fp = open(filename, "r")
    filelist = [line.strip() for line in fp ]
    return filelist



if __name__ == '__main__':
    line = '- 114.94.139.52 [26/Jun/2014:21:25:00 +0800] "POST /ucinput? HTTP/1.1" 200 0.004 "sugs.m.sm.cn" "refer" "UCWEB/9.7.1.450 CFNetwork/672.1.14 Darwin/14.0.0" "10.99.76.63:7650" "200" "0.002"'
    log_parser = LogParser(True)
    record = log_parser.parse(line)
    print record
    sys.exit(0)

    try:
        options,args = getopt.getopt(sys.argv[1:], "h",["help", "ipListFile=", "inputList=", "output=", "ve=", "fr=", "from=", "host=", "location="])
        for name,value in options:
            if name in ("-h","--help"):
                print "Usage:", sys.argv[0], "iplist input_files output_file"
                sys.exit(1)

            if name in ("--ipListFile"):
                print 'iplist is----',value
                ipListFile = value
            if name in ("--inputList"):
                print 'inputList is----',value
                inputFiles = read_ip_list(value)
            if name in ("--output"):
                print 'output is----',value
                outputFile = value

            if name in ("--ve"):
                print 've is----',value
                ve = value
            if name in ("--host"):
                print 'host is----',value
                host = value
            if name in ("--fr"):
                print 'fr is----',value
                fr = value
            if name in ("--from"):
                print 'from is----',value
                req_from = value
            if name in ("--location"):
                print 'location is----',value
                location = "/" + value + "?"

    except getopt.GetoptError, e:
        print "error:", e, str(getopt.GetoptError)
        sys.exit(1)

    e = Executor(ve, fr, host, req_from, location)
    if e.init(ipListFile, inputFiles, outputFile) == False:
        print "init executor failed"

    if e.run() == False :
        print "run failed"

# test_data: - 114.94.139.52 [26/Jun/2014:21:25:00 +0800] "POST /ucinput? HTTP/1.1" 200 0.004 "sugs.m.sm.cn" "refer" "UCWEB/9.7.1.450 CFNetwork/672.1.14 Darwin/14.0.0" "10.99.76.63:7650" "200" "0.002"


