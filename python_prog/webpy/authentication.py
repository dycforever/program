import hashlib
import web

urls = (
        "/login", "login"
        )
app = web.application(urls, locals())


class login:
    def POST(self):
        i = web.input()
        print "i=%s" % str(i)
        return i.password

    def GET(self):
        print "i=NULL"
        return "get"


if __name__ == "__main__":
    app.run()