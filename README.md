<img width="410" src="weder-logo.png" alt="weder">

<hr>

[![License](https://img.shields.io/badge/License-Apache%202.0-orange.svg)](https://opensource.org/licenses/Apache-2.0)
[![Language](https://img.shields.io/badge/language-C++-blue.svg)](https://isocpp.org/)
[![Standard](https://img.shields.io/badge/c%2B%2B-20-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B17)
[![Version](https://badge.fury.io/gh/brianjgamble%2Fweder.svg)](https://github.com/brianjgamble/weder/releases)

Command-line weather using the Open Weather API

## Example

Get the current conditions by zip code:

```shell script
weder --zip 12345 --apiKey abcdef12345
```

### Default Values

To avoid passing the zip and api key, store them in a configuration file named `.weder.json` within the home directory.  

```json
{
  "zip": 12345,
  "apiKey": "abcdef12345"
}
```


## Build

### Requiremens for Building
- C++20
- [CMake](https://cmake.org)
- [Conan](https://conan.io)

### Instructions

To build the project via CMake:

```
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
```

## Links
[Open Weather API](https://openweathermap.org)

## Contact
Created by [@brianjgamble](http://brianjgamble.com/)
