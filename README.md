# Led Matrix Controller 🌈

A powerful C++ Application for driving LED matrix displays with the raspberry Pi. Built on top of [rpi-rgb-led-matrix](https://github.com/hzeller/rpi-rgb-led-matrix)

![License](https://img.shields.io/badge/license-MIT-blue.svg)
![Platform](https://img.shields.io/badge/platform-Raspberry%20Pi-red.svg)
![Language](https://img.shields.io/badge/language-C%2B%2B-green.svg)

## Featured animation modules
- [x] Shifting colors
- [x] Game of life
- [x] The time and date
- [ ] Rotating square
- [ ] Rotating cube
- [ ] Mandelbrot set
- [ ] That one donut rendering thing that appears on YT
- [ ] Snake
- [ ] Pong
- [ ] Sorting algorithms

### Other planned modules

- [x] Arbitrary images
- [ ] Arbitrary videos
- [ ] Arbitrary text
- [ ] Arbitrary drawings

## 🚀 Installation

### Prerequisites
- Raspberry Pi (any model)
- LED Matrix display properly connected
- Git
- CMake
- Make
- Required libraries: libgraphicsmagick++-dev, libwebp-dev

### Build instructions

To build this project, run the following commands on the Raspberry Pi's command line
```bash
sudo apt-get update                                           # Update system packages
sudo apt-get install libgraphicsmagick++-dev libwebp-dev -y   # Install required dependencies
git clone "https://github.com/h8moss/led-matrix"              # Clone the repository
cd led-matrix/build-scripts                                   # Go into the project's build scripts
git submodule init                                            # Initialize submodules
git submodule update                                          # Update submodules
./build.sh                                                    # Generate the build files
cd ../build                                                   # Go into the build directory
make                                                          # Build the project
```

## 📚 Usage

After a successful build, two executables will be generated in the build directory, both of which require `sudo` to run.

### `led-matrix`
Run any module directly using CLI arguments

```bash
sudo ./led-matrix                   # Shows usage information
sudo ./led-matrix --help            # Display help message
sudo ./led-matrix <MODULE> --help   # Module-specific help
```

### `led-matrix-manager`
Operates through IPC (Inter-Process Communication) using a FIFO, allowing remote control of the display.

```
sudo ./led-matrix-manager <PATH-TO-FIFO>
```
## 🎨 Font Support
The time-date module uses BDF fonts for text rendering. Default fonts are included in:

```
led-matrix/rpi-rgb-led-matrix/src/rpi-rgb-led-matrix/fonts
```

Custom fonts in BDF format can be added to this directory. Online converters are available for converting other font formats to BDF. But beware, most fonts will be too big to fit in an ordinary LED matrix

## 🤝 Contributing
Contributions are welcome! Feel free to:

Report bugs
Suggest new features
Submit pull requests

## 📝 License
This project is open source and available under the MIT License.

## 🙏 Acknowledgments
rpi-rgb-led-matrix library for the core LED matrix functionality
