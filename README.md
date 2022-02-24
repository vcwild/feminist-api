# The Feminist API

The Feminist API is a RESTful API implementation that provides access to randomly generated feminist quotes.

This idea was originally proposed by [Patricia Parra](https://twitter.com/pachicodes). Thanks for the inspiration!

## Tech stack

- GNU Make
- ANSI C
- Mongoose web server
- OpenSSL

## Requirements

The current instance of the Feminist API project is only supported on Linux distributions.

In order to compile and run the server, it is strongly recommended to get at least a **build-essential** or equivalent package module, although it might not be required, depending on your system.

### DevTools for Debian/Ubuntu

In order to install the build essentials, run the following command:

```sh
sudo apt-get install build-essential
```

### DevTools for Fedora/RHEL/CentOS

The Fedora/RHEL/CentOS equivalent to the above is:

```sh
sudo yum install make automake gcc gcc-c++ kernel-devel
```

Other distributions may require different libraries, please check the documentation of your package manager.

## How to run

- Clone this repository

- Test the server execution with `make run`.

### Development server

Please, follow the instructions below if you intend to develop for this application.

- Go to the root of your git clone

- Run `make` to build the server

- **IMPORTANT:** temporarily update your path to include the current program build.

```sh
export PATH=$PATH:$(pwd)
```

- Now run the program by executing the `feminist_api` command.

This command will bind your terminal to the server and wait for requests.

You can also run this as a background proccess:

```sh
feminist_api &
```

In this case, you can catch the proccess ID with the following command:

```sh
pgrep feminist_api
```

### Installing the program

- It is also possible to install the program with `make install`. This will add the `feminist_api` server and the `ada` CLI to the `/usr/local/bin` directory.

### Security (optional step)

This application also supports HTTPS via SSL and TLS.

You will need to install TLS libraries for your distribution:

#### Security for Debian/Ubuntu

sudo apt-get install libssl-dev libmbedtls-dev

#### Security for Fedora/RHEL/CentOS

```sh
sudo yum install openssl-devel mbedtls-devel
```

Other distributions may require different libraries, please check the documentation of your package manager.

After installation, you can compile the dependencies and run the server as previosly mentioned [here](#development-server).

## Using the CLI

The server logs can be accessed via the `ada` command line interface. This step assumes that the server is already running and your [environment path is configured](#development-server).

Please follow the steps below:

- Compile the dependencies with `make cli`.

Now simply execute any CLI interaction by using the `ada` command.

```sh
# e.g. get help from the CLI
ada --help
```
