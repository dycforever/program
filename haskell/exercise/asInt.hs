import Data.Char

_asInt (c:cs) sum = _asInt cs (sum*10 + (digitToInt c))
_asInt _ sum = sum

--注意参数的顺序，第一个参数决定了返回类型
_fold_sum sum c = sum*10 + digitToInt c
asInt_fold (c:cs) 
        | c=='-' = (- foldl _fold_sum 0 cs)
        | isDigit c = foldl _fold_sum 0 (c:cs)
        | otherwise = error  "not a digit " 
asInt_fold _ =  0 

asInt_lambda (c:cs) 
        | c=='-' = (- foldl (\sum c -> sum*10 + digitToInt c) 0 cs)
        | isDigit c = foldl (\sum c -> sum*10 + digitToInt c) 0 (c:cs)
        | otherwise = error  "not a digit " 
asInt_lambda _ =  0 

asInt::String->Int
asInt (c:cs) 
    | c=='-' = (- _asInt cs 0 )
    | isDigit c = _asInt (c:cs) 0 
    | otherwise = 0
asInt _ = 0
