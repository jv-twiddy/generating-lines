* goals
- first learn c++ again
  - hello world
  - some data structures 
- learn a library for 2d graphics
  - draw a shape
  - draw a line
  - draw a curve
  - draw a curve with variable thickness
  - find points along the curve and 'branch'
  - ...
 
 requirements:
 sfml v3.1

i compile it with:

cl.exe main.cpp /std:c++17 /EHsc /I"C:\Program Files\SFML\SFML-3.1.0\include" /link /LIBPATH:"C:\Program Files\SFML\SFML-3.1.0\lib" sfml-graphics.lib sfml-window.lib sfml-system.lib /out:main.exe

