### Font Conv

Converts ttf font to bitmap file and font metadata (bitmap.png + font.txt)

Font metadata contains information about position of each character in the bitmap. First line
of the metadata file (font.txt) contains width, height and pixel height (font size) of the bitmap font, 
after that each line consists of space separated char, x, y, width, height, xoffset, yoffset, and xadvance.

yoffset is the distance of the top of character to the base line of the char (with y axis pointing downwards).

#### Sample usage
```
bin/font-conv font-file.ttf
```

**Note:** `font-conv` command will be located under `{project_root}/bin` directory.
