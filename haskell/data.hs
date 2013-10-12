
import Data.Char

-- module Main where
data Triple a = Trio a a a deriving (Show)
data Tree a = Children [Tree a] | Leaf a deriving (Show)




data Operator = Plus | Minus | Times | Div | LParen | RParen | TokAssign
    deriving (Show, Eq)

data Token = TokOp Operator
           | TokIdent String
           | TokNum Int
    deriving (Show, Eq)

operator :: Char -> Operator
operator c | c == '+' = Plus
           | c == '-' = Minus
           | c == '*' = Times
           | c == '/' = Div
           | c == '(' = LParen
           | c == ')' = RParen
           | c == '=' = TokAssign

tokenize :: String -> [Token]
tokenize [] = []
tokenize (c : cs) 
    | elem c "+-*/()=" = TokOp (operator c) : tokenize cs
    | isDigit c = number c cs
    | isAlpha c = identifier c cs
    | isSpace c = tokenize cs
    | otherwise = error $ "Cannot tokenize " ++ [c]

identifier c cs = let (str, cs') = span isAlphaNum cs in
                  TokIdent (c:str) : tokenize cs'

number c cs = 
   let (digs, cs') = span isDigit cs in
   TokNum (read (c : digs)) : tokenize cs'

main = do
    print $ tokenize "(12 + 24)/ x1 == 2"
