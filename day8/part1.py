import re

_old_locals = set(locals())
id = 0

with open('input.txt') as _f:
    for _l in _f:
        _err = True
        while _err:
            try:
                exec(re.sub(r"^(.+)(if.+)$", r"\2:\1", _l).replace('inc', '+=').replace('dec', '-='))
                _err = False
            except NameError as _e:
                exec(re.findall("name '(\w+)' is not defined", str(_e))[0] + ' = 0')

print(max(eval(reg) for reg in set(locals()) - _old_locals if not reg.startswith('_')))