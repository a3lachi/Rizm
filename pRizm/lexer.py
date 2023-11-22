from dataclasses import dataclass



class Lexer:
    def __init__(self, program):
        self.program = program
        print('[x] - Initializing the lexer...')

    def tokenize(self):
        print(self.program)




class TokenType:
    INTEGER = 1
    FLOAT = 2
    STRING = 3
    BOOL = 4
    IF = 5
    ELSE = 6
    WHILE = 7
    SEMICOLON = 8
    TRU = 9
    FALS = 10
    COLON = 11
    NAME = 12
    LPAREN = 13
    RPAREN = 14
    LBRACE = 15
    RBRACE = 16
    EQUAL = 17
    PLUS = 18
    MINUS = 19
    MULTIPLY = 20
    DIVIDE = 21
    RETURN = 22
    FOR = 23
    PRINT = 24
    QUOTE = 25
    DOUBLEQUOTE = 26
    VALUE = 27
    IMPORT = 28
    COMMENT = 29
    EMPTYLINE = 30
    UKNOWN = 31
    SPACE = 32
    EMPTY = 33
    NEWLINES = 34
    GREATER = 35
    LESS = 36
    IN = 37
    RBRACKET = 38
    LBRACKET = 39
    UKNOWN_INT = 40
    UKNOWN_STRING = 41
    UKNOWN_FLOAT = 42
    UKNOWN_VARNAME = 43
    RANGE_SKIP = 44
    VALUE_BOOL = 45
    RANGE = 46
    PATH = 47
    COMMA = 48
    SPACES = 49
    STRING_INT = 50
    VALUE_STRING = 51
    NEWLINE = 52


@dataclass
class RizmToken:
    type: TokenType
    value: str

@dataclass
class RizmTokenS:
    token: RizmToken
    next: 'RizmTokenS' = None




aa = TokenType.INTEGER


print('Lexer working perfectly')