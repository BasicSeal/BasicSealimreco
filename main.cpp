#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "lcy_Obamna.h"
#include <random>
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
float pi = 3.1415926536;

class DataSource {
public:
    const char path[9] = "data.png";
    SDL_Rect scale = {
        0, 0, 100, 100
    };
};


int main(int argc, char *argv[]) {
    time_t start, end;
    time(&start);

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("Blue Rectangle", 1800, 1200, SDL_WINDOW_RESIZABLE);

    // Create a renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, nullptr);
    SDL_RenderClear(renderer);
    //

    const int geschwindigkeit = 0; //antipropotional zum detailbei groesser8 ist es unnuetz
    //

    ofstream dbf("debugfile.csv");

    DataSource p;
    SDL_Surface *source_img = IMG_Load("Ob100.png"); // source_imgama
    if (
        SDL_LockSurface(source_img)) { cout << "Source image locked  "; }
    SDL_Surface *data_source = IMG_Load(p.path);
    if (SDL_LockSurface(data_source)) { cout << "Data image locked \n"; }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, data_source);
    SDL_Texture *source_imgt = SDL_CreateTextureFromSurface(renderer, source_img); // source_imgamatexture

    SDL_FRect drect = {(float) p.scale.w * 2, 0, (float) p.scale.w * 2, (float) p.scale.h * 2};
    SDL_RenderTexture(renderer, source_imgt, nullptr, &drect);
    SDL_FRect frect = {0, 0, (float) p.scale.w * 2, (float) p.scale.h * 2};
    SDL_RenderTexture(renderer, texture, nullptr, &frect);
    SDL_RenderPresent(renderer);

    bool banned_pixel_list[(int) p.scale.w][(int) p.scale.h]; //bl:ban liste
    int pixel_index[2];
    SDL_Color pixels[(int) p.scale.w][(int) p.scale.h];
    for (int (source_x) = 0; (source_x) < (p.scale.w); (source_x)++) {
        for (int (source_y) = 0; (source_y) < (p.scale.h); (source_y)++) {
            //
            //
            for (int (data_x) = 0; (data_x) < (p.scale.w); (data_x)++) {
                for (int (data_y) = 0; (data_y) < (p.scale.h); (data_y)++) {
                    if (banned_pixel_list[(data_x)][(data_y)] == true) {
                        data_y++;
                    }
                    ////
                    ////r
                    ////
                    ///
                    /// BITTE NICHT JEDESMAL GETPIXELCOLOUR ABRUFEN EINFACH ZWEI ARRYS MACHEN ; DANKEEE!!!!
                    ///  Verfahren Get Pixel Colour: greift auf Datenplatz im Surface zu
                    ///
                    ///
                    ///
                    ///

                    if (pixel_distance(source_x, source_y, data_x, data_y, source_img, data_source) <= 30 *
                        geschwindigkeit) {
                        pixels[source_x][source_y] = GetPixelColor(data_source, (data_x), (data_y));
                        pixel_index[0] = (data_x);
                        pixel_index[1] = (data_y);

                        source_y++;
                    } else if (pixel_distance(source_x, source_y, data_x, data_y, source_img, data_source) <
                               pixel_pythagoras(pixels[source_x][source_y],
                                                GetPixelColor(source_img, (source_x), (source_y)))) {
                        pixels[source_x][source_y] = GetPixelColor(data_source, (data_x), (data_y));
                        pixel_index[0] = (data_x);
                        pixel_index[1] = (data_y);
                    }

                    ////
                } //(data_y*ks)
            } //(data_x*ks)
            banned_pixel_list[pixel_index[0]][pixel_index[1]] = true;

            cout << source_x << "/" << p.scale.w << " " << source_y << "/" << p.scale.h << endl;
        } //(source_y*ks)
    } //(source_x*ks)

    SDL_DestroySurface(data_source);
    SDL_DestroySurface(source_img);
    SDL_RenderTexture(renderer, source_imgt, nullptr, &drect);
    SDL_RenderTexture(renderer, texture, nullptr, &frect);
    SDL_RenderPresent(renderer);
    SDL_Delay(500);
    dbf.close();
    // Wait for 5 seconds
    //SDL_Delay(500);

    SDL_Surface *surface =
            SDL_CreateSurfaceFrom(p.scale.w, p.scale.h, SDL_PIXELFORMAT_RGBA8888, &pixels, 4 * p.scale.w);
    SDL_RenderClear(renderer);
    IMG_SavePNG(surface, "result.png");
    SDL_Texture *text = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);
    SDL_FRect crect = {0, (float) p.scale.h * 2, (float) p.scale.w * 2, (float) p.scale.h * 2};
    SDL_RenderTexture(renderer, text, nullptr, &crect);

    SDL_RenderTexture(renderer, source_imgt, nullptr, &drect);
    SDL_RenderTexture(renderer, texture, nullptr, &frect);

    SDL_RenderPresent(renderer);
    SDL_Delay(2000);

    // Destroy the renderer and window
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    // Quit SDL
    SDL_Quit();
    time(&end);
    auto time_taken = static_cast<double>(end - start);

    cout << "Time taken by program is : " << fixed
            << time_taken << setprecision(5);
    cout << " sec " << endl;
    return (0);
}
