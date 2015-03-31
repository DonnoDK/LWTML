Lightweight Terminal Media Library
==================================

Lightweight Terminal Media Library, or LWTML for short, is a small C++ library
that makes it easy to output simple graphics to a supported terminal emulator. It also provides non-blocking keyboard input and timing - both useful in soft-realtime interactive applications and games.

But why?
-------
Surely, much more advanced and feature-rich media libraries exist and I can
only wholeheartedly suggest the use of something like SDL or SFML for
interactive media development. However, LWTML was developed primarily as a
personal learning experience, and for fun! I also frequent [/r/unixporn](http://www.reddit.com/r/unixporn) and
[/r/commandline](http://www.reddit.com/r/commandline), and find small quirky command-line tools interesting. I'm also
interested in game-development, and see a terminal emulator as a platform for
presenting very low-fi graphics - only consoles from the 8-bit generation come
close in fidelity.

But what can I use it for?
--------------------------
Game development - small games like packman, pong, tetris, rogue-likes. Old-school demos, generate fractals, simulate Game Of Life, or just rice your desktop with it (the good people on
[/r/unixporn](http://www.reddit.com/r/unixporn) are especially creative in this regard). Here are some examples of
how programs using LWTML might look like:

![Game Of Life demo](http://i.imgur.com/FgeCNWZ.gif)

![Sprite blitting demo](http://i.imgur.com/sMFvrFd.gif)

Note that those are just lame demos I quickly throw together. Also, the refresh rate of the gifs are terrible.

But why not just use ncurses?
-----------------------------
Sure, you can do that - no hurt feelings.

Does it work yet?
-----------------
The state of the library is still pretty much beta: it has only been tested on OS X at the moment, the interface might change, the makefile and install proceedure is crude - so please use it at your own risk. Contributions are welcome - bug reports, feature requests, you name it. Also, if you create something using the library, be sure to shoot me a message as I would be excited to see what you have cooked up.

Ok, so I'm midly intrigued. How do I get started?
-------------------------------------------------
Compile and install the library:
        
        make && sudo make install

Include the LWTML headers and link against LWTML when compiling:

        clang++ <your_program>.cpp -lLWTML -o <your_program>
        
And here is a sample of a program using LWTML:

        #include <LWTML/LWTML.hpp>
        
        int main(int argc, char** argv){
            Renderer renderer;
            Keyboard keyboard;
            Bitmap bitmap(renderer.width(), renderer.height());
            Timer timer;
            while(true){
                timer.update();
                keyboard.update();
                if(keyboard.is_key_down('q'){
                      break;
                }
                for(int y = 0; y < bitmap.height(); y++){
                      for(int x = 0; x < bitmap.width(); x++){
                            /* do some fancy stuff */
                      }
                }
                renderer.blit(&bitmap);
                timer.lock_at_fps(30);
            }
            return 0;
        }
        
This is a rather dull example, but should get you started.
