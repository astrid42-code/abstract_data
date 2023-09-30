#!/bin/sh

make ft
# time ./containers > test_ft
./containers > test_ft

make std
# time ./containers > test_std
./containers > test_std

diff test_ft test_std -s