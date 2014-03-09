
zipLst :: ([a], [b]) -> [(a, b)]

zipLst (h1:as, h2:bs) = (h1,h2):zipLst (as,bs)
zipLst ([], _) = []
zipLst (_, []) = []

main = print $ zipLst ([1, 2, 3, 4], "Hello")
