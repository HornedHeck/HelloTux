#!/bin/bash

in_list=(test_samples/in-*.txt)

for i in "${!in_list[@]}"; do
  echo "Running test №$((i + 1))"
  ./build/morze <"${in_list[$i]}" >"test_samples/out-$((i + 1)).txt"
  if cmp -s "test_samples/out-expected-$((i + 1)).txt" "test_samples/out-$((i + 1)).txt"; then
    echo "Passed"
  else
    echo "Fail"
    break
  fi
done
