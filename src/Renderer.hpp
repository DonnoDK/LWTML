#ifndef RENDERER_H
#define RENDERER_H
class Bitmap;
class Renderer{
private:
    unsigned int _width;
    unsigned int _height;
    void setPixel(unsigned int x, unsigned int y, unsigned char color) const;
    void clearScreen() const;
    void hideCursor() const;
public:
    Renderer(unsigned int width, unsigned int height);
    void blit(Bitmap* bitmap) const;
    void clearBuffer(unsigned char color) const;
    unsigned int width() const;
    unsigned int height() const;
    Bitmap* standardBitmap() const;
};
#endif
