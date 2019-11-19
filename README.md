myrm – remove files

usage: myrm [-h|--help] [-f ] [ -R ] <file1> <file2> <file3>
  
-h   find out instruction of using
-R   allow to remove directories
-f   skip message before removing


To compile:
  mkdir build
  cd build
  cmake .. -DCMAKE_BUILD_TYPE=Release
  make
  cd ..
  ./myrm ...
