Cryptolator

![](/screenshot.png?raw=true)

Cryptolator is an application that encrypts and decrypts text messages and files using a given mask. It does this through simple addition encryption. It adds each byte of the text/file with the corresponding byte of the mask. The result is the encrypted code. To decrypt, it simply subtracts the corresponding byte of the mask with each byte of the text/file. This allows two people to communicate privately providing both have access to the mask. The mask could be a photo or a random file they both have.

********************************************************************************
INSTALLING

This application uses Qt which will need to be installed to compile this project.

Windows:

You may use the binaries located in /bin or compile it yourself.

To compile:
First, you must download and install Qt from http://qt-project.org/downloads
Note: This is a very large library so patience and perseverance are in order.

The basic instructions for installing it are to open up the project Cryptolator on
QtCreator (the official Qt IDE) and compile it with that. 
After Qt has been installed, open QtCreator (which comes with Qt) and click File->Open Project and 
browse for the Cryptolator.pro file. To compile the project, you do Build->Build All. 
You can now run Cryptolator by clicking the 'Play' button. The actual build files and executable 
will be found in the Qt Project directory which is usually Qt/Projects/. It should be in a folder called
something along the lines of 'Cryptolator build...'. Note: The default project directory can be 
changed in Qt Creator.


Linux:

We'll describe how to do this on Ubuntu 16.04 LTS, and hope for the best with your version of Linux.

1. To install Qt4, on the terminal enter sudo apt install qt4-default
2. Move into the Cryptolator directory with the command
   cd Cryptolator
3. and then give the command
   qmake
4. followed by the command
   make
5. This should create an executable file called Cryptolator which can then be run with the command
   ./Cryptolator
6. If you wish Cryptolator to be systemically available, then give the command
   sudo cp Cryptolator /usr/local/bin


Author: Abdul Hakim Johnson
