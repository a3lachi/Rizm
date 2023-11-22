import lexer
import sys

    
def main():
    
    program = open(sys.argv[1] , 'r').read()

    rizmLexer = lexer.Lexer(program)


if __name__ == "__main__":
    main()