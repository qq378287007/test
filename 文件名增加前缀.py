#设置输出编码为utf-8
import io
import sys
sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8')

import os
def add_prefix(prefix = '', suffix='.html', directory = os.getcwd()):
    n = len(suffix)
    for old_file in os.listdir(directory):
        if(old_file.endswith(suffix)):
            new_file = os.path.join(directory, prefix + old_file)
            #os.rename(old_file, new_file)
            print(new_file)

add_prefix('中文-')