from PIL import Image, ImageFont, ImageDraw
import string

def write_string(text):
    #font
    font = ImageFont.truetype("COOPBL.TTF", 200)
    
    #text
    #text = '1'
    width, height = font.getsize(text)
    
    #background color
    image = Image.new('RGB', (width, height), (255, 255, 255))
    
    #rectangle
    #image.paste((255, 255, 255), (10, 20, 100, 50))
    
    #text
    draw = ImageDraw.Draw(image)
    draw.text((0, 0), text, fill=(0,0,0), font=font)
    
    #save
    image.save(text+".png")

def get_percent(text):
    image = Image.open(text+".png")
    width = image.width
    height = image.height
    
    count = 0
    for h in range(0, height):  
        for w in range(0, width):  
            pixel = image.getpixel((w, h))   
            if sum(pixel) == 0:
                count += 1
    return count/width/height

def get_color_str():
    font = ImageFont.truetype("COOPBL.TTF", 200)
    texts = {}
    for text in string.printable:
        if text in ('\t', '\r', '\n', '\x0b', '\x0c'):
            continue
        width, height = font.getsize(text)
        image = Image.new('RGB', (width, height), (255, 255, 255))
        draw = ImageDraw.Draw(image) 
        draw.text((0, 0), text, fill=(0,0,0), font=font)
        count = 0
        for h in range(0, height):  
            for w in range(0, width):  
                pixel = image.getpixel((w, h))   
                if sum(pixel) == 0:
                    count += 1
        percent = count/width/height
        texts[text] = percent
    
    color_str = sorted(texts.items(), key=lambda item: item[1], reverse=False)
    color_str = [key for key, value in color_str]
    return color_str
    
def pic_to_ascii(file, color_str):
    img_name = file.split('.')
    image = Image.open(file).convert('L')
    pix = image.load()
    width, height = image.size
    file = open(img_name[0]+'.txt', mode='w')
    for h in range(height):
        for w in range(width):
            char = color_str[int(int(pix[w,h])*(len(color_str)-1)/255)]
            file.write(char)
        file.write('\n')
    file.close()

pic_to_ascii('test.jpg', get_color_str())
