#!/bin/bash
timestamp=`date "+%Y-%m-%d  %H:%M"`
git commit -a -m "$timestamp" 
git push origin master
