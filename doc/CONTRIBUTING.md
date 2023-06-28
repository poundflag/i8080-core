# Contribution Guidelines <!-- omit in toc -->

Welcome to the contribution guidelines for **i8080-core**! I appreciate your interest in contributing to my project.<br>
This document will guide you through the process of contributing.

## Table of Contents <!-- omit in toc -->

- [Getting Started](#getting-started)
  - [Relevant documentation and sources](#relevant-documentation-and-sources)
  - [Code Style](#code-style)
  - [Branching Rules](#branching-rules)
  - [Opening an issue](#opening-an-issue)
- [Contributing Code](#contributing-code)
  - [Step 1: Fork the Repository](#step-1-fork-the-repository)
  - [Step 2: Set Up the Development Environment](#step-2-set-up-the-development-environment)
  - [Step 4: Make changes and create a pull request](#step-4-make-changes-and-create-a-pull-request)

## Getting Started

### Relevant documentation and sources

Besides the documentation itself here are some resources i use in the development of this project:
- [Opcodes of the Intel 8080](https://pastraiser.com/cpu/i8080/i8080_opcodes.html)
- [rokkerruslan Intel 8080 Emulator](https://rokkerruslan.github.io/)
- [Intel 8080 Programmers Manual](https://altairclone.com/downloads/manuals/8080%20Programmers%20Manual.pdf)
- [GunshipPenguin's Emulator for the flagregister refinements and ALU idea](https://github.com/GunshipPenguin/lib8080/blob/master/src/i8080.c)
- [Superzazu for the CPU-Test resources](https://github.com/superzazu/8080/tree/master/cpu_tests)
- [Rokkerruslan's Emulator for some minor testing](https://rokkerruslan.github.io/assembler)
- [Oshonsoft's 8085 Simulator (which apparently produces false flagregister results!)](https://www.oshonsoft.com/8085.php)
- [A basic explaination of all instructions](http://dunfield.classiccmp.org/r/8080.txt)

### Code Style

Please follow the rules from my [Code Style](CODE_STYLE.md) to create consistent code.

### Branching Rules

Please don't use the `main-branch` as a base revision, as it is used to build a specific release.

If you plan to contribute to the project always use the `develop-branch` as a base revision. It will be merged in the `main-branch` if a release is planned.

### Opening an issue

To open up an issue you can follow the guide [Opening an Issue](OPENING_ISSUE.md).

## Contributing Code

### Step 1: Fork the Repository

1. Go to the **i8080-core** repository on GitHub: [github.com/poundflag/i8080-core](https://github.com/poundflag/i8080-core).
2. Click on the "Fork" button in the top-right corner of the repository page.
3. After forking, you will have a copy of the repository in your GitHub account.

### Step 2: Set Up the Development Environment

Follow the guide to [Set Up the Development Environment](SETUP_DEV_ENVIRONMENT.md).

### Step 4: Make changes and create a pull request

1. Go to your forked repository on GitHub. You should see a banner indicating that you recently pushed a new branch.
2. Click the "Compare & pull request" button next to the branch name.
3. Provide a descriptive title and detailed description for your pull request, explaining the changes you made.
4. Review the changes in the "Files changed" tab to ensure everything looks correct.
5. If everything is in order, click the "Create pull request" button to submit your pull request.

