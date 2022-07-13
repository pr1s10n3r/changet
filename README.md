# changet

Very minimalist utility console program for 4chan threads downloading.

## Dependencies

- [meson](https://mesonbuild.com/index.html) as the build system.
- [libcurl](https://curl.se/libcurl/) for http requests.
- [json-c](https://github.com/json-c/json-c) for JSON parsing.

### Fedora Distributions:

```sh
sudo dnf install meson ninja-build libcurl-devel json-c-devel
```

### Debian Distributions:

```sh
sudo apt install meson ninja-build libcurl-dev libjson-c-dev
```

## Build

```sh
# generate required files for project building
meson target
```

```sh
# build the project
meson build -C target
```

## License

See [LICENSE](./LICENSE) file.

