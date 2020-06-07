# UML-ifier

Developed by Adam Payzant.

A disgusting joke program to generate a UML from header files, then turn all headers into a UML diagram of the program. Inspired by [this post](https://www.reddit.com/r/programminghorror/comments/glwk7k/a_c_header_file_that_doubles_as_a_uml_diagram/). Please do not take the actual contents of this project too seriously.

## Requirements and Installation

This project only uses standard libraries, so just run:

`make all`

## Usage

To generate and umlify header files, run as:

`umlify "/path/to/header/files"`

There are currently two additional options umlify can be run with.

* -g : Only generates a UML file
* -u : Skips UML file generation and modifies the header files. Requires a UML file to already be generated

ex:

`umlify -g "/path/to/header/files"`

`umlify -u "/path/to/header/files"`

## License
[MIT](https://choosealicense.com/licenses/mit/)