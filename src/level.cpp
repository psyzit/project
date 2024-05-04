#include "level.hpp"
#include <dviglo/gl_utils/texture_cache.hpp>
#include <dviglo/fs/fs_base.hpp>

#include <format>
#include <iostream>


void level::load(string filepath)
{

    pugi::xml_parse_result result = levelFile_.load_file(filepath.c_str(),
                                                        pugi::parse_default|pugi::parse_declaration);
    if (!result)
    {
        std::cout << "Parse error: " << result.description() << ", character pos= " << result.offset;
    }


    string imagepath = levelFile_.child("map").child("tileset").child("image").attribute("source").as_string();

    imagewidth = levelFile_.child("map").child("tileset").child("image").attribute("width").as_int();
    imageheight = levelFile_.child("map").child("tileset").child("image").attribute("height").as_int();
    StrUtf8 base_path = get_base_path();
    texturetile_ = DV_TEXTURE_CACHE->get(base_path + imagepath);

}
void level::draw(SpriteBatch* sprite_batch)
{
    pugi::xml_node map = levelFile_.child("map");

    width = map.attribute("width").as_int();
    height = map.attribute("height").as_int();
    tilewidth = map.attribute("tilewidth").as_int();
    tileheight = map.attribute("tileheight").as_int();
    tilecount = map.child("tileset").attribute("tilecount").as_int();

    pugi::xml_node tile = map.child("layer").child("data").child("tile");
    int x = 0;
    int y = 0;
    int value;
    while(tile != NULL) {
        value = tile.attribute("gid").as_int();
        if (value != 0) {
            Rect tile_uv = calc_tile_uv(value);
            sprite_batch->draw_sprite(texturetile_, {x * tilewidth, y * tileheight}, &tile_uv, 0xFFFFFFFF, 0);
        }

        tile = tile.next_sibling("tile");
        x++;
        if (x >= width)
        {
            x = 0;
            y++;
            if(y >= height)
                y = 0;
        }
    }
}

Rect level::calc_tile_uv(u32 value)
{
    value--;
    assert(value < tilecount);

    i32 rows = imagewidth / tilewidth;
    i32 index_y = value / rows; // Строка
    i32 index_x = value - index_y * rows; // Столбец

    f32 u = index_x * tilewidth; // Левая граница костяшки
    f32 v = index_y * tileheight; // Верхняя граница костяшки

    return {{u, v}, {tilewidth, tileheight}}; // Правая и нижняя граница включаются в Rect
}
