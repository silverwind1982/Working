#! /bin/bash

X=3

[ $X -ne 0 ] && echo "X isn't zero" || echo "X is zero"

[ -f $X ] && echo "X is a file" || echo "X is not a file"

[ -z "$USER" ] && echo "The \$USER variable is empty" || \
        echo "The \$USER variable is set to: \"${USER}\""

[ -n "$X" ] && echo "X is of non-zero length" || \
        echo "X is of zero length"
