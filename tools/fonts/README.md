### Font Conv

Converts ttf font to bitmap file and font metadata (bitmap.png + font.txt)

Font metadata contains information about position of each character in the bitmap. First line
of the metadata file (font.txt) contains width and height of the bitmap font, after that each
line consists of space separated char, x0, y0, x1, y1, xoffset, yoffset, and xadvance.

#### Sample usage
```
bin/font-conv font-file.ttf
```

**Note:** `font-conv` command will be located under `{project_root}/bin` directory.
