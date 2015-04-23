#!/bin/sh
antlr -gt $1.g
dlg -ci parser.dlg scan.c
g++ -o $1 $1.c scan.c err.c