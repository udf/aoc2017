import re
from collections import defaultdict

reg = defaultdict(int)
subt = {
    'inc': '+=',
    'dec': '-=',
    'if': 'if'
}

with open('input.txt') as file:
    for line in file:
        line = re.sub(r'^(.+)(if.+)$', r'\2:\1', line)
        line = re.sub(r'\b([a-z]+)\b', lambda m: subt.get(m.group(1), 'reg["{}"]').format(m.group(1)), line)
        exec(line)

print(max(v for k, v in reg.items()))