#!/bin/bash

#Change this variable based on directory of your SpiderBite project
CURR_DIR="/home/$USER/git/SpiderBite/"

cd $CURR_DIR

#Change the "url_list" to your url folder
./SpiderBite $CURR_DIR/url_list/*

wait

#Change the "result" folder to your html folder
if [ -d "$CURR_DIR/result" ]; then
  if [ -f "$CURR_DIR/result/test.html" ]; then
    FILE_SIZE=$(wc -c <"$CURR_DIR/result/test.html")
    if [ $FILE_SIZE -ge 0 ]; then
      echo "file size is not zero"
    else
      echo "file size is zero"
    fi
  else
    echo "file not found"
  fi
else
  echo "folder not exist"
fi