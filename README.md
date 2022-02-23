# The Feminist API

The Feminist API is a RESTful API implementation that provides access to randomly generated feminist quotes.

This idea was originally proposed by [@PachiCodes](https://twitter.com/pachicodes). Thanks for the inspiration!

## Tech stack

- GNU Make
- ANSI C
- Mongoose web server
- OpenSSL

## How to run as a development server

Please, follow the instructions below if you intend to develop for this application.

For the development server, run the following instructions:

- Clone this repository

Run `make` to build the server.

Make will take care of compiling the server dependencies and will also start the server as well.

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
