# PixlHide, a steganography tool
A practical implementation of Steganography

## Tasks and Requirements
The requirements for the project is translated and put into a markdown file [Practical Work Assignment](Docs/Practical_Work_Assignment_2026.md). In the [./Docs](Docs) folder you will find the documnetation from blackboard and original Spanish text for the work.

# Make and run program 

To run this program you will need Make and gcc (or similar) compiler. 
To see avaliable compile targets use the command ```make```, and use ```make run``` to execute program rigth after compilation. ```make clean``` deleates all build-files.

To use the program the following TWO modes are supported

```
pixlhide –d –secret clave.bmp –k 2 –n 4 –dir varias
```

```
pixlhide –r –secret secreta.bmp –k 2 –n 4 –dir varias 
```

# Documentation
I've Started adding doxygen style comments, but I dont think there is any need to acutually generate the docs. The comment type is just nice tooltips when hovering over functions in VS Code. 
