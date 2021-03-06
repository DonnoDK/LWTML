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

Note that those are just lame demos I quickly threw together. Also, the refresh rate of the gifs are terrible.

But why not just use ncurses?
-----------------------------
Sure, you can do that - no hurt feelings. I do aim to make it easier to get started using my library compared to ncurses. Ncurses is great, but it has gained some "weight" over the years, meaning a lot of boilerplate code is necessary to get started using it.

Does it work yet?
-----------------
The state of the library is still pretty much beta: it has only been tested on OS X at the moment, the interface might change, the makefile and install proceedure is crude - so please use it at your own risk. Contributions are welcome - bug reports, feature requests, you name it. Also, if you create something using the library, be sure to shoot me a message as I would be excited to see what you have cooked up.

Ok, so I'm midly intrigued. How do I get started?
-------------------------------------------------
Compile and install the library:
        
        make && sudo make install
        
Do note that the last step requires root access and installs headers to */usr/local/include* and the library to */usr/local/lib*. If you rather not have that happen, you can make gcc/clang search for the library and headers elsewhere using:

        clang++ ... -L<path_to_lib> -I<path_to_headers> -lLWTML -o ...

If you did *make install* you just include the LWTML headers and link against LWTML when compiling:

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

So, what is supported? Where does it work?
------------------------------------------
At the moment it's only tested on and made to work on OS X, but making it work on GNU/Linux is simply a matter of using the correct compile flags, which I'll get to in the near future. It will _probably_ never support Windows. I don't own any version of Windows, so I can't really develop for it without too much hassle.

Are there any caveats or known bugs?
-----------------------------------
Know bugs, a few yes, and there are probably a whole slew of bugs that I don't know of yet.

Known bugs:
- The iTerm2 terminal emulator for OSX seems to be significantly slower at refreshing the display compared to urxvt under X11. You will probably get something near 10-15fps in iTerm2 compared to ~200fps in urxvt. I'm not sure this is something I have control over, and I assume this has to do with the implementation of iTerm2.
- There is currently an interface for rendering normal ascii text. It does not work properly in iTerm2. 

Planned enhancements:
----------------------
- Proper namespacing. Considered candidates: LWTML::, lwtml:: or lw::.
- Convinient classes such as Rect, Point, etc.
- Proper error handling.
- Double buffering for the renderer. As of now, blittet bitmaps are just spilled directly into the terminal.
- Loading of PNGs to internal bitmaps.
- Persistent valuestore, similar to Unity3d's PlayerPrefs.
- ...
