# LOG_([^\(]*)\(LOG_([^\)]*)\) << (.+);


import os
import glob
import re

def replace_logs(content):
    res = []
    changed = False
    for line in content.splitlines():
        a = re.search(r'LOG_([^\(]*)\(LOG_([^\)]*)\) << (.+);', line)
        if a is not None:
            other = ', '.join(x.strip() for x in a.group(3).split('<<'))
            temp = "LOG_%s(LOG_%s, %s);" % (a.group(1), a.group(2), other)
            new_line = line.replace(a.group(0), temp)
            res.append(new_line)
            changed = True
        else:
            res.append(line)
        
    return changed, '\n'.join(res)

path = '/Users/fernando/dev/kth/kth/'
result = [y for x in os.walk(path) for y in glob.glob(os.path.join(x[0], '*.cpp'))]
# result.extend([y for x in os.walk(path) for y in glob.glob(os.path.join(x[0], '*.hpp'))])
# print(result)

for f in result:
    with open(f, 'r') as content_file:
        content = content_file.read()
    new_content = replace_logs(content)
    if new_content[0]:
        # print(new_content[1])
        # break
        with open(f, 'w') as content_file:
            content_file.write(new_content[1])
        print("%s changed" % (f,))

