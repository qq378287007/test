from PIL import Image
import argparse

#命令行输入参数处理
parser = argparse.ArgumentParser()

parser.add_argument('file')     #输入文件
parser.add_argument('-o', '--output')   #输出文件
parser.add_argument('--width', type = int, default = 80) #输出字符画宽
parser.add_argument('--height', type = int, default = 80) #输出字符画高

#获取参数
args = parser.parse_args()

IMG = args.file
WIDTH = args.width
HEIGHT = args.height
OUTPUT = args.output

ascii_char = list("$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\|()1{}[]?-_+~<>i!lI;:,\"^`'. ")
ascii_len = len(ascii_char)

#将256灰度映射到70个字符上
def get_char(r, b, g, alpha = 256):
    if alpha == 0:   
        return ' '
        
    #灰度值公式
    gray = 0.2126 * r + 0.7152 * g + 0.0722 * b  
    return ascii_char[int(round(gray*(ascii_len-1)/255))]

if __name__ == '__main__':
    #载入IMG的文件
    im = Image.open(IMG) 
    
    #WIDTH = im.width
    #HEIGHT = im.height
    
    #重置或默认值       
    im = im.resize((WIDTH, HEIGHT), Image.NEAREST)
    

    txt = ""
    for i in range(HEIGHT):
        for j in range(WIDTH):
            #返回指定位置的像素
            txt += get_char(*im.getpixel((j,i)))   
        txt += '\n'

    #字符画输出到文件
    if OUTPUT:
        with open(OUTPUT,'w') as f:
            f.write(txt)
    else:
        with open("output.txt",'w') as f:
            f.write(txt)