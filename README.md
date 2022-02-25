<div>
  <p align="center">
    <img src=".github/static/img/rosie.png" width="200px">
  </p>
</div>

The Feminist API is a RESTful API implementation that provides access to randomly generated feminist quotes.

This idea was originally proposed by [Patricia Parra](https://twitter.com/pachicodes). Thanks for the inspiration!

## Table of contents

- [Tech stack](#tech-stack)
- [How to run](#how-to-run)
- [How to develop](#development-builds)
- [How to use the CLI](#using-the-cli)
- [Install the program](#install-the-program)
- [API declaration](docs/api.md)
- [Contribute](#contribute)
- [License](#LICENSE)

## Tech stack

- ANSI C
- Docker
- GNU Make
- Mongoose web server
- OpenSSL

## How to run

If you want to try out the application you can run the server as a docker container. This step assumes that you have [Docker](https://docs.docker.com/engine/install/) installed.

### Method 1 - Use our container build

 Simply pull the image from our Docker Hub registry:

```sh
# Create a docker container with the application `feminist_api`
docker run -p 8080:8000 -d --name feminist_api vcwild/feminist_api:latest

# Open the application in your browser
xdg-open http://localhost:8080
```

If you want to know how to use the CLI tool, you can check [this topic](#using-the-cli).

### Method 2 - Manual build

If you feel like it, you can build the container yourself:

```sh
docker build . -t vcwild/feminist_api:latest
```

Now you can run the container, as [previosly mentioned](#method-1---use-our-container-build).

## How to develop

Please, follow the instructions below only if you intend to develop for this application.

### Requirements

The current instance of the Feminist API project is only supported on Linux distributions.

In order to compile and run the server, it is strongly recommended to get at least a **build-essential** or equivalent package module, although it might not be required, depending on your system.

#### DevTools for Debian/Ubuntu

In order to install the build essentials, run the following command:

```sh
sudo apt-get install build-essential
```

#### DevTools for Fedora/RHEL/CentOS

The Fedora/RHEL/CentOS equivalent to the above is:

```sh
sudo yum install make automake gcc gcc-c++ kernel-devel
```

Other distributions may require different libraries, please check the documentation of your package manager.

### Development server

Follow along these steps:

- Clone this repository

- Test the server execution with `make run`.

- Go to the root of your git clone

- Run `make` to build the server

- **IMPORTANT:** temporarily update your path to include the current program build.

```sh
export PATH=$PATH:$(pwd)
```

- Now run the program by executing the `feminist_api` command.

This command will bind your terminal to the server and wait for requests.

You can also run this as a background process:

```sh
feminist_api &
```

In this case, you can end the process with the following command:

```sh
kill $(pgrep feminist_api)
```

### Security (optional step)

This application also supports HTTPS via SSL and TLS.

You will need to install TLS libraries for your distribution:

#### Security for Debian/Ubuntu

```sh
sudo apt-get install libssl-dev libmbedtls-dev
```

#### Security for Fedora/RHEL/CentOS

```sh
sudo yum install openssl-devel mbedtls-devel
```

Other distributions may require different libraries, please check the documentation of your package manager.

After the installation, you can compile the dependencies and run the server as previosly mentioned [here](#development-server), but with the caveat that you need to add the TLS libraries to your execution:

```sh
make MBEDTLS_DIR=/your/path/to/mbedtls
```

## Using the CLI

The server logs can be accessed via the `ada` command line interface. This step assumes that the server is already running.

### Running the CLI from within a docker container

This step assumes that you already have the [server running in a docker container](#how-to-run).

Execute `ada` commands through the docker interface:

```sh
docker exec -it feminist_api ada --help
```

You can also make an alias for that, to make this process easier:

```sh
alias ada="docker exec -it feminist_api ada"
```

Now you can run the CLI as if you were running it from your own terminal:

```sh
ada --help
```

### Running the CLI locally

This step assumes that you followed the [how to develop](#how-to-develop) guide.

Update your path with the current directory if you don't have it already:

```sh
export PATH=$PATH:$(pwd)
```

Simply execute any CLI interaction by using the `ada` command.

```sh
# e.g. get help from the CLI
ada --help
```

## Install the program

- It is also possible to install the program with `make install`. This will add the `feminist_api` server and the `ada` CLI to the `/usr/local/bin` directory permanently.

## Contribute

Enjoyed the application? Please, consider contributing to the project.

## License

This project is under the [GNU General Public License v3](LICENSE).
