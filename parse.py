import re
from collections import defaultdict
import glob
cm = defaultdict(list)
sm = defaultdict(list)
for file in glob.glob("./*/*cpp"):
    f = open(file, 'r')
    text = f.read()
    res = set(re.findall("struct\s+(\w+)\s?\{", text))
    
    for tag in res:
        sm[tag].append(file)


    res = set(re.findall("class\s+(\w+)\s?\{", text))


print("# The data structure")
print("")
for name, candi in sm.items():
    print(f"## {name} {len(candi)}")
    for c in candi:
        # print (c) [词向量 (Word Embedding)](./word_embedding/)
        print(f"- [{c.split('/')[-1]}]({c})")
    print("")
