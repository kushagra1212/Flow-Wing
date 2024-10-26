#!/bin/bash

INSTALL_DIR="/usr/local/flowwing"
LOG_FILE="/tmp/flowwing_install.log"

echo "Starting FlowWing installation..." | tee -a $LOG_FILE

# Create installation directories
echo "Creating installation directories..." | tee -a $LOG_FILE
if sudo mkdir -p $INSTALL_DIR/bin && sudo mkdir -p $INSTALL_DIR/lib/modules; then
    echo "Directories created successfully." | tee -a $LOG_FILE
else
    echo "Failed to create directories." | tee -a $LOG_FILE
    exit 1
fi

# Copy binaries
echo "Copying binaries..." | tee -a $LOG_FILE
if sudo cp bin/FlowWing $INSTALL_DIR/bin/ && \
   sudo cp bin/FlowWing-jit $INSTALL_DIR/bin/ && \
   sudo cp bin/FlowWing-repl $INSTALL_DIR/bin/; then
    echo "Binaries copied successfully." | tee -a $LOG_FILE
else
    echo "Failed to copy binaries." | tee -a $LOG_FILE
    exit 1
fi

# Copy libraries
echo "Copying libraries..." | tee -a $LOG_FILE
if sudo cp lib/*.a $INSTALL_DIR/lib/ && \
   sudo cp lib/*.so $INSTALL_DIR/lib/ && \
   sudo cp lib/*.bc $INSTALL_DIR/lib/; then
    echo "Libraries copied successfully." | tee -a $LOG_FILE
else
    echo "Failed to copy libraries." | tee -a $LOG_FILE
    exit 1
fi

# Copy modules
echo "Copying modules..." | tee -a $LOG_FILE
if sudo cp -r lib/modules/* $INSTALL_DIR/lib/modules/; then
    echo "Modules copied successfully." | tee -a $LOG_FILE
else
    echo "Failed to copy modules." | tee -a $LOG_FILE
    exit 1
fi

# Add FlowWing executables to PATH via symbolic links
echo "Adding FlowWing executables to PATH..." | tee -a $LOG_FILE
for cmd in FlowWing FlowWing-jit FlowWing-repl; do
    if sudo ln -sf "$INSTALL_DIR/bin/$cmd" /usr/local/bin/$cmd; then
        echo "$cmd added to /usr/local/bin." | tee -a $LOG_FILE
    else
        echo "Failed to link $cmd to /usr/local/bin." | tee -a $LOG_FILE
        exit 1
    fi
done

# Add FlowWing library path to the system library path
echo "Updating system library path..." | tee -a $LOG_FILE
echo "$INSTALL_DIR/lib" | sudo tee /etc/ld.so.conf.d/flowwing.conf > /dev/null
if sudo ldconfig; then
    echo "Library path updated successfully." | tee -a $LOG_FILE
else
    echo "Failed to update library path." | tee -a $LOG_FILE
    exit 1
fi

# Verify installation
echo "Verifying installation..." | tee -a $LOG_FILE
if $INSTALL_DIR/bin/FlowWing --version &> /dev/null; then
    echo "FlowWing installed successfully!" | tee -a $LOG_FILE
    echo "Run 'FlowWing --version' to confirm." | tee -a $LOG_FILE
else
    echo "Installation verification failed." | tee -a $LOG_FILE
    exit 1
fi
