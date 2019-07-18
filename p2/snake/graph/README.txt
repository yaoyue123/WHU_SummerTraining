The files consist of a game parameter section, followed
by a game board data section.

The game parameter section consists of five space delimited values, followed by a newline
character:
    The number of rows in the game board, as a decimal integer.
    The number of columns in the game board, as a decimal integer.
    The delay between each game iteration in seconds, as a fraction containing decimal.
    The probability of food being added to the board in each game iteration, as a fraction
        containing decimal.
    The number of segments snakes grow when they eat food, as a decimal integer.

The game board data sections consists of newline delimited rows of game data. Each row
represents a row of the game board, with row 0 being the first row in the game board data
section. In each row is a sequence of characters, each character representing a cell in
the game board with the first character corresponding to column 0.  Characters are
interpreted as follows:

'X': A wall cell
'-': An open cell
'N','S','E','W': A single segment computer controlled snake with the same respective initial
                 heading.
