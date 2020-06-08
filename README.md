# UML-ifier

Developed by Adam Payzant.

A disgusting joke program to generate a UML class diagram from header files, then turn all headers into a UML diagram of the system. Inspired by [this post](https://www.reddit.com/r/programminghorror/comments/glwk7k/a_c_header_file_that_doubles_as_a_uml_diagram/). Please do not take the actual contents of this project too seriously.

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

## Current Shortcomings

* Some UML class diagram specifications are broken or str to ensure headers will still operate normally (This is unlikely to be completely fixable)
* Header files need to following the following specifications:
    - Only one class is defined
    - Only one parent
    - All attributes must be declared on seperate lines
    - Functions and values cannot be defined in the header file
    - Header files must follow the format seen in this project's headers
    - Other issues may arise if there's something I didn't catch
* UML-ifier will not acknowledge container classes as different, and will include them in the diagram
* Does not support multiple inheritances

## License
[MIT](https://choosealicense.com/licenses/mit/)