import chardet
def get_file_encoding(file_path):
    with open(file_path, 'rb') as f:
        result = chardet.detect(f.read())
    return result['encoding']

import codecs
def change_file_code(src_file, src_code, des_file, des_code):
    with codecs.open(src_file, 'r', src_code) as f1, codecs.open(des_file, 'w', des_code) as f2:
        content = f1.read()
        f2.write(content)

def change_file_code(src_file, des_file):
    with codecs.open(src_file, 'r', 'utf-8-sig') as f1, codecs.open(des_file, 'w', 'utf-8') as f2:
        content = f1.read()
        content = content.encode('utf-8').decode('utf-8-sig')
        f2.write(content)

#print(get_file_encoding('01.2-1.html'))
#print(get_file_encoding('08.3-1.html'))
#change_file_code('original_file.txt', 'gb2312', 'target_file.txt', 'utf-8')

import os

for file in os.listdir(os.getcwd()):
    if file.endswith('.cpp') and get_file_encoding(file) == 'UTF-8-SIG':
        change_file_code(file, 'C:\\Users\\HP\\Desktop\\test\\dir\\'+file)

def addZero(suffix):
    for file in os.listdir(os.getcwd()):
        new_file = []
        for str in file.split('.'):
            if len(str) == 1 and str.isnumeric():
                new_file.append('0' + str)
            else:
                new_file.append(str)
        new_file = '.'.join(new_file)
        if(new_file.endswith(suffix)):
            os.rename(file, new_file)
        
def addPrefix(prefix):
    for file in os.listdir(os.getcwd()):
        if(file.endswith('.html')):
            os.rename(file, prefix+file)
            
#addPrefix('appendix-')
#addZero('.html')

