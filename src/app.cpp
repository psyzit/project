#include "app.hpp"
#include "level.hpp"

#include <dviglo/gl_utils/texture_cache.hpp>
#include <dviglo/fs/fs_base.hpp>
#include <dviglo/main/engine_params.hpp>
#include <dviglo/main/os_window.hpp>
#include <third_party/pugixml/src/pugixml.hpp>

#include <format>
#include <iostream>

using namespace glm;


App::App(const vector<StrUtf8>& args)
    : Application(args)
{
}


void App::setup()
{
    engine_params::log_path = get_pref_path("dviglo2d", "samples") + "hello.log";
    engine_params::window_size = ivec2(960, 640);
    engine_params::vsync = -1;
}
level level1;
void App::start()
{
    StrUtf8 base_path = get_base_path();
    DV_LOG->write_info(format("Командная строка: {}", join(args(), " ")));
    DV_LOG->write_info(format("Папка программы: {}", base_path));


    texture_ = DV_TEXTURE_CACHE->get(base_path + "game_data/textures/tile.png");
    sprite_batch_ = make_unique<SpriteBatch>();
    r_20_font_ = make_unique<SpriteFont>(base_path + "game_data/fonts/ubuntu-r_20_simple.fnt");
    my_font_ = make_unique<SpriteFont>(base_path + "game_data/fonts/my_font.fnt");

    level1.load("game_data/tilemap/tilemap3.xml");
}

bool App::handle_sdl_event(const SDL_Event& event)
{
    if (Application::handle_sdl_event(event)) // Реагируем на закрытие приложения
        return true;
    switch (event.type)
    {
    case SDL_EVENT_KEY_DOWN:
    case SDL_EVENT_KEY_UP:
        on_key(event.key);
        return true;
    default:
        return false;
    }

}

void App::on_key(const SDL_KeyboardEvent& event_data)
{
    if (event_data.type == SDL_EVENT_KEY_DOWN && event_data.repeat == false
        && event_data.keysym.scancode == SDL_SCANCODE_ESCAPE)
    {
        should_exit_ = true;
    }

}

void App::update(u64 ns)
{

}


void App::draw()
{
    ivec2 screen_size;
    SDL_GetWindowSizeInPixels(DV_OS_WINDOW->window(), &screen_size.x, &screen_size.y);

    glClearColor(1.0f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);


    sprite_batch_->prepare_ogl(true);
    level1.draw(sprite_batch_.get());

    sprite_batch_->flush();
}
