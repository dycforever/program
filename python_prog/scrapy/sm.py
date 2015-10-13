#!/usr/bin/python
import scrapy

class SMSpider(scrapy.Spider):
    name = 'sm.cn'
    start_urls = ['https://ft.sm.cn/A4/upload.html']
    def parse(self, response):
        pass
#        print "response: ",response

    def parse_question(self, response):
        yield {
                'title': response.css('h1 a::text').extract()[0],
                'link': response.url,
                }
