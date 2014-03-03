module Main (main) where

import JsonParse

main = print (JObject [("foo", JNumber 1), ("bar", JBool False)])