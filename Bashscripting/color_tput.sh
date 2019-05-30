#!/bin/bash

# Change terminal text output color
# 
# To use:  tput setaf 1; echo "testing"
# To stack commands:
# tput bold; tput setaf 1; echo "testing"

# Num  Colour    #define         R G B

# 0    black     COLOR_BLACK     0,0,0
# 1    red       COLOR_RED       1,0,0
# 2    green     COLOR_GREEN     0,1,0
# 3    yellow    COLOR_YELLOW    1,1,0
# 4    blue      COLOR_BLUE      0,0,1
# 5    magenta   COLOR_MAGENTA   1,0,1
# 6    cyan      COLOR_CYAN      0,1,1
# 7    white     COLOR_WHITE     1,1,1


# Text mode commands:
# tput bold    # Select bold mode
# tput dim     # Select dim (half-bright) mode
# tput smul    # Enable underline mode
# tput rmul    # Disable underline mode
# tput rev     # Turn on reverse video mode
# tput smso    # Enter standout (bold) mode
# tput rmso    # Exit standout mode

# Cursor movement commands
# tput cup Y X # Move cursor to screen postion X,Y (top left is 0,0)
# tput cuf N   # Move N characters forward (right)
# tput cub N   # Move N characters back (left)
# tput cuu N   # Move N lines up
# tput ll      # Move to last line, first column (if no cup)
# tput sc      # Save the cursor position
# tput rc      # Restore the cursor position
# tput lines   # Output the number of lines of the terminal
# tput cols    # Output the number of columns of the terminal


# Clear and insert commands
# tput ech N   # Erase N characters
# tput clear   # Clear screen and move the cursor to 0,0
# tput el 1    # Clear to beginning of line
# tput el      # Clear to end of line
# tput ed      # Clear to end of screen
# tput ich N   # Insert N characters (moves rest of line forward!)
# tput il N    # Insert N lines


# Other commands
# tput sgr0    # Reset text format to the terminal's default
# tput bel     # Play a bell