#!/usr/bin/python
# -*- coding: utf-8 -*-

import web
import blog

# 坑爹啊，跳转的时候，pattern后面跟的是class obj而不是字符串
# 浪费了我多少时间啊，设计不一致啊！！！
urls = (
        "/py/signin", "signin",
        "/py/list/(.+)", "listing",
        "/py/post", "post",
        "/py/chgpass", "chgpass",
        "/py/act", "actions",
        "/py/logout", "logout",
        "/py/signup", "signup",
        "/py/index", "hello",
        "/py/req", "requestHandler",
        "/py/blog", blog.app_blog,
        )
app = web.application(urls, locals())

# 用以捕获参数
# 允许这样访问： http://127.0.0.1:8087/py/index?name=dyc
class hello:
    def GET(self):
        render = web.template.render('.')
        i=web.input(name=None)
        return render.templates(i.name)

class signin:
    def GET(self):
        ref = web.ctx.env.get('HTTP_REFERER', '');
        return 'sign in! HTTP_REFERER:' + str(ref)

class signout:
    def GET(self):
        return 'sign out!'

class signup:
    def GET(self):
        raise web.seeother('/py/signin')

class post:
    def GET(self):
        return 'post!'

class actions:
    def GET(self):
        return 'action!'

# url中list后面的小括号就起到了捕获变量的作用
# 允许这样访问：  http://127.0.0.1:8087/py/list/dyc
class listing:
    def GET(self, name):
        return 'list ' + str(name)

#    def GET(self):
#        return 'list '

class requestHandler:
    def POST():
        data = web.data() # you can get data use this method

class chgpass:
    def GET(self):
        return 'chgpass!'

if __name__ == "__main__":
#    web.wsgi.runwsgi = lambda func, addr=None: web.wsgi.runfcgi(func, addr)
    app.run()
