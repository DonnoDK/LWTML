#ifndef RENDERER_H
#define RENDERER_H
#include "IService.hpp"
class Bitmap;
class Text;
class Renderer : public IService{
private:
    unsigned int _width;
    unsigned int _height;
    void setPixel(unsigned int x, unsigned int y, unsigned char color) const;
    void clearScreen() const;
    void hideCursor() const;
    void showCursor() const;
public:
    Renderer(unsigned int width, unsigned int height);
    Renderer();
    ~Renderer();
    void blit(Bitmap* bitmap) const;
    void renderText(Text* text, unsigned int x, unsigned int y) const;
    void clearBuffer(unsigned char color) const;
    unsigned int width() const;
    unsigned int height() const;
    Bitmap* standardBitmap() const;
    unsigned int type() const;
};
#endif
