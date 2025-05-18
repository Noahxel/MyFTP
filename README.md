# MyFTP - File Transfer Protocol Server

A custom implementation of an FTP server in C, following the RFC959 specification. This server supports both active and passive modes for data transfer, along with essential FTP commands.

## Project Overview

MyFTP is a lightweight FTP server that implements core FTP functionality:
- User authentication
- File operations (upload, download, delete)
- Directory navigation
- Both active and passive transfer modes
- Command-response protocol following RFC959

## Project Structure

```
MyFTP/
├── src/
│   ├── main.c                  # Program entry point
│   ├── server.c                # Server implementation
│   ├── auth.c                  # Authentication handling
│   ├── clients_requests.c      # Client request processing
│   ├── port.c                  # Active mode implementation
│   ├── pasv.c                  # Passive mode implementation
│   ├── directory.c             # Directory operations
│   ├── dele.c                  # File deletion operations
│   └── misc_fctns.c           # Utility functions
├── includes/                   # Header files
└── Makefile                    # Build configuration
```

## Building the Project

To compile the server:

```bash
make
```

This will generate the `myftp` executable.

## Usage

### Starting the Server

```bash
./myftp port path
```

Parameters:
- `port`: The port number on which the server should listen
- `path`: The path to the server's root directory

Example:
```bash
./myftp 2121 /home/ftp/
```

### Supported Commands

The server supports the following FTP commands:

| Command | Description |
|---------|-------------|
| USER | Specify username for authentication |
| PASS | Specify password for authentication |
| QUIT | Disconnect from server |
| PORT | Enable "active" mode for data transfer |
| PASV | Enable "passive" mode for data transfer |
| PWD  | Print working directory |
| CWD  | Change working directory |
| DELE | Delete file |
| HELP | List available commands |
| NOOP | Do nothing (keep-alive) |

## Features

### Authentication
- Basic username/password authentication
- Anonymous access support
- Session management

### Transfer Modes
- Active (PORT) mode support
- Passive (PASV) mode support
- Secure data transfer handling

### File Operations
- Directory navigation
- File deletion
- Working directory management

## Implementation Details

The server is implemented with:
- Non-blocking socket I/O
- Multi-client support
- RFC959-compliant response codes
- Robust error handling
- Clean session management

## Error Handling

The server includes error handling for:
- Invalid commands
- Authentication failures
- File operation errors
- Network connection issues
- Permission violations

## Building and Cleaning

Available make targets:
- `make`: Build the server
- `make clean`: Remove object files
- `make fclean`: Remove object files and executable
- `make re`: Rebuild the project

## License

This project is licensed under the terms provided in the LICENSE file.

## Contributing

Contributions are welcome! Feel free to submit issues and pull requests. 