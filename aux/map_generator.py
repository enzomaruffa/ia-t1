import sys
import os
from random import randint
  
if (len(sys.argv) < 3):
    exit("Missing arguments")
  
lines = int(sys.argv[1])
columns = int(sys.argv[2])
colors = int(sys.argv[3])

if not os.path.isdir('generated_maps'): 
    os.makedirs('generated_maps')

f = open(f"generated_maps/map-{lines}-{columns}-{colors}", "w")
f.write(f"{lines} {columns} {colors}\n")

for i in range(lines):
    line = [str(randint(1, colors)) for j in range(columns)]
    line_str = " ".join(line) + "\n"
    f.write(line_str)

f.close()
