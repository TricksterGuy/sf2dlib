#include "sf2d.h"
#include <stdlib.h>
#include <math.h>

static sf2d_batch* current_batch = NULL;

sf2d_batch* sf2d_create_batch(int size)
{
    sf2d_batch* rt = calloc(1, sizeof(*rt));
    // 2 triangles each with 3 vertices.
    rt->size = size * 6 * sizeof(sf2d_vertex_pos_tex);
    rt->vertices = linearAlloc(rt->size);
    return rt;
}

void sf2d_reset_batch(sf2d_batch* batch)
{
   batch->index = 0;
   batch->start_index = 0;
   batch->bound = NULL;
}

void sf2d_start_batch(sf2d_batch* batch)
{
    if (current_batch != NULL) return;

	sf2d_reset_batch(batch);
	current_batch = batch;
}

void sf2d_batch_texture(sf2d_texture* texture, int x, int y)
{
    if (current_batch == NULL) return;

    // Out of space
    if (current_batch->index >= current_batch->size) return;

    if (current_batch->bound != texture)
    {
        if (current_batch->index - current_batch->start_index > 0)
            sf2d_flush_batch(current_batch);
        sf2d_bind_texture(texture, GPU_TEXUNIT0);
        current_batch->bound = texture;
    }

	sf2d_vertex_pos_tex* vertices = current_batch->vertices + current_batch->index;

	int w = texture->width;
	int h = texture->height;

	vertices[0].position = (sf2d_vector_3f){(float)x,   (float)y,   SF2D_DEFAULT_DEPTH};
	vertices[1].position = (sf2d_vector_3f){(float)x,   (float)y+h, SF2D_DEFAULT_DEPTH};
	vertices[2].position = (sf2d_vector_3f){(float)x+w, (float)y,   SF2D_DEFAULT_DEPTH};

	vertices[3].position = (sf2d_vector_3f){(float)x+w, (float)y,   SF2D_DEFAULT_DEPTH};
	vertices[4].position = (sf2d_vector_3f){(float)x,   (float)y+h, SF2D_DEFAULT_DEPTH};
	vertices[5].position = (sf2d_vector_3f){(float)x+w, (float)y+h, SF2D_DEFAULT_DEPTH};

	float u = texture->width/(float)texture->tex.width;
	float v = texture->height/(float)texture->tex.height;

	vertices[0].texcoord = (sf2d_vector_2f){0.0f, 0.0f};
	vertices[1].texcoord = (sf2d_vector_2f){0.0f,    v};
	vertices[2].texcoord = (sf2d_vector_2f){   u, 0.0f};
	vertices[3].texcoord = (sf2d_vector_2f){   u, 0.0f};
	vertices[4].texcoord = (sf2d_vector_2f){0.0f,    v};
	vertices[5].texcoord = (sf2d_vector_2f){   u,    v};

	current_batch->index += 6;
}

void sf2d_batch_texture_part(sf2d_texture* texture, int x, int y, int tex_x, int tex_y, int tex_w, int tex_h)
{
    if (current_batch == NULL) return;

    // Out of space
    if (current_batch->index >= current_batch->size) return;

    if (current_batch->bound != texture)
    {
        if (current_batch->index - current_batch->start_index > 0)
            sf2d_flush_batch(current_batch);
        sf2d_bind_texture(texture, GPU_TEXUNIT0);
        current_batch->bound = texture;
        current_batch->start_index = current_batch->index;
    }

	sf2d_vertex_pos_tex *vertices = current_batch->vertices + current_batch->index;

	vertices[0].position = (sf2d_vector_3f){(float)x,       (float)y,       SF2D_DEFAULT_DEPTH};
	vertices[1].position = (sf2d_vector_3f){(float)x,       (float)y+tex_h, SF2D_DEFAULT_DEPTH};
	vertices[2].position = (sf2d_vector_3f){(float)x+tex_w, (float)y,       SF2D_DEFAULT_DEPTH};

	vertices[3].position = (sf2d_vector_3f){(float)x+tex_w, (float)y,       SF2D_DEFAULT_DEPTH};
	vertices[4].position = (sf2d_vector_3f){(float)x,       (float)y+tex_h, SF2D_DEFAULT_DEPTH};
	vertices[5].position = (sf2d_vector_3f){(float)x+tex_w, (float)y+tex_h, SF2D_DEFAULT_DEPTH};

	float u0 = tex_x/(float)texture->tex.width;
	float v0 = tex_y/(float)texture->tex.height;
	float u1 = (tex_x+tex_w)/(float)texture->tex.width;
	float v1 = (tex_y+tex_h)/(float)texture->tex.height;

	vertices[0].texcoord = (sf2d_vector_2f){u0, v0};
	vertices[1].texcoord = (sf2d_vector_2f){u0, v1};
	vertices[2].texcoord = (sf2d_vector_2f){u1, v0};
	vertices[3].texcoord = (sf2d_vector_2f){u1, v0};
	vertices[4].texcoord = (sf2d_vector_2f){u0, v1};
	vertices[5].texcoord = (sf2d_vector_2f){u1, v1};

	current_batch->index += 6;
}

void sf2d_end_batch()
{
    if (current_batch == NULL) return;

    if (current_batch->index - current_batch->start_index > 0)
        sf2d_flush_batch(current_batch);

    current_batch = NULL;
}

void sf2d_flush_batch()
{
    if (current_batch == NULL) return;

	C3D_AttrInfo* attrInfo = C3D_GetAttrInfo();
	AttrInfo_Init(attrInfo);
	AttrInfo_AddLoader(attrInfo, 0, GPU_FLOAT, 3);
	AttrInfo_AddLoader(attrInfo, 1, GPU_FLOAT, 2);

	C3D_BufInfo* bufInfo = C3D_GetBufInfo();
	BufInfo_Init(bufInfo);
	BufInfo_Add(bufInfo, current_batch->vertices, sizeof(sf2d_vertex_pos_tex), 2, 0x10);

	C3D_DrawArrays(GPU_TRIANGLES, current_batch->start_index, current_batch->index - current_batch->start_index);

    current_batch->start_index = current_batch->index;
}
