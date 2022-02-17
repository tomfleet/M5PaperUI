import sys
from PIL import Image, ImageOps
import os.path
import fs #import list
from fs import open_fs

from pathlib import Path

GRAYSCALE_MAP = [0 for i in range(256)]

x = -1
for i in range(0, 256):
    if i % 16 == 0:
        x += 1
    GRAYSCALE_MAP[i] = 15 - x


def getBitmap(img):
    buffer = []
    byte = 0
    img = img.convert('L')
    for y in range(img.height):
        for x in range(0, img.width, 2):
            byte = GRAYSCALE_MAP[img.getpixel((x, y))] << 4
            if x + 1 < img.width:
                byte |= GRAYSCALE_MAP[img.getpixel((x + 1, y))]
            buffer.append(byte)
    return bytes(buffer)


def main():

  this_dir = os.path.dirname(__file__)
  src_dir = os.path.join(this_dir, "..", "..", "images")
  print(src_dir)
  full_path=src_dir
  print(str(Path(full_path).parents[4]))
  src_dir=str(Path(full_path).parents[4])+"\images"
  print(src_dir)
  dstf = open('image_resources.h', 'w+')
  dstf.write("#pragma once\n")

  with open_fs(src_dir) as fs:
      print(src_dir)
      print(fs)
      
      for f in fs.walk.files():
            print(src_dir+f)
            tmp=src_dir+f
            print(tmp)
            tmp2 = tmp.replace("/","\\")
            print(tmp2)
            final = Image.open(tmp2)
            ident = "_".join(os.path.basename(tmp2).split(".")[:-1]).upper()
            print(ident)
            dstf.write("\nconst unsigned char %s[] PROGMEM = {\n" % (ident))
            buffer = getBitmap(final)
            cnt = 0
            for byte in buffer:
              cnt += 1
              if cnt == 1:
                dstf.write("    ")
                dstf.write('0x%02X' % byte)
              elif cnt == 12:
                cnt = 0
                dstf.write(', 0x%02X,' % byte)
                dstf.write('\n')
              else:
                dstf.write(', 0x%02X' % byte)
            dstf.write('};\n')



if __name__ == "__main__":
    main()
