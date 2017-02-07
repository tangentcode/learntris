#!/usr/bin/env python
# this is learntris.py
import sys

val = raw_input()

if val == 'p':
    for x in range(1,23):
        for y in range(1,10):
           print('.'),
        print '.'
