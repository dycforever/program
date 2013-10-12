
import Data.Char

func :: (String, String) -> Char -> (String, String)
func (acc, lst) c = if Data.Char.isAlphaNum c
                        then (acc ++ [c], lst)
                        else (acc, lst ++ [c])

alnums :: String -> (String, String)
alnums = foldl func ("", "")

parse :: (String , String) -> String
parse (str, _) = str

main = do
    print $ (parse.alnums) "a14 haha"

