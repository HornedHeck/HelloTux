#!/bin/bash

echo "Start at $(date '+%T')"
./cmake-build-debug/Client 0.0.0.0 8000 < test_input.txt &
./cmake-build-debug/Client 0.0.0.0 8000 < test_input.txt &
wait
echo "End at $(date '+%T')"