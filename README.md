# Simple Web Scraper

This is a simple web scraper written in C++ that uses `libcurl` and `Gumbo` to fetch and parse HTML.
I'm not really into CMake so everything was included manually.

## Requirements

- `libcurl`
- `Gumbo`

If using CLion, just install them with vcpkg and specify the path as in 'CMakeLists.txt'.

## Usage

1) Run a compiled binary in Linux:
```bash
$ ./SimpleWebScraper
```

2) Build yourself with example 'CMakeLists.txt' if you have dependences installed on your system:

```bash
mkdir build
cd build
cmake ..
make
```
