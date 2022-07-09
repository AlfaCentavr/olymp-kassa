# About this Project

This app is build with pure C++ with the framework Qt Creator 6.2.4 

# Getting Started

**Prerequisites**

To run this project, you'll need to have g++ and Qt Creator installed.

**Installing**

To install the g++ compiler for C++ code, run this on terminal:

        $ sudo apt install g++

Download and Install Qt from [here](https://www.qt.io/download).

After that, clone this Repository:

    $ git clone https://github.com/AlfaCentavr/olymp-kassa.git
  
Launch Qt Creator, and open the file "OlympClinic/OlympClinic.pro". This will open all the related files of this project in Qt.

To run the project, click on the green triangle on the left bottom part of the window. This will make the window pop just link in the screenshot above. 

You can test it with the .mp3 file in this repo.

# Built With
- [Qt](https://www.qt.io): Cross platform software development for embedded systems.

# About install
You need to create a settings.ini file along the path C:\monitor
It is necessary to define 2 fields in the settings file: [MAIN], [POSITION].
[MAIN] includes parameters
PATH_HTML=C:/monitor/act.html
FONT_NAME=Halvar Engschrift Light.ttf
FONT_SIZE=60
INTERVAL_READING=1
PATH_MEDIA=D:/monitor/media
IMAGE_INTERVAL=5
[POSITION] includes parameters
X=0
Y=0
dX=650
dY=400
