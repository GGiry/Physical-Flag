Physical-Flag
=============

To compile
----------
  First compile lib/libg3x++
    cd lib/libg3x++
    make
    cd ../..
  Compile the project
    make


To launch
---------
  Add lib/libg3x++ to LD_LIBRARY_PATH with:
    LD_LIBRARY_PATH=lib/libg3x++:$LD_LIBRARY_PATH
  Execute the program
    ./main
