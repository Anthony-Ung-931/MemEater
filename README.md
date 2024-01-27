Anthony Ung

This program leaks memory continuously.
It displays "ERRNO = ENOMEM" when no more memory is available to be leaked.
When the user enters ^C at the keyboard, statistics are displayed
    indicating the block size, the number of blocks, and the number of
    bytes leaked.
