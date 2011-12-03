#!/bin/bash
# 
# File:   test.bash
# Author: gmc
#
# Created on 03-Dec-2011, 01:30:44
#

fusermount -u ~/mnt/aux
$1 -o repo=/home/gmc/.dfuser/repo ~/mnt/aux