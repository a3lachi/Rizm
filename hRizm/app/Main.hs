module Main (main) where

-- import Lexer
import Compiler (compile)

program :: IO Char
program = do
    putStrLn "Please enter a character:"
    getChar

main = do 
    print "TNAKT ALORS"
    compile program
