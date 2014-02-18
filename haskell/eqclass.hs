
data Color = Red | Blue | Green 

class BasicEq a where
    isEqual :: a -> a -> Bool
    isEqual x y = not (isNotEqual x y)

    isNotEqual :: a -> a -> Bool
    isNotEqual x y = not (isEqual x y)


instance BasicEq Color where 
    isEqual Red Red = True
    isEqual Blue Blue = True
    isEqual Green Green = True
    isEqual _ _ = False

instance Show Color where
    show Red = "Red"
    show Blue = "Blue"
    show Green = "Green"

--module Main where
main = do print $ show Red
