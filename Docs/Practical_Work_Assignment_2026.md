# Cryptography and Security (72.04) 2026

## PRACTICAL IMPLEMENTATION WORK: SHARED SECRET IN IMAGES WITH STEGANOGRAPHY

## 1. Objectives

- Introduce students to the field of visual cryptography and its applications, through the implementation of a Shared Secret in Images algorithm.
- Introduce students to the field of steganography and its applications.
- Implement and analyze an algorithm described in a scientific document.

## 2. Assignment

Develop a program in C or Java that implements the Shared Secret in Images algorithm described in the document *"An Efficient Secret Image Sharing Scheme"* by Luang-Shyr Wu and Tsung-Ming Lo from the China University of Technology, Taiwan.

The program must allow:

1. Distributing a secret image with `.bmp` extension into other images, also with `.bmp` extension, that will be the shadows in a (k, n) shared secret scheme.
2. Recovering a secret image with `.bmp` extension from k images, also with `.bmp` extension.

## 3. Introduction

Visual cryptography is a concept introduced in 1994 by Adi Shamir and Moni Naor. In their presentation at EUROCRYPT'94 they considered a new type of cryptographic scheme that can decode secret images without using classical cryptographic calculations. In essence, the system they devised was an extension of the concept of shared secret schemes, but applied to images. The images that contained the secret information, distributed in a secure manner, could later be superimposed to recover the secret image.

The concept of Shared Secret Scheme was also, in part, Shamir's idea. Adi Shamir and George Blakley conceived in 1979, although separately, the concept of Shared Secret as a way to protect keys.

Both Shamir and Blakley argue that keeping the key in a single place is highly risky and keeping multiple copies in different places only increases the security gap. Shamir, for example, concludes that the secret (D) must be divided into a fixed number of parts (D1, D2, ..., Dn) such that:

1. Knowing any subset of k of these parts, D can be reconstructed.
2. Knowing any subset of k-1 of these parts, the value of D remains undetermined.

Blakley's document describes a way to achieve the objective of distributing shadows in the required manner, using concepts of projective geometry.

The document to be implemented in this practical work proposes a scheme for sharing a secret image based on Shamir's method. To make the image hidden in the shadows practically imperceptible, the document mentions the possibility of using hiding methods, i.e., steganography.

Steganography (from the Greek *steganos*, covered or hidden, and *graphos*, writing) is the science that deals with the way of hiding a message.

The existence of a message or object is hidden within another, called the carrier. The objective is to protect sensitive information, but unlike cryptography, which makes such information unintelligible, steganography makes the information go completely unnoticed by hiding its very existence.

Cryptography and steganography complement each other. A message encrypted using cryptographic algorithms can be noticed by an intruder. An encrypted message that has also been hidden using some steganography method has a much higher level of security since intruders cannot detect its existence. And if for any reason an intruder were to detect the existence of the message, they would find the encrypted information.

## 4. System Details

### 4.1 General

The program must receive the following mandatory parameters:[^1]

- `-d` or `-r`
- `-secret image`
- `-k number`

And the following optional parameters:

- `<-n number>`
- `<-dir directory>`

**Meaning of each mandatory parameter:**

- `-d`: indicates that a secret image is going to be distributed into other images.
- `-r`: indicates that a secret image is going to be recovered from other images.
- `-secret image`: The name `image` corresponds to the name of a file with `.bmp` extension. If the `-d` option was chosen, this file must exist as it is the image to be hidden. If the `-r` option was chosen, this file will be the output file, containing the revealed secret image at the end of the program.
- `-k number`: The `number` corresponds to the minimum number of shadows needed to recover the secret in a (k, n) scheme.

**Meaning of each optional parameter:**

- `<-n number>`: The `number` corresponds to the total number of shadows into which the secret will be distributed in a (k, n) scheme. It can only be used if the `-d` option was chosen. If not used, the program will choose as the value of n the total number of images in the directory.
- `<-dir directory>`: The directory where the images into which the secret will be distributed are located (if the `-d` option was chosen), or where the images containing the hidden secret are located (if the `-r` option was chosen). If not used, the program will look for the images in the current directory.

**Examples:**

- Hide the image `clave.bmp`, in a (2, 4) scheme, looking for images in the `varias` directory:
  ```
  $visualSSS –d –secret clave.bmp –k 2 –n 4 –dir varias
  ```
- Hide the image `clave.bmp`, in a scheme using k = 3, looking for images in the current directory:
  ```
  $visualSSS –d –secret clave.bmp –k 3
  ```
