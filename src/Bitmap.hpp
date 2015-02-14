#ifndef BITMAP_HPP
#define BITMAP_HPP
class Bitmap{
private:
    unsigned int _width;
    unsigned int _height;
    unsigned char _colorkey;
    unsigned char* _pixels;
public:
    Bitmap(unsigned int width, unsigned int height, unsigned char colorkey);
    ~Bitmap();
    void setPixel(unsigned int x, unsigned int y, unsigned char color);
    void clear(unsigned char color);
    unsigned char pixel(unsigned int x, unsigned int y) const;
    unsigned char colorkey() const;
    void blit(Bitmap* bitmap, unsigned int xOffset, unsigned int yOffset);
    unsigned int height() const;
    unsigned int width() const;
};
#endif
