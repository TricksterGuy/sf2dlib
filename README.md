## SF2DLIB

Simple and Fast 2D library for the Nintendo 3DS (using [citro3d] and [ctrulib])

These changes in this fork are to make the code more consistent with [citro3d] while also add new functions and improvements. See the [sample] to see the new code flow.

To enumerate the list of changes in this [sf2dlib] fork:

### API Changes
| Function                         | Change                                                       |
|----------------------------------|--------------------------------------------------------------|
| `sf2d_start_render()`            | Newly added, use instead of `sf2d_start_frame`.              |
| `sf2d_start_frame(screen, side)` | Removed, `sf2d_set_render_screen(screen, side)` replaces it. |
| `sf2d_end_frame()`               | Removed, `sf2d_end_render()` replaces it.                    |
| `sf2d_swapbuffers()`             | Removed, `sf2d_end_render()` replaces it.                    |
| `sf2d_draw_quad_uv_current(...)` | Removed, use Batch functions instead.                        |
| `sf2d_draw_quad_uv(...)`         | Removed, use Batch functions isntead.                        |
| `sf2d_draw_quad_uv_blend(...)`   | Removed, use Batch functions isntead.                        |

### New Features
* Support for Sprite Batching to improve efficiency of drawing many sprites using the same texture see [Batching Sample].
* Ability to set framerate limit via `sf2d_set_fps(float fps)`

### Documentation (original)
http://xerpi.github.io/sf2dlib/html/sf2d_8h.html

[//]: # (These are reference links used in the body of this note and get stripped out when the markdown processor does its job. There is no need to format nicely because it shouldn't be seen. Thanks SO - http://stackoverflow.com/questions/4823468/store-comments-in-markdown-syntax)

[citro3d]: <https://github.com/fincs/citro3d>
[ctrulib]: <https://github.com/smealum/ctrulib>
[sample]: <https://github.com/TricksterGuy/sf2dlib/blob/master/sample/source/main.c>
[Batching Sample]: <https://github.com/TricksterGuy/sf2dlib/tree/master/samples/batching>
[sf2dlib]: <https://github.com/xerpi/sf2dlib>
