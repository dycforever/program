#!/usr/local/bin/python2.7

from log_parser import LogParser
from log_parser import FileReader

class analyser:
    def report(self, record):
        if record.

if __name__ == '__main__':
    logParser = log_parser.()
    fp = open("output", "r")
    for line in fp:
        record = logParser.parse(line)

