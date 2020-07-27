# > python parseini.py
#!/usr/bin/python
# -*- coding: utf-8 -*-
import pprint
import sys

def parse_ini(fname):
    ini = {}
    section = {}
    ini["__global__"] = section

    with open(fname) as f:
        for ln in f: # Line by line reading
            # Comment
            if ln.startswith(';'):
                continue

            # Remove whitespace at line end/start.
            ln = ln.strip()

            if ln.startswith('[') and ln.endswith(']'):
                section_name = ln[1:-1].strip() # Get the section name.
                section = {}
                ini[section_name] = section
                continue

            # Ignoring blank and invalid lines.
            if '=' not in ln:
                continue

            # Break the line into two parts about the = sign and remove
            # the white space from the start and end of both parts.
            name, val = [x.strip() for x in ln.split("=", 1)]
            section[name] = val

    return ini

if __name__ == "__main__":
    pp = pprint.PrettyPrinter()
    pp.pprint(parse_ini("test.ini"))