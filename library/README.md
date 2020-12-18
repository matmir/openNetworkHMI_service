Shared Memory driver libraries for C and C++ based control program.

COMPILATION
===========

Go to selected library directory and run: 

	mkdir build          # Directory with build output
	cd build
	cmake ..             # Generate build script
	make 
	sudo make install    # Install library in /usr/local

To build library with tests add option:

	cmake -DWithTest=true ..

License
=======

libonhSHMc and libonhSHMcpp are licensed on BSD-3-Clause license.