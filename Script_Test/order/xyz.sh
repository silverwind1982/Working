#!/bin/bash
echo "Start"

sleep 3 && echo "sleep 3 is done" &
sleep 2 && echo "sleep 2 is done" &
sleep 1 && echo "sleep 1 is done" &

wait

echo "Done"
