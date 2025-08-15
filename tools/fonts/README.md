### Font Conv

Converts ttf font to bitmap file and font metadata (bitmap.png + font.txt)

Font metadata contains information about position of each character in the bitmap. Each
line of metadata (font.txt) file consists of space separated char, x0, y0, x1, y1, xoffset,
yoffset, and xadvance.

#### Sample usage
```
bin/font-conv font-file.ttf
```

**Note:** `font-conv` command will be located under `{project_root}/bin` directory.
