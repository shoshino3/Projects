# -*- coding: utf-8 -*-
"""
Created on Mon Feb 28 15:48:48 2022

@author: kajim
"""

import glob
import os

ext = 'JPG'

sorted_files = sorted(
    glob.glob('[*/DIRECTORY/TO/IMAGES/SOURCE/HERE/*]/*.' + ext), key=os.path.getmtime)

for i, f in enumerate(sorted_files, 1):
    try:
        head, tail = os.path.split(f)            
        # os.rename(f, os.path.join(head, str(i).zfill(2) + '_' + tail))
        os.rename(f, os.path.join(head, str(i + 189).zfill(2) + '.' + ext))
    except OSError:
        print('Invalid operation')