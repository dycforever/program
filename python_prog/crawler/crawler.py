#!/usr/bin/python
import urllib2
import re
import StringIO
import gzip

ua = { #'User-Agent':'Mozilla/5.0 (compatible; Googlebot/2.1; +Googlebot - Webmaster Tools Help)',
'User-Agent':'Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.11 (KHTML, like Gecko) Chrome/23.0.1271.64 Safari/537.11',
'Connection': 'close',
'Accept-Language': 'zh-CN,zh;q=0.8',
'Accept-Encoding': 'gzip,deflate,sdch',
'Accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8',
'Accept-Charset': 'GBK,utf-8;q=0.7,*;q=0.3',
'Cache-Control': 'max-age=0',
}

def get_html(url_address):
    '''open url and read it'''
    req_http = urllib2.Request(url_address,headers=ua)
    #req_http = urllib2.Request(url_address)
    html = urllib2.urlopen(req_http).read()
    print "len: %d" % len(html)
    return html

def controller():
    '''make url list and download page'''

    urlt = 'http://www.matrix67.com/blog/page/%d'
    reget = re.compile('(<div class=\"post-wrapper.*?)<p class=\"pagination\">',re.DOTALL)
    fp=open("org.txt","w+")
    for i in range (1,100):
        html_c = get_html(urlt% (i))
        print urlt%(i)
#        html_c = gzip.GzipFile(fileobj=StringIO.StringIO(html_c)).read()
        res = reget.findall(html_c)
        for x in res :
            fp.write(x)
        fp.write("\n\n\n")

    fp.close();
    return

controller()

