[![license](https://img.shields.io/github/license/Evgenk2020/student-experiment)](https://github.com/Evgenk2020/student-experiment/blob/main/LICENSE)
[![last commit](https://img.shields.io/github/last-commit/Evgenk2020/student-experiment)](https://github.com/Evgenk2020/student-experiment/commits)
[![repo size](https://img.shields.io/github/repo-size/Evgenk2020/student-experiment)](https://github.com/Evgenk2020/student-experiment)
[![stars](https://img.shields.io/github/stars/Evgenk2020/student-experiment)](https://github.com/Evgenk2020/student-experiment/stargazers)
[![forks](https://img.shields.io/github/forks/Evgenk2020/student-experiment)](https://github.com/Evgenk2020/student-experiment/network/members)
[![top language](https://img.shields.io/github/languages/top/Evgenk2020/student-experiment)](https://github.com/Evgenk2020/student-experiment)
[![latest release](https://img.shields.io/github/v/release/Evgenk2020/student-experiment)](https://github.com/Evgenk2020/student-experiment/releases)
[![version](https://img.shields.io/badge/version-1.0.4-blue)](https://github.com/Evgenk2020/student-experiment)

# Statistical analysis of variance

This tool is designed for processing data sets that include more than two distinct variants, including cases with partial overlap. By default, it evaluates confidence intervals using the Student's t-test at a significance level of 0.05. This threshold can be adjusted to accommodate different precision requirements.

Run it with specified keys

```

stexp -d | -df [data...] [alf (0 <...< 1)]

```

Using `-df` key you may write data to `*.csv` file for the next importing to LibreOffice Calc, MS Excell or Google Tables

![Google table data import](/.img/screen.png)

.sh file example for running in terminal

```SH

#!/bin/bash

stexp -d 2.3 3.4 2.6 3.5
echo "----------------"
stexp -d 2.5 3.4 2.6 -- 8.9 11.2 13.5
echo "----------------"
stexp -d 2.3 3.4 2.6 3.5 alf 0.01
echo "----------------"
stexp -d 2.5 3.4 2.6 -- 8.9 11.2 13.5 alf 0.2

exec $SHELL

```

.sh file example for writing to `.csv`

```SH

#!/bin/bash

stexp -df 2.3 3.4 2.6 3.5
echo "----------------"
stexp -df 2.5 3.4 2.6 -- 8.9 11.2 13.5
echo "----------------"
stexp -df 2.3 3.4 2.6 3.5 alf 0.01
echo "----------------"
stexp -df 2.5 3.4 2.6 -- 8.9 11.2 13.5 alf 0.2

exec $SHELL

```

<hr>

You need to be installed on your Linux system previously:

- GCC g++
- Boost C++ Libraries
- CMake

(Fedora/CentOS Stream)
- rpm-build

On Fedora based systems run
<br>

```SH

sudo dnf group install development-tools
sudo dnf install boost boost-devel
sudo dnf install cmake
sudo dnf install rpm-build

```

On Debian based systems run
<br>

```SH

sudo apt update
sudo apt install build-essential
sudo apt install cmake
sudo apt install libboost-all-dev

```

On other systems see the details of your distro

<hr>

<b>To compile and run the utility (Fedora/CentOS Stream)</b>

1. Clone the Repository

```SH

git clone https://github.com/Evgenk2020/student-experiment

cd student-experiment

```

2. Build the Project with `.rpm` setup package for Fedora/CentOS Stream by default

```SH

./build.sh

cd build

```

3. Install `.rpm` package from build folder

```SH

sudo dnf install *.rpm

```

4. Run the application in terminal directly

```SH

stexp -h

```

<hr>

<b>If using either than Fedora/CentOS Stream</b>

1. Clone the Repository

```SH

git clone https://github.com/Evgenk2020/student-experiment

cd student-experiment

```

2. Change the string `set(assemble_tgz OFF)` to `set(assemble_tgz ON)` in CMakeLists.txt

```SH

nano CMakeLists.txt

```

3. Build the Project

```SH

./build.sh

```

4. Move `.tar.gz` file from `build` folder to any folder and unpack it

5. Run the program to check it from unpacked folder

```SH

./stexp -h

```

For more convenience add the application path into `.bashrc` file

```SH

export PATH="$PATH:/path/to/application/folder"

```

This will allow you to run the application in terminal directly

```SH

stexp -h

```
