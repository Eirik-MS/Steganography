# PixlHide, a steganography tool
A practical implementation of Steganography


# Make and run program 

To run this program you will need Make and gcc (or similar) compiler. 
To compile the program use the command ```make```, and use ```make run``` to execute program rigth after compilation. ```make clean``` deleates all build-files.

To use the program the following TWO modes are supported

```
pixlhide –d –secret clave.bmp –k 2 –n 4 –dir varias
```

```
pixlhide –r –secret secreta.bmp –k 2 –n 4 –dir varias 
```
