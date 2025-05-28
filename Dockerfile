FROM ubuntu:22.04

# Prevent interactive prompts during package installation
ENV DEBIAN_FRONTEND=noninteractive

# Update package list and install development tools
RUN apt-get update && apt-get install -y \
    build-essential \
    gcc \
    g++ \
    make \
    cmake \
    valgrind \
    gdb \
    git \
    vim \
    nano \
    less \
    tree \
    strace \
    ltrace \
    man-db \
    libc6-dev \
    && rm -rf /var/lib/apt/lists/*

# Set working directory
WORKDIR /workspace

# Display tool versions when container starts
RUN echo '#!/bin/bash' > /usr/local/bin/show-tools && \
    echo 'echo "=== Build Environment Ready ==="' >> /usr/local/bin/show-tools && \
    echo 'echo "Available tools:"' >> /usr/local/bin/show-tools && \
    echo 'echo "  - gcc: $(gcc --version | head -1)"' >> /usr/local/bin/show-tools && \
    echo 'echo "  - valgrind: $(valgrind --version)"' >> /usr/local/bin/show-tools && \
    echo 'echo "  - make: $(make --version | head -1)"' >> /usr/local/bin/show-tools && \
    echo 'echo ""' >> /usr/local/bin/show-tools && \
    echo 'echo "Project directory contents:"' >> /usr/local/bin/show-tools && \
    echo 'ls -la' >> /usr/local/bin/show-tools && \
    echo 'echo ""' >> /usr/local/bin/show-tools && \
    echo 'echo "Ready to build! Try:"' >> /usr/local/bin/show-tools && \
    echo 'echo "  make"' >> /usr/local/bin/show-tools && \
    echo 'echo "  valgrind --leak-check=full ./myprogram 1982"' >> /usr/local/bin/show-tools && \
    echo 'echo ""' >> /usr/local/bin/show-tools && \
    chmod +x /usr/local/bin/show-tools

# Default command
CMD ["/bin/bash", "-c", "show-tools && exec /bin/bash"]
