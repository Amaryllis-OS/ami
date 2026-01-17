# AMI

AMI is a low-level package installer for Amaryllis OS, focused on speed, simplicity, and static linking for reliable system bootstrap.

## Recommended Build Method (Using Docker)

To ensure a consistent build environment, it is recommended to use Docker for building AMI. The following steps will guide you through building the Docker image and compiling AMI inside the container.

### 1. Build the Docker Image

From the project root directory, build the Docker image:

```sh
docker build -t ami-build .
```

### 2. Run the Build in the Docker Container

Start a container from the built image, mounting your project directory:

```sh
docker run --rm -it -v "$PWD":/workspace -w /workspace ami-build bash
```

### 3. Run `cmate` Inside the Container

Before building, run the `cmate` command inside the Docker container to generate the necessary build files:

```sh
cmate
```

### 4. Build the Project

After running `cmate`, build the project: 

```sh
make
```

## License

This project is licensed under the terms of the LICENSE file in this repository.
