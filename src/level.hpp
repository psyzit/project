#ifndef LEVEL_H
#define LEVEL_H
#include <dviglo/graphics/sprite_batch.hpp>
#include <third_party/pugixml/src/pugixml.hpp>

using namespace dviglo;
using namespace std;
using namespace glm;
class level
{
    pugi::xml_document levelFile_;
    Texture* texturetile_;
public:
    void load(string filepath);
    void draw(SpriteBatch* sprite_batch);

private:
    Rect calc_tile_uv(u32 value);

    int width, height;
    int tilewidth, tileheight;
    int imagewidth, imageheight;
    int tilecount;
};

#endif // LEVEL_H
