#!/bin/bash

spawn-fcgi -n -u dyc -d /home/dyc/web/web.py/ -f /home/dyc/web/web.py/first.py -a 127.0.0.1 -p 9002

