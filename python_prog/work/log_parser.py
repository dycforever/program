#!/usr/local/bin/python2.7

import sys;
import getopt
import time
import math
import json

class URLObject:
    def __init__(self):
        self.location = ''
        self.querys = []
        self.fr = ''
        self.ve = ''
        self.q = ''
        self.reqFrom = ''
        self.eid= ''
    def __str__(self):
        desc = "url location ==> %s \n  ve ==> %s \n  fr ==> %s\n" % (self.location, self.ve, self.fr)
        desc += "  from ==> %s \n " % (self.reqFrom)
        return desc


class URLParser:
    def parseURL(self, urlStr):
        urlStr = urlStr.strip()
        url = URLObject()
        locationEnd = urlStr.find('?')
        url.location = urlStr[1:locationEnd]
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
        return

    def __str__(self):
        return "methed: " + self.httpMethod + " version: " + self.version

# for performance
class TimeStamp:
    def __init__(self, line):
        self.minite = ""
        self.second = ""
        if (line == None or line == ""):
            return
        minStart = line.find(':') + 1
        self.minite = int(line[minStart : minStart + 2]);
        secStart = line.find(':', minStart + 1) + 1
        self.second = int(line[secStart : secStart + 2]);

    def __str__(self):
        return "minite: " + str(self.minite) + " second: " + str(self.second)

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
        desc += "%s\n" % (str(self.urlObj))
        desc += "code ==> %d \nrequest_time ==> %f\n" % (self.statusCode, self.requestTime)
        desc += "host ==> %s \nrefer ==> %s" % (self.host, self.refer)
        return desc

class LogParser:
    def parse(self, line):
        record = Record()

        # parse xff and remote address
        ipsEnd = line.find("[") - 1
        ips = line[0:ipsEnd]
        xffEnd = ips.rfind(' ')

        record.xff = line[:xffEnd]
        record.remoteAddr = line[xffEnd+1:ipsEnd]

        # parse local time
        timeStrStart = line.find("[") + 1
        timeStrEnd = line.find(" ", timeStrStart)
        timeStr = line[timeStrStart:timeStrEnd]
        # record.timestamp = time.mktime(time.strptime(timeStr,"%d/%b/%Y:%H:%M:%S"))
        record.timestamp = TimeStamp(timeStr)
        timeEnd = line.find('[', ipsEnd)+1

        # parse http request
        reqLineStart = line.find('"', ipsEnd)+1
        reqLineEnd = line.find('"', reqLineStart)
        record.requestLineStr = line[reqLineStart: reqLineEnd]
        record.requestLineObj = RequestLine(record.requestLineStr)

        # parse url in http request
        record.urlObj = URLParser().parseURL(record.requestLineObj.url)
        if (record.urlObj == None):
            print "parse url failed"
            return

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

class DefaultCollector:
    def init(self, outputFile):
        self.mOutputFile = outputFile

    def put(self, record):
        pass
    def dump(self):
        pass

class IpCollector(DefaultCollector):
    def init(self, outputFile):
        self.container = dict()
        self.outputFile = outputFile

    def put(self, record):
        count = 0
        if record.remoteAddr in self.container:
            count = self.container[record.remoteAddr]
        self.container[record.remoteAddr] = (count+1)

    def dump(self):
        print "begin to dump", outputFile
        fp = open(self.outputFile, "w")
        for (k,v) in self.container.items():
            output_str = str(v) + " " + k + "\n"
            fp.write(output_str)
        fp.close()


class Executor :
    def __init__(self):
        self.mCondition = None
        self.mCollector = None
        self.mLogFile = None

    def init(self, inputFile, outputFile, conditionFile) :
        fp = open(conditionFile, "r")
        content = fp.read()
        self.mCondition = Condition(json.loads(content))

        self.mLogFile = open(inputFile, "r")

        if self.mCollector == None:
            self.mCollector = DefaultCollector()
        self.mCollector.init(outputFile)

    def run(self):
        log_parser = LogParser()
        i=0
        for line in self.mLogFile:
            i += 1
            if i%10000 == 0:
                print "i:", i, "\r",
            record = log_parser.parse(line)

            if not self.mCondition.judge(record) :
#                print "discard line:", line
                continue
            self.mCollector.put(record)
        self.mCollector.dump()




def toList(filelist):
    return filelist.split('\n')

def read_ip_list(filename):
    fp = open(filename, "r")
    filelist = [line.strip() for line in fp ]
    return filelist



class VeValidator:
    def prefixCompare(self, str1, str2):
        length = min(len(str1), len(str2))
        for i in range(0, length):
            if str1[i] != str2[i]:
                return False
        return True

    def __init__(self, veList):
        self.veList = veList

    def isValid(self, record):
        for item in self.veList:
            if self.prefixCompare(record.urlObj.ve, item):
                return True
        return False

    def __str__(self):
        return "VeValidator " + str(self.veList) + " "

class LocationValidator:
    def __init__(self, locationList):
        self.locationList = locationList

    def isValid(self, record):
        for item in self.locationList:
            if record.urlObj.location == item:
                return True
        return False

    def __str__(self):
        return "LocationValidator " + str(self.locationList) + " "

