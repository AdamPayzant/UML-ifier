# UML-ifier

Developed by Adam Payzant.

A disgusting program to generate a UML from header files, then turn all headers into a UML diagram of the program. Inspired by [this post](https://www.reddit.com/r/programminghorror/comments/glwk7k/a_c_header_file_that_doubles_as_a_uml_diagram/). Please do not take the actual contents of this project too seriously.

## Requirements and Installation

This project only uses standard libraries, so just run:

`make all`

## Usage

To run this program, run the binary and give a path to the header files of a project. It currently will only load header files in the provided folder.

`umlify /path/to/header/files`

## License
[MIT](https://choosealicense.com/licenses/mit/)