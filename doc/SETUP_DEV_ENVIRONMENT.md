# Setting Up the Development Environment

To contribute to i8080-core, you need to set up a local development environment. This guide will walk you through the necessary steps. This guide only shows how to set up the project on Linux.

## Prerequisites

Before you begin, ensure that you have the following installed on your system:

- GCC (GNU Compiler Collection)
- Make
- Clang-Formatter

Installation Steps

1. Clone the repository to your local machine using the following command:

```bash
git clone https://github.com/poundflag/i8080-core.git
```
If you've forked the repository, please change the url to your own fork.

2. It is recommended to only develop using the latest version, which is located under the `develop` branch. To check this branch out use the following command:

```bash
git checkout develop
```

3. Change to the project directory:

```bash
cd i8080-core
```

4. Build the project by running the following command:

```bash
make all
```
This command will compile the source files, create a library, and generate the binary file.

5. If you want to run the tests, use the following command:

```bash
make test
```

This command will compile the test files, link them with the project library, and execute the tests using the Unity testing framework.

Note: The test files should be located under the "test" directory within the project.

6. Before commiting any code, please ensure that you've formatted the code using clang formatter. Either install a plugin or use the following command:

```bash
clang-format -i <FILE> --
```
This will ensure that the code is consistent throughout the project.

7. After building the project and running the tests, you can find the compiled binary and library files under the "bin" directory.

## Conclusion

Once you have set up your development environment, you're ready to contribute to i8080-core. Make sure to follow my [Contribution Guidelines](CONTRIBUTING.md) to ensure a smooth collaboration process.

If you encounter any issues during the setup process or have any questions, please don't hesitate to reach out to me. Happy coding 😊