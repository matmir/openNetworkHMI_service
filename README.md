openNetworkHMI service
=======

Service part of the openNetworkHMI project.

COMPILATION
===========

Run: 

	mkdir build			# Directory with build output
	cd build
	cmake ..				# Generate build script
	make					# Build application

To build application with tests add option:

	cmake -DWithTest=true ..

TESTING
===========

Tests need to be run from tests directory of the main openNetworkHMI project via sh script.

Project site: https://opennetworkhmi.net