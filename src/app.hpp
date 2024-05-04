#pragma once

#include <dviglo/graphics/sprite_batch.hpp>
#include <dviglo/main/application.hpp>

using namespace dviglo;
using namespace std;
using namespace glm;

class App : public Application
{
    Texture* texture_;
    unique_ptr<SpriteBatch> sprite_batch_;
    unique_ptr<SpriteFont> r_20_font_;
    unique_ptr<SpriteFont> my_font_;

public:
    App(const vector<StrUtf8>& args);

    void setup() override;
    void start() override;
    bool handle_sdl_event(const SDL_Event& event) override;
    void update(u64 ns) override;
    void draw() override;

    void on_key(const SDL_KeyboardEvent& event_data);
};

