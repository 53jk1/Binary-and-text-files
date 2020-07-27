# $ python write1.py
# $ hexdump -C example.bin
#!/usr/bin/python
# -*- coding: utf-8 -*-
# High-level creation of the entire file in memory.
from struct import pack

# Create a character file:
# N
# 0:
# 1: 1
# 2: 2 2
# ...
# N-1: N-1 N-1 ... N-1

N = 5
data = []

# Append a 16-bit number of sets to the data.
# The <format character stands for Little Endian, and H is a 16-bit natural number.

data.append(pack("<H", N))

# Generate N sets with simple numbers.
for M in range(N):
    # Append an 8-bit number with the number of values in the set.
    # The B format character represents an 8-bit natural number.
    data.append(pack("B", M))

    # Add M values to the set.
    # The I format character denotes a 32-bit natural number.
    for _ in range(M):
        data.append(pack("<I", M))

# Save the generated data to a file.
with open("example.bin", "wb") as f:
    f.write(b''.join(data))