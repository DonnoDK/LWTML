#ifndef RENDERER_H
#define RENDERER_H
class Bitmap;
class Text;
class Renderer{
private:
    unsigned int _width;
    unsigned int _height;
    void set_pixel(unsigned int x, unsigned int y, unsigned char color) const;
    void clear_screen() const;
    unsigned char* _symbol_buffer;
    unsigned char* _bg_color_buffer;
    unsigned char* _fg_color_buffer;
    void initialize_buffers();
public:
    Renderer(unsigned int width, unsigned int height);
    Renderer();
    ~Renderer();
    void blit(Bitmap* bitmap) const;
    void render_text(Text* text, unsigned int x, unsigned int y) const;
    void clear_buffer(unsigned char color) const;
    void present_buffer() const;
    unsigned int width() const;
    unsigned int height() const;
    Bitmap* standard_bitmap() const;
};
#endif
