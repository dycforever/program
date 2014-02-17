
import System.Environment (getArgs)
import Data.Char

--module JsonParse (
--    JValue(..)
--    getString,
--    getInt,
--    getDouble,
--    getBool,
--    getObject,
--    getArray,
--    isNull
--) where

data JValue = JString String |
              JNumber Double |
              JBool Bool |
              JArray [JValue]|
              JObject [(String, JValue)]|
              JNull |
              Other 
              deriving (Show)

toDouble :: String -> Double
toDouble cs = toDouble_ 0 cs

--charToInt :: Char -> Int
--charToInt c = c - '0'
--charToInt _ = 0

toDouble_ :: Double->String->Double
toDouble_ sum (c:cs) = toDouble_ ((sum*10) + fromIntegral(ord c)) cs
toDouble_ sum [] = sum

classify :: String -> JValue
classify w 
        | w == "null"  = JNull
        | w == "true" || w == "True" = JBool True
        | w == "false" || w == "False" = JBool False
        | isAlpha (head w) = JString w
        | isDigit (head w) = JNumber (toDouble w)
        | otherwise = Other

judge :: [String] -> [JValue]
judge (w:ws) = classify w : judge ws
judge (_) = []

myFunction = judge.words

interactWith function inputFile outputFile = do
  input <- readFile inputFile
  print $ (function input)

--writeFile outputFile (function input)

main = mainWith myFunction
  where mainWith function = do
          args <- getArgs
          case args of
            [input] -> interactWith function input "output"
            _ -> interactWith function "dyc.json" "output"

 --           _ -> putStrLn "error: exactly two arguments needed"