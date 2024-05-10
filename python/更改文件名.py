import os

def change_file(suffix = '.html', directory = os.getcwd()):
    n = len(suffix)
    for file in os.listdir(directory):
        if(file.endswith(suffix)):
            old_file = file
            old_file = os.path.join(directory, old_file)
            file = file[:-n]
            file = file.replace('.', '-')
            new_file = []
            for str in file.split('-'):
                if len(str) == 1 and str.isnumeric():
                    str = '0' + str
                new_file.append(str)
            new_file = '-'.join(new_file)
            new_file += suffix
            os.rename(old_file, new_file)
        
#directory = os.getcwd()
#suffix = '.html'
#change_file()
#change_file('.cpp')
change_file('.go', 'C:\\Users\\HP\\Desktop\\goWebActualCombat\\03')
