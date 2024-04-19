# Led Matrix Controller

A simple C++ script that allows you to control a led matrix with a bunch of different animations and images, using [rpi-rgb-led-matrix](https://github.com/hzeller/rpi-rgb-led-matrix)

# Animations
- [x] Shifting colors
- [x] Game of life
- [x] The time and date
- [ ] Rotating square
- [ ] Rotating cube
- [ ] Mandelbrot set
- [ ] That one donut rendering thing that appears on YT
- [ ] Snake
- [ ] Sorting algorithms

## Other planned animations

- [ ] Arbitrary images
- [ ] Arbitrary videos
- [ ] Arbitrary text
- [ ] Arbitrary drawings


# Usage

In order to use this thing, you gotta compile it first (I know, if I figure out how, maybe I'll add releases one day)

To build this project you will need to have git, cmake and make installed on your raspberry pi.
Said raspberry pi must also be set up with a led matrix

To compile, on the raspberry pi run he following:

(note, if you want help connecting the raspberry pi to an led matrix, I will make a tutorial at some point)

```bash
$ git clone "https://github.com/h8moss/led-matrix"  # Clone the repository
$ cd led-matrix                                     # Go into the project
$ mkdir build                                       # Make a directory for the build to go to
$ cd build                                          # Go into the build directory
$ cmake ..                                          # Generate the build files
$ make                                              # Actually build this project
```

That should leave you with either an error, or two executables `led-matrix` and `led-matrix-manager`, both of these
must be run with `sudo`

`led-matrix` runs using flags and the command line, it should hopefully give you a self explanatory "usage" message if 
you just run `sudo led-matrix`

`led-matrix-manager` works similarly, but receives the command line arguments from a fifo, allowing it to be controlled through IPC

