<p align="center">
  <a href="" rel="noopener">
 <img width=200px height=200px src="lins355.png" alt="Project logo"></a>
</p>

<h3 align="center">LINS355 Acceleration Sensor</h3>

<div align="center">

[![Status](https://img.shields.io/badge/status-active-success.svg)]()
[![GitHub Issues](https://img.shields.io/badge/issues-0-yellow)](https://github.com/embed-coder/LINS355-accelerator/issues)
[![GitHub Pull Requests](https://img.shields.io/github/issues-pr/kylelobo/The-Documentation-Compendium.svg)](https://github.com/kylelobo/The-Documentation-Compendium/pulls)
[![License](https://img.shields.io/badge/license-MIT-blue.svg)](/LICENSE)

</div>

---

<p align="center"> Read acceleration data from sensor LINS355.
    <br> 
</p>

## 📝 Table of Contents

- [About](#about)
- [Getting Started](#getting_started)
- [Built](#build)
- [Deployment](#deployment)
- [Usage](#usage)
- [TODO](#todo)
- [Authors](#authors)

## 🧐 About <a name = "about"></a>

Get the sensor data and save it as a CSV file of the following format.

<table>
  <tr>
    <th>Timestamp (UTC)</th>
    <th>Acc_x</th>
    <th>Acc_y</th>
    <th>Acc_z</th>
  </tr>
  <tr>
    <th>1633436700083</th>
    <th>0.026935</th>
    <th>0.02394</th>
    <th>9.79528</th>
  </tr>
  <tr>
    <th>...</th>
    <th>...</th>
    <th>...</th>
    <th>...</th>
  </tr>
</table>

A new CSV file will be created every 5mins in a configurable path of your choice.

Each CSV file should contain all the 100Hz acceleration data within the 5mins span:

The naming convention of each file shall be:
acc_YYYYMMDD_hhmm.csv. For eg, “acc_20220609_1240.csv”

## 🏁 Getting Started <a name = "getting_started"></a>

Clone project from this repository or download the source files in compressed format in the list of release packages.

### Prerequisites

Dependencies:

- cmake
- libserial-dev
- googletest

Install dependency packages:

```
sudo apt update
sudo apt install -y gcc g++ git autogen autoconf build-essential \
                    cmake graphviz libgtest-dev libtool \
                    pkg-config libserial-dev
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
./test_lins355

```

### 🚀 Running SW

Run SW with the real device with format "./m2m-serial <device_file>"

```
./m2m-serial /dev/ttyUSB0
```

## 📝 Todo <a name="todo"></a>

Bucket list for the future features should be implemented for good:

- Get version from git tag for auto naming the output packages.

## ✍️ Authors <a name = "authors"></a>

- [@embedcoder](https://github.com/kylelobo) - Idea & Initial work
