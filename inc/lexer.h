#ifndef LEXER_H
#define LEXER_H

enum state {
    STATE_GENERAL,
    STATE_IN_SINGLE_QUOTE,
	STATE_IN_DOUBLE_QUOTE,
	STATE_AFTER_SYMBOL
};

enum character_category
{
    CHAR_GENERAL,
    CHAR_WHITESPACE = ' ',
	CHAR_SINGLE_QUOTE = '\'',
	CHAR_DOUBLE_QUOTE = '"',
    CHAR_AMPERSAND = '&',
    CHAR_PIPE = '|',
    CHAR_EOF = EOF,
};

#endif
