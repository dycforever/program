
data Color = Red | Blue | Green 
    deriving(Show)

data CantShowColor = CantShowColor
    deriving(Show)

data CantDervShowColor = CantDervShowColor CantShowColor
    deriving(Show)

main = do 
    print $ show Red
    print $ show CantShowColor

-- below won't compile
--    print $ show CantDervShowColor
