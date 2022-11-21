# Pong Game

We created a 2 player Pong game using Godot game development engine and their GDNative C++ module.

The game is compatible with Windows, Linux, or OSX



## Dependencies
Before cloning this repository and building this project please make sure you have all of the following:
- git
- python
- pip
- scons
- Godot Editor

### Quick Guide for all Dependencies
First make sure you have python installed using the following command in your terminal on Linux/MacOS:
```
python3 --version
```
Or the following code in command prompt if you are on Windows:
```
py --version
```
If python is not installed please download the latest version at [python.org](https://www.python.org/)

Second make sure pip is installed as well. This can be a bit of a pain to set 
up so this document will link to pip's own documentation on [how to install pip](https://packaging.python.org/en/latest/tutorials/installing-packages/) as it will explain this better.

Third you need to make sure you have SCons installed:
```
python3 -m pip install scons
```

The fourth dependancey needed is git. If you don't have git installed or don't know if you have 
git installed please check the guide for downloading over at [GitHub](https://github.com/git-guides/install-git) or just google search: install git, it isn't hard to find but it would take up to
much space in this readme.

The final dependency is the Godot Editor which can simply be installed from [Godot's offical website](https://godotengine.org/download)

## Compiling
Now that all the dependancies have been installed you can clone the repository and then build the project. Start by cloning the repository using the command:
```
git clone --recursive https://github.com/danirod10/CSE165_Pong
```

Next open the terminal and use the command:
```
 cd /path/to/CSE165_Pong/final_project 
```
to get to the proper directory where you can use SCons to compile the library using:

```
scons platform=PLATFORM
```

Where PLATFORM is: `windows`, `linux`, or `osx`.

What this does is complie our cpp files in CSE165\_Pong/src along with CSE165\_Pong/godot-cpp and
creates a dynamic library in CSE165\_Pong/project/gdnative/platform that then can be accessed by
a .gdnlib file. This .gdnlib file code is taken from Godot's own [documentation](https://docs.godotengine.org/en/stable/tutorials/scripting/gdnative/gdnative_cpp_example.html).

From there the .gdns files in CSE165\_Pong/final\_project/project/logic link to the .gdnlib file, and
then the .gdns files are attacted to the proper objects in pong.tscn. You should be able to see this for 
yourself using the godot editor installed earlier, or by opening the .tscn files in a text editor since .tscn files are human readable.

The final step is to open the godot editor, import the project, and then go to project settings, click
export and export the project to the platform you're computer is running on.


This creates the file `Pong_project.[appropriate executable file type]` 
which you need to double click to start the game 


## How to play?
```
Player 1(Green) Controls: W(UP), S(Down)
```
```
Player 2(Red Orange) Controls: UP ARROW(UP), DOWN ARROW(Down)
```




