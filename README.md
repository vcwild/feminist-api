# The Feminist API

The Feminist API is a RESTful API implementation that provides access to randomly generated feminist quotes.

This idea was originally proposed by [Patricia Parra](https://twitter.com/pachicodes). Thanks for the inspiration!

## Tech stack

- GNU Make
- ANSI C
- Mongoose web server
- OpenSSL

## How to run

- Clone this repository

- Test the server execution with `make run`.

### Development server

Please, follow the instructions below if you intend to develop for this application.

For the development server, run the following instructions:

- Run `make` to build the server

- Temporarily update your path to include the current program build.

```sh
export PATH=$PATH:$(pwd)
```

- Now run the program by executing the `feminist_api` command.

### Installing the program

- You can install the program with `make install`.

### Security (optional step)

This application also supports HTTPS via SSL and TLS.

You will need to install TLS libraries for your distribution:

#### Debian/Ubuntu

sudo apt-get install libssl-dev libmbedtls-dev

#### Fedora/RHEL/CentOS

```sh
sudo yum install openssl-devel mbedtls-devel
```

Other distributions may require different libraries, please check the documentation of your package manager.

After installation, you can compile the dependencies and run the server as previosly mentioned by using `make`.
