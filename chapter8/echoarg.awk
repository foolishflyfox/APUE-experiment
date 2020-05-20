#!/usr/bin/awk -f
# echoarg.awk
# Note: on Solaris, use nawk instead
BEGIN {
    for(i=0; i<ARGC; i++)
        printf "ARGV[%d] = %s\n", i, ARGV[i]
    exit
}
