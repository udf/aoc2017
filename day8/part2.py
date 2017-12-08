import re
from collections import defaultdict

reg = defaultdict(int)
subt = {
    'inc': '+=',
    'dec': '-=',
    'if': 'if'
}

biggest = 0

with open('input.txt') as file:
    for line in file:
        code = re.sub(r'^(.+)(if.+)$', r'\2:\1', line)
        code = re.sub(r'\b([a-z]+)\b', lambda m: subt.get(m.group(1), 'reg["{}"]').format(m.group(1)), code)
        exec(code)
        biggest = max(biggest, reg[re.findall(r'^(\S+)', line)[0]])

print(biggest)