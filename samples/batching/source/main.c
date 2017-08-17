#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <3ds.h>
#include <sf2d.h>

/// Exported via GIMP
extern const struct {
  unsigned int 	 width;
  unsigned int 	 height;
  unsigned int 	 bytes_per_pixel;
  unsigned char	 pixel_data[];
} ballsprites_img;

#define MAX_SPRITES   1600

typedef struct {
	float x,y;			// screen co-ordinates
	float dx, dy;		// velocity
	int sx, sy;         // texture coordinates
}Sprite;

static Sprite sprites[MAX_SPRITES];

static size_t numSprites = 256;

static void moveSprites()
{
	for(unsigned int i = 0; i < numSprites; i++)
    {
		sprites[i].x += sprites[i].dx;
		sprites[i].y += sprites[i].dy;

		//check for collision with the screen boundaries
		if(sprites[i].x < 1 || sprites[i].x > (400-32))
			sprites[i].dx = -sprites[i].dx;

		if(sprites[i].y < 1 || sprites[i].y > (240-32))
			sprites[i].dy = -sprites[i].dy;
	}
}

int main()
{
	// Set the random seed based on the time
	srand(time(NULL));

	sf2d_init();
	sf2d_set_clear_color(RGBA8(0x40, 0x40, 0x40, 0xFF));
    consoleInit(GFX_BOTTOM, NULL);

    // Create a sprite batch, this should be done outside the game loop, and created only once.
    // This allocates enough memory (via linearAlloc) to handle MAX_SPRITES sprites.
    sf2d_batch* sprite_batch = sf2d_create_batch(MAX_SPRITES);

    sf2d_texture *tex1 = sf2d_create_texture_mem_RGBA8(ballsprites_img.pixel_data, ballsprites_img.width, ballsprites_img.height, TEXFMT_RGBA8, SF2D_PLACE_RAM);

    int batched_draw = 1;

    // Create the sprites here.
	for(unsigned int i = 0; i < MAX_SPRITES; i++) {
		//random place and speed
		sprites[i].x = rand() % (400 - 32);
		sprites[i].y = rand() % (240 - 32);
		sprites[i].dx = rand() * 4.0f / RAND_MAX - 2.0f;
		sprites[i].dy = rand() * 4.0f / RAND_MAX - 2.0f;
		// Generate texture coordinates via random number
		// 0 -> (0, 0)
		// 1 -> (32, 0)
		// 2 -> (0, 32)
		// 3 -> (32, 32)
		int image = rand() & 3;
		sprites[i].sx = (image % 2) * 32;
		sprites[i].sy = (image / 2) * 32;
	}

	printf("\x1b[7;1HPress Y to switch mode");
	printf("\x1b[8;1HPress Up to increment sprites");
	printf("\x1b[9;1HPress Down to decrement sprites");

	// Main loop
	while (aptMainLoop()) {

		hidScanInput();

		// Respond to user input
		u32 kDown = hidKeysDown();
		if (kDown & KEY_START)
			break; // break in order to return to hbmenu

		u32 kHeld = hidKeysHeld();
		if ((kHeld & KEY_UP) && numSprites < MAX_SPRITES)
			++numSprites;
		else if ((kHeld & KEY_DOWN) && numSprites > 1)
			--numSprites;

        if (kDown & KEY_Y)
		    batched_draw = !batched_draw;

		moveSprites();


		printf("\x1b[1;1HMode:    %s\x1b[K", (batched_draw) ? "Batched" : "Nonbatched");
		printf("\x1b[2;1HSprites: %zu/%u\x1b[K", numSprites, MAX_SPRITES);
		/// TODO sf2d_get_fps seems to be wildly inaccurate, consider removing/improving citra-qt gives an accurate reading.
		printf("\x1b[3;1HFPS:     %6.2f%%\x1b[K", sf2d_get_fps());
        printf("\x1b[4;1HCPU:     %6.2f%%\x1b[K", C3D_GetProcessingTime()*6.0f);
		printf("\x1b[5;1HGPU:     %6.2f%%\x1b[K", C3D_GetDrawingTime()*6.0f);

		// Render the scene, Start rendering.
        sf2d_start_render();
            //  We are drawing on the top screen left eye (3d is disabled).
            sf2d_set_render_screen(GFX_TOP, GFX_LEFT);
            if (batched_draw)
            {
                // Activate batch drawing mode.
                // Between the call of sf2d_start_batch and sf2d_end_batch, you should only draw textures here.
                // Only call functions sf2d_batch_texture* within this section of code.
                // Note that drawing will be super efficient if you group calls with the same texture together.
                // If you switch textures, then whatever calls to batching functions you've made with the previous
                // texture will be immediately drawn.
                // The batch will be drawn onto the screen when sf2d_end_batch is called.
                sf2d_start_batch(sprite_batch);
                    for (unsigned int i = 0; i < numSprites; i++)
                        sf2d_batch_texture_part(tex1, sprites[i].x, sprites[i].y, sprites[i].sx, sprites[i].sy, 32, 32);
                sf2d_end_batch();
            }
            else
            {
                for (unsigned int i = 0; i < numSprites; i++)
                    sf2d_draw_texture_part(tex1, sprites[i].x, sprites[i].y, sprites[i].sx, sprites[i].sy, 32, 32);
            }
        sf2d_end_render();

	}

	sf2d_fini();
	return 0;
}
