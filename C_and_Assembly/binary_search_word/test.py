#!/usr/bin/env python3

import subprocess
import os, sys   

'''
This script will convert an .iso file to a disk image
and write it to a disk that you select
MUST BE RUN IN DIRECTORY WHERE THE ISO FILE IS STORED
'''
count = 0
no_words = ["boner","balls","dicks"]
for i in no_words:
    p = subprocess.Popen(["./ok", i], stdout=subprocess.PIPE)
    result = p.stdout.read().decode('utf-8')
    if 'yes' in result:
        count += 1


with open('webster') as f:

    lines = f.readlines()
    count = 0
    for i in lines:
        words = i.strip()
        p = subprocess.Popen(["./ok", words], stdout=subprocess.PIPE)
        result = p.stdout.read().decode('utf-8')
        if 'yes' in result:
            count += 1
    print(count)

        
sys.exit("Process Complete")