- Recover the image `secreta.bmp`, in a (2, 4) scheme, looking for images in the `varias` directory:
  ```
  $visualSSS –r –secret secreta.bmp –k 2 –n 4 –dir varias
  ```
- Recover the image `secreta.bmp`, in a scheme using k = 3, looking for images in the current directory:
  ```
  $visualSSS –r –secret secreta.bmp –k 3
  ```

[^1]: Respect the order of the parameters.

### 4.2 Distribution Algorithm

In distribution, the following aspects must be considered:

#### 4.2.1 Value of k

The value of k must be greater than or equal to 2 and less than or equal to 10. (And also less than or equal to n).

#### 4.2.2 Value of n

The value of n must be at least 2.

#### 4.2.3 Secret Image

The secret image must be in BMP format, 8 bits per pixel. (1 byte = 1 pixel)

The BMP format is a fairly simple binary image file format. It consists of two parts:

i. **Header** → 54 bytes
ii. **Body** → variable size

The header contains information about the file: file size, image width, image height, bits per pixel, whether it is compressed, etc.

**IMPORTANT:** Read carefully the value indicating at which offset the pixel matrix begins, as it may start immediately after the 54 bytes of the header, or it may start later.

In the body of the BMP file are the bits that define the image itself. The image is read from bottom to top and from left to right. If the image is 8 bits per pixel, it is a grayscale image: the pixel with value `0x00` is black and the pixel `0xFF` is white.

Be careful when choosing the image: review it with a hexadecimal editor to ensure that it has no extra information at the end (metadata) and that it conforms to the required format.

#### 4.2.4 Permutation Table

The permutation table R used by the algorithm proposed by the paper will be generated from a seed hidden in the BMP file (the next section indicates where).

For an image of, for example, m pixels, a sequence of m values in the range [0, 255] will be generated.

##### 4.2.4.1 Implementation in C language

See the annexed document *Implementation Permutation Table*.

##### 4.2.4.2 Implementation in Java language

See the annexed document *Implementation Permutation Table*.

#### 4.2.5 Carrier Images and Hiding via Steganography

Carrier images must be in BMP format, 8 bits per pixel.

##### (8, n) Scheme

In case the value of k equals 8, the images must have the same size (width and height) as the secret image. If there are not n images that meet this condition, an error message is displayed and nothing is done.

The hiding of information will be done using the LSB replacement (Least Significant Bit) method. This will be done in the order in which the bytes are obtained starting from the first pixel (taking the offset into account) and considering the bits from most significant to least significant.

Thus, supposing the first value to hide was `0xD1` (1101 0001), and supposing the first pixel begins at offset 1078:

| Byte | Current Value | Last 4 bits | Value After | Last 4 bits |
|------|---------------|-------------|-------------|-------------|
| Byte 1078 | ED | 1101 | ED | 1101 |
| Byte 1079 | A4 | 0100 | A5 | 0101 |
| Byte 1080 | 45 | 0101 | 44 | 0100 |
| Byte 1081 | 36 | 0110 | 37 | 0111 |
| Byte 1082 | 3A | 1010 | 3A | 1010 |
| Byte 1083 | 3A | 1010 | 3A | 1010 |
| Byte 1084 | 3A | 1010 | 3A | 1010 |
| Byte 1085 | 39 | 1001 | 39 | 1001 |

The random number generation seed will be a 2-byte integer and must be hidden in bytes 6 and 7 of the BMP file (reserved bytes section).

Thus, if the number is 641 (0000 0010 1000 0001), the following will be stored:[^2]

| Byte | Current Value | Value After |
|------|---------------|-------------|
| Byte 6 | 00 | 81 |
| Byte 7 | 00 | 02 |

The order number corresponding to the shadow (i.e., whether the shadow is number 1, 2, 3, ... k) must be hidden in bytes 8 and 9 of the BMP file (reserved bytes section).

Thus, if the shadow is the third one (0000 0000 0000 0011), the following will be stored:

| Byte | Current Value | Value After |
|------|---------------|-------------|
| Byte 8 | 00 | 03 |
| Byte 9 | 00 | 00 |

[^2]: Be careful with Little/Big Endian encoding. Take the bits as shown in the example.

##### (k, n) Scheme with k different from 8

In case the value of k is different from 8, it is up to the group to define (with justification) the size of the carrier images and the hiding method.

It must be indicated in the README if there is any special requirement for the carriers in this case.

### 4.3 Recovery Algorithm

#### 4.3.1 Value of k

The value of k must be greater than or equal to 2 and less than or equal to 10.

#### 4.3.2 Secret Image

##### (8, n) Scheme

