#!/usr/bin/python
import argparse
import sys
import urllib;

if __name__ == '__main__':
    try:
        parser = argparse.ArgumentParser(description='tengine log analysis tool')
        parser.add_argument("ipList", help="ipList file")
        parser.add_argument("inputList", help="list of files need to analyse")
        parser.add_argument("--output", help="output file name")

        parser.add_argument("--ve", help="specify ve's value in url parameters")
        parser.add_argument("--fr", help="specific fr's value in url parameters")
        parser.add_argument("--reqFrom", help="specific from's value in url parameters")
        parser.add_argument("--host", help="specific host's value in url parameters")
        parser.add_argument("--location", help="specific location's value in url parameters")

        args = parser.parse_args()
        if args.ipList:
            ipList = args.ipList
            print "ipList: ", args.ipList
        if args.inputList:
#            inputList = read_ip_list(args.inputList)
            print "inputList: ", args.inputList
        if args.output:
            output = args.output
            print "output: ", args.output
        if args.ve:
            ve = args.ve
            print "ve: ", args.ve
        if args.fr:
            fr = args.fr
            print "fr: ", args.fr
        if args.reqFrom:
            reqFrom = args.reqFrom
            print "from: ", args.reqFrom
        if args.host:
            host = args.host
            print "host: ", args.host
        sys.exit(0)

    except argparse.ArgumentError as e:
        print "error: ", e.value
        sys.exit(1)



#        options,args = getopt.getopt(sys.argv[1:], "h",["help", "ipList=", "inputList=", "output=", "ve=", "frx=", "from=", "host=", "action="])
#        for name,value in options:
#            if name in ("-h","--help"):
#                print "Usage:", sys.argv[0], "ipList input_files output_file"
#                sys.exit(1)
#
#            if name in ("--ipList"):
#                print 'ipList is----',value
#                ipList = value
#            if name in ("--inputList"):
#                print 'inputList is----',value
#                inputFiles = read_ip_list(value)
#            if name in ("--output"):
#                print 'output is----',value
#                outputFile = value
#
#            if name in ("--ve"):
#                print 've is----',value
#                ve = value
#            if name in ("--host"):
#                print 'host is----',value
#                host = value
#            if name in ("--frx"):
#                print 'fr is----',value
#                fr = value
#            if name in ("--from"):
#                print 'from is----',value
#                req_from = value
#            if name in ("--action"):
#                print 'action is----',value
#                action = "/" + value + "?"
