module Lexer
    ( listDelimiterString,
        sk
    ) where

listDelimiterString :: IO ()
listDelimiterString = putStrLn "someFunc"


main :: IO ()
main = print (div 92 10) -- div is being used as a prefix function



{- 
    Using infix with `` 
-}
anotherMain :: IO ()
anotherMain = print (92 `div` 10) -- div is a infix function



{-
    FUNCTIONS
-}
firstKind :: Num a => a -> a -> a -- signature for -Wsignature
firstKind a  b = a * b
sk :: Num a => a -> a -> a -> a -> a
sk a b c d = firstKind a b + firstKind c d 


