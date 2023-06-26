Setting Up the Development Environment

To contribute to i8080-core, you need to set up a local development environment. This guide will walk you through the necessary steps.

Prerequisites

Before you begin, ensure that you have the following installed on your system:

- GCC (GNU Compiler Collection)
- Make
- Clang-Formatter

Installation Steps

1. Clone the repository to your local machine using the following command:

   ```bash
   git clone https://github.com/poundflag/i8080-core.git

2. Change to the project directory:

cd i8080-core

3. Build the project by running the following command:

make all

This command will compile the source files, create a library, and generate the binary file.

4. (Optional) If you want to run the test files, use the following command:

make test

This command will compile the test files, link them with the project library, and execute the tests using the Unity testing framework.

Note: The test files should be located under the "test" directory within the project.

5. After building the project and running the tests, you can find the compiled binary and library files under the "bin" directory.

Conclusion

Once you have set up your development environment, you're ready to contribute to i8080-core. Make sure to follow our Contribution Guidelines to ensure a smooth collaboration process.

If you encounter any issues during the setup process or have any questions, please don't hesitate to reach out to me. Happy coding!