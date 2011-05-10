#!/bin/sh
tolua++ -o tolua_$1.cpp -H tolua_$1.h -n $1 $1.pkg
mv tolua_$1.cpp source/
mv tolua_$1.h include/
