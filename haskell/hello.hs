program :: String -> String
program x = "[ " ++ x ++ " ]"

main :: IO ()
main = do
    s <- getContents
    putStr (program s)
