## SF2DLIB

Simple and Fast 2D library for the Nintendo 3DS (using [citro3d] and [ctrulib])

### Overview

sf2dlib is now a simple abstraction layer  over [citro3d] with extra functions over citro3d to make displaying simple shapes and 2d sprites easy. As long as you are not drawing millions of shapes/sprites, this library should be able to fit your use case.  If you are seeking to squeeze all of the power out of your 3ds and have full control over the GPU then sf2dlib will probably not fit your use case and you should use [citro3d] instead.  Note that there is a small overhead in using sf2dlib over citro3d, but it is negligible as long as you aren't rendering too much in a single frame.

### Special Note for new users.
If you are a new user to 3ds homebrew or starting new code, you would be much better served trying out [nop90's SDL port](https://github.com/nop90/SDL-3DS).  There are a lot of reasons to use SDL over this library, SDL has [tutorials], there are a ton of [examples], and you get the ability to take your work off the 3ds or test it off the 3ds.

### Changes

These changes in this fork are to make the code more consistent with [citro3d] while also adding new functions and improvements. See the [sample] to see the new code flow.

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
[tutorials]: <https://www.google.com/search?q=SDL+tutorials&oq=SDL+tutorials&aqs=chrome..69i57j0l5.8503j0j7&sourceid=chrome&ie=UTF-8>
[examples]: <https://libregamewiki.org/SDL_games>
