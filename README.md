<p align="center">
  <a href="" rel="noopener">
 <img width=200px height=200px src="icon.png" alt="Project logo"></a>
</p>

<div align="center">

[![Status](https://img.shields.io/badge/status-active-success.svg)]()
[![GitHub Issues](https://img.shields.io/github/issues/embed-coder/sensor-fusion?style=plastic)](https://github.com/embed-coder/sensor-fusion/issues)
[![GitHub Pull Requests](https://img.shields.io/github/issues-pr/embed-coder/sensor-fusion)](https://github.com/kylelobo/The-Documentation-Compendium/pulls)
[![License](https://img.shields.io/badge/license-MIT-blue.svg)](/LICENSE)

</div>

---

<p align="center"> Multiple sensor connections, communicaions, storing, and forwarding data.
    <br> 
</p>

## 📝 Table of Contents

- [About](#about)
- [Getting Started](#getting_started)
- [Running the tests](#tests)
- [TODO](#todo)
- [Authors](#authors)

## 🧐 About <a name = "about"></a>

SensorFusion collects and controls data from various types of sensors. It allows users to receive data from sensors and send commands to control them. SensorFusion also provides a platform to store data received from sensors in databases and forward them to the cloud. With SensorFusion, users can easily integrate and manage different types of sensors in their projects.

Sensor Fusion config every sensor independently, enabling/disabling without impact to other sensors' operation.

Data will be stored in the database and optional to a CSV file with configurable path and frequency.

## 🏁 Getting Started <a name = "getting_started"></a>

Clone project from this repository or download the source files in compressed format in the list of release packages.

### ➡️ Prerequisites

Dependencies:

- cmake
- googletest
- libserial-dev
- socat

Install dependency packages:

```
sudo apt update
sudo apt install -y autogen autoconf build-essential cmake\
                    gcc git graphviz g++ libgtest-dev libserial-dev libtool\
                    pkg-config  socat
```

### ⛏️ Compiling

A step by step series of examples that tell you how to get a development env running.

Compile the SW

```
./build.sh
```

The output will be

```
m2m-serial test_lins355
```

## 🔧 Running the tests <a name = "tests"></a>

Run the automated tests for this SW.

### ✅ Unit test

The output will be like below

```
sudo ./run_test.sh

```

### 🚀 Running SW

Run SW with the real device: "./m2m-serial <device_file>"

```
sudo ./m2m-serial -d /dev/ttyUSB0
```

## 📝 Todo <a name="todo"></a>

The Bucket list for the future implemented features:

- Output logs to a file and set logging rotation.
- Get version from git tag for auto naming the output packages.
- Configuration for SW from json file.
- Replace data storing by a real time database for a better management and scalability.
- Documentation for software and solution architecture (UML & Graph).

## ✍️ Authors <a name = "authors"></a>

- [@embedcoder](https://github.com/embed-coder) - Idea & Initial work
