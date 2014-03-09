
--module func where
lazyfib x y = x:(lazyfib y (x+y))
fib = lazyfib 0 1
fibNth n = head (drop (n-1) (take n fib))

pyth :: Int -> Int -> Int
pyth a b = a+b

main = do
    print $ ""

