#!/bin/bash

proc=signaltest

pkill -USR1 $proc
pkill -HUP $proc
pkill -CHLD $proc
pkill -QUIT $proc

