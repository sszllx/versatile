#!/bin/bash
#generateBigJson.sh
 
MAX=15000
echo "{\"arr\":["
i=1
while [ $i -le $MAX ]; do
    echo -ne "{\"id\":$i, \"next\":\"asdfasdfasdfqwefqwefasdfasdfasdgasdgasdgasdgasdfasdfasdfasdfasdfqwefqwefqwefasdfasdf\", \"id1\":$i, \"next1\":$((i+1)), \"id2\":$i, \"next2\":$((i+1))}"
  if [ "$i" -ne "$MAX" ]; then
    echo ","
  fi
  let i=i+1
done
echo "]}"
