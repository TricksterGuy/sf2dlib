## SF2DLIB


Simple and Fast 2D library for the Nintendo 3DS (using [citro3d] and [ctrulib])

The main changes in this [sf2dlib] fork are as follows
| Function                         | Change                                                       |
|----------------------------------|--------------------------------------------------------------|
| `sf2d_start_render()`            | Newly added, use instead of `sf2d_start_frame`               |
| `sf2d_start_frame(screen, side)` | Removed, `sf2d_set_render_screen(screen, side)` replaces it. |
| `sf2d_end_frame()`               | Removed, `sf2d_end_render()` replaces it.                    |
| `sf2d_swapbuffers()`             | Removed, `sf2d_end_render()` replaces it.                    |


These changes are to make the code more consistent with [citro3d].

See the [sample] to see the new code flow


### Documentation (original)
http://xerpi.github.io/sf2dlib/html/sf2d_8h.html

[//]: # (These are reference links used in the body of this note and get stripped out when the markdown processor does its job. There is no need to format nicely because it shouldn't be seen. Thanks SO - http://stackoverflow.com/questions/4823468/store-comments-in-markdown-syntax)


[citro3d]: <https://github.com/fincs/citro3d>
[ctrulib]: <https://github.com/smealum/ctrulib>
[sample]: <https://github.com/TricksterGuy/sf2dlib/blob/master/sample/source/main.c>
[sf2dlib]: <https://github.com/xerpi/sf2dlib>
