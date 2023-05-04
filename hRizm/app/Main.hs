module Main (main) where

import Lexer
import Compiler (compiler)

main :: IO ()
main = print (sk 1 2 4 2)
