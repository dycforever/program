
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

instance Read Color where
    -- readsPrec is the main function for parsing input
    readsPrec _ value = 
        -- We pass tryParse a list of pairs.  Each pair has a string
        -- and the desired return value.  tryParse will try to match
        -- the input to one of these strings.
        tryParse [("Red", Red), ("Green", Green), ("Blue", Blue)]
        where tryParse [] = []    -- If there is nothing left to try, fail
              tryParse ((attempt, result):xs) =
                      -- Compare the start of the string to be parsed to the
                      -- text we are looking for.
                      if (take (length attempt) value) == attempt
                         -- If we have a match, return the result and the
                         -- remaining input
                         then [(result, drop (length attempt) value)]
                         -- If we don't have a match, try the next pair
                         -- in the list of attempts.
                         else tryParse xs

--module Main where
main = do print $ show Red