The secret image must be generated the same size as the carrier images. To build its header, the header of any of the carrier images can be used.

##### (k, n) Scheme with k different from 8

Each group must determine how the secret image is regenerated (in correspondence with what is established in item 4.2.5).

#### 4.3.3 Carrier Images

##### (8, n) Scheme

Carrier images must be in BMP format, 8 bits per pixel, and all of the same size (width and height) as each other. If there are not 8 images that meet this condition, an error message is displayed and nothing is done.

##### (k, n) Scheme with k different from 8

Each group must determine how to validate the carrier images (in correspondence with what is established in item 4.2.5).

#### 4.3.4 Permutation

It is verified in the reverse manner to distribution.

#### 4.3.5 Secret Recovery

It is recommended to use the Gauss method or the reduced Lagrange method (see *"Clase de Shamir.ppt"*) and not the determinants method to solve the system of equations. Keep in mind that you are working in integer arithmetic modulo 257.

## 5. Issues to Analyze

The following issues must be analyzed:

1. Discuss the following aspects relative to the Luang-Shyr Wu and Tsung-Ming document:
   - a. Formal organization of the document (parts of the paper).
   - b. The description of the distribution algorithm and the recovery algorithm.
   - c. The notation used: is it clear? Does it change throughout the document?
2. Is the recovered image exactly the same as the original hidden image? Why?
3. Analyze the security in the location of the shadow number and permutation seed. In what other way or in what other place could they be stored?
4. Explain the criterion used to hide the shadows in the case of k different from 8. What size should the carriers be? Indicate whether there were previous proposals that were discarded.
5. Discuss the following aspects relative to the implemented algorithm:
   - a. Ease of implementation
   - b. Possibility of extending the algorithm to use color images (24 bits per pixel)
6. What difficulties did you have in reading the document and/or in the implementation?
7. What extensions or modifications would you make to the implementation or to the algorithm?
8. In what situations would you apply this type of algorithms?

## 6. Group Organization

The work will be carried out in groups of a maximum of 3 members. Groups will register through the campus.

## 7. Submission

The submission date is **June 8**.

Each group will submit the executable and the source code in C or Java, along with the files to obtain the executable and the documentation corresponding to the use of the program, through a specific activity on the campus.

Additionally, they will present in the same activity a report with the solution corresponding to the recovery of the secret from the files we will provide to the group in due time, and with the analysis of each of the issues raised in section 5 (Issues to Analyze).

## 8. Approval Criteria

For the work to be approved, the following will be considered:

- Submission on the indicated date.
- That the program can perform the recovery of the secret for the files provided by the course staff.
- That the program can perform the distribution and recovery of the secret.
- That the content of the report is correct and complete, i.e., that all issues in section 5 are answered.

Additionally, consider:

- It is a necessary condition for approval that the program works correctly in the **pampero environment** at ITBA. Verify that the use of any library is possible in that environment.
- The execution syntax of the assignment must be respected. Respect even uppercase and lowercase letters.
- The program must report errors explicitly. For example, if there was an error in an input parameter, the user must be informed of the error and the correct syntax.

The grade will be composed of 60% by the program and 40% by the report. Both the report and the program are mandatory.

If the work, submitted on June 8, is later disapproved, it can be resubmitted only once. The resubmitted work can only have a maximum grade of 4 (four).

For submission, as well as for any inconvenience, students must communicate with the professors or assistants.

## 9. Reading Material

- Chapter 15 of *Computer Security – Art and Science*, Matt Bishop, Addison-Wesley, 2004
- Chapters 10 and 12 of *Handbook of Applied Cryptography*, Alfred J. Menezes, Paul C. Van Oorschot, Scott A. Vanstone, CRC Press, 1997
- *"An Efficient Secret Image Sharing Scheme"* by Luang-Shyr Wu and Tsung-Ming
- *"Secret image sharing"*, by Chih-Ching Thien and Ja-Chen Lin.
- *"Secreto Compartido"*, by Ana María Arias Roig.

**On Visual Cryptography:**

- Doug Stinson's Visual Cryptography page: [https://cs.uwaterloo.ca/~dstinson/visual.html](https://cs.uwaterloo.ca/~dstinson/visual.html)
- *"Visual Cryptography"*, Moni Naor and Adi Shamir: [http://www.wisdom.weizmann.ac.il/~naor/PAPERS/vis.pdf](http://www.wisdom.weizmann.ac.il/~naor/PAPERS/vis.pdf)

**On BMP Format:**

- [http://www.fileformat.info/format/bmp/corion.htm](http://www.fileformat.info/format/bmp/corion.htm)