class FrValidator:
    def __init__(self, frList):
        self.frList = frList

    def isValid(self, record):
        for item in self.frList:
            if record.urlObj.fr == item:
                return True
        return False

    def __str__(self):
        return "FrValidator " + str(self.frList) + " "

class FromValidator:
    def __init__(self, reqFromList):
        self.reqFromList = reqFromList
    def isValid(self, record):
        for item in self.reqFromList:
            if record.urlObj.reqFrom == item:
                return True
        return False

    def __str__(self):
        return "FromValidator " + str(self.reqFromList) + " "

class HostValidator:
    def __init__(self, hostList):
        self.hostList = hostList
    def isValid(self, record):
        for item in self.hostList:
            if record.host == item:
                return True
        return False

    def __str__(self):
        return "HostValidator " + str(self.hostList) + " "

class IpValidator:
    def __init__(self, ipListFileList):
        self.ipSet = set()
        for ipListFile in ipListFileList:
            ipListFilep = open(ipListFile, "r")
            for line in ipListFilep:
                ip, count = line.split('/')
                self.ipSet.add(ip2net(ip, int(count)))
            ipListFilep.close()


    def isValid(self, record):
        for i in range(0,32):
            ip_int_tuple = ip2net(record.remoteAddr, i)
            if ip_int_tuple in self.ipSet:
                return True
        return False

    def __str__(self):
        return "IpValidator "

class TimeValidator:
    def __init__(self, timeRange):
        self.startTime = TimeStamp("")
        self.endTime = TimeStamp("")

        startMin, startSec = timeRange[0].split(":")
        self.startTime.minite = int(startMin)
        self.startTime.second = int(startSec)

        endMin, endSec = timeRange[1].split(":")
        self.endTime.minite = int(endMin)
        self.endTime.second = int(endSec)

    def timeCompare(self, time1, time2):
        if (time1.minite < time2.minite):
            return -1
        if (time1.minite > time2.minite):
            return 1
        # equal minite
        if (time1.second < time2.second):
            return -1
        if (time1.second > time2.second):
            return 1
        return 0


    def isValid(self, record):
        if (self.timeCompare(self.startTime, record.timestamp) <= 0
                and self.timeCompare(self.endTime, record.timestamp) > 0):
            return True
        return False

    def __str__(self):
        return "TimeValidator from " + str(self.startTime) + " to " + str(self.endTime)

class ValidatorRegister:
    def __init__(self, conditions):
        self.mValidatorMap = {
                "location" : LocationValidator(conditions["location"]),
                "from" : FromValidator(conditions["from"]) ,
                "fr" : FrValidator(conditions["fr"]),
                "ve" : VeValidator(conditions["ve"]),
                "host" : HostValidator(conditions["host"]),
                "ip" : IpValidator(conditions["ip"]),
                "time_range" : TimeValidator(conditions["time_range"]),
                }
        return

    def getValidator(self, cond):
        if (cond in self.mValidatorMap.keys()):
            return self.mValidatorMap[cond]
        else:
            return None



class Condition:
    def __init__(self, conditions):
        register = ValidatorRegister(conditions)
        self.mValidatorMap = {}
        for key in conditions.keys():
            self.mValidatorMap[key] = register.getValidator(key)

        return

    def judge(self, record):
        for key in self.mValidatorMap:
            validator = self.mValidatorMap[key]
            if (validator != None and not validator.isValid(record)):
#                print "record[\n", record,"\n] failed at [", str(validator), "]"
                return False
        return True



def test():
    fp = open("./condition.json", "r")
    content = fp.read()
    condition = Condition(json.loads(content))
    line = '- 114.94.139.52 [26/Jun/2014:21:25:00 +0800] "POST /s?q=qq&fr=iphone&from=uczj&ve=9.8.1.22 HTTP/1.1" 200 0.004 "m.sm.cn" "refer" "UCWEB/9.7.1.450 CFNetwork/672.1.14 Darwin/14.0.0" "10.99.76.63:7650" "200" "0.002"'

# test_data: - 114.94.139.52 [26/Jun/2014:21:25:00 +0800] "POST /ucinput? HTTP/1.1" 200 0.004 "sugs.m.sm.cn" "refer" "UCWEB/9.7.1.450 CFNetwork/672.1.14 Darwin/14.0.0" "10.99.76.63:7650" "200" "0.002"

    log_parser = LogParser(True)
    record = log_parser.parse(line)

    assert condition.judge(record)
    sys.exit(0)


if __name__ == '__main__':
    if len(sys.argv) < 2:
        print "Usage:", sys.argv[0], "-c condition.json -o output_file"
        sys.exit(-1)
    inputFile = ""
    outputFile = ""
    conditionFile = ""
    try:
        options,args = getopt.getopt(sys.argv[1:], "hi:c:o:", ["help"])
        for name,value in options:
            if name in ("-h","--help"):
                print "Usage:", sys.argv[0], "-c condition.json -o output_file"
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
    if e.init(inputFile, outputFile, conditionFile) == False:
        print "init executor failed"

    if e.run() == False :
        print "run failed"



