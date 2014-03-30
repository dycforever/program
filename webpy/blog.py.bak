#!/usr/bin/python
import web

blog_urls = (
        '', 'reblog',
        '/(.*)', 'blog',
        '/py/blog/', 'blog',
        '/py/blog', 'blog',
        )

class reblog:
    def GET(self):
        fp = open("/home/dyc/web/web.py/logs", "wa")
        fp.write("reblog " + path + '\n');
        fp.close()
        raise web.seeother('/')

    def POST(self):
        return "reblog post"



class blog:
#    def GET(self, path):
#        fp = open("/home/dyc/web/web.py/logs", "wa")
#        fp.write("blog " + path + '\n');
#        fp.close()
#        return "blog " + path
    def GET(self):
        fp = open("/home/dyc/web/web.py/logs", "wa")
        fp.write("blog ");
        fp.close()
        return "blog "

    def POST(self, path):
        return "blog " + path

#web.wsgi.runwsgi = lambda func, addr=None: web.wsgi.runfcgi(func, addr)
app_blog = web.application(blog_urls, locals())
print "blog.py run"