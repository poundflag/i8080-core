# i8080-core

i8080-core is a core library that emulates the behaviour of the Intel 8080 Microprocessor.

## Table of Contents

- [Getting Started](#getting-started)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

## Getting Started

These instructions will help you get a local copy of the project up and running on your machine.

### Compile the project yourself

1. **Clone the project with `git clone https://github.com/poundflag/i8080-core`**
2. **Run `make all` in the root directory of the project**
3. **The compiled application is located under the directory `bin/`**

### Run all tests

1. **Run `make test` in the root directory of the project**
2. **The console output should display the failed testcases and passed suites**

### Development-Prerequisites

The following dependencies need to be installed in order to develop the project, or to run the tests.

| Dependency                                                                         |
| ---------------------------------------------------------------------------------- |
| [Check](https://libcheck.github.io/check/web/install.html#yum)                     |
| [Check-Devel](https://yum-info.contradodigital.com/view-package/base/check-devel/) |

## Usage

Due to the early version of this project there are really only two use-cases for this project.
The project can either be used to develop an i8080 based machine around the interfaces of this project provided, or to run code and to check the output of the output file.

## License

This project uses the MIT-License.