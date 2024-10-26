#!/bin/bash

INSTALL_DIR="/usr/local/flowwing"
LOG_FILE="/tmp/flowwing_uninstall.log"
BINARY_NAMES=("FlowWing" "FlowWing-jit" "FlowWing-repl")
SYSTEM_PATHS=("/usr/local/bin" "/usr/bin" "/bin")

echo "Starting FlowWing uninstallation..." | tee -a $LOG_FILE

# Step 1: Remove symbolic links or binaries from common system paths
echo "Removing FlowWing binaries from system paths..." | tee -a $LOG_FILE
for binary in "${BINARY_NAMES[@]}"; do
    for path in "${SYSTEM_PATHS[@]}"; do
        if [ -f "$path/$binary" ]; then
            if sudo rm -f "$path/$binary"; then
                echo "Removed $binary from $path." | tee -a $LOG_FILE
            else
                echo "Failed to remove $binary from $path." | tee -a $LOG_FILE
            fi
        fi
    done
done

# Step 2: Remove the installation directory
echo "Removing installation directory and all binaries..." | tee -a $LOG_FILE
if sudo rm -rf "$INSTALL_DIR"; then
    echo "Installation directory removed successfully." | tee -a $LOG_FILE
else
    echo "Failed to remove the installation directory or it may not exist." | tee -a $LOG_FILE
fi

# Step 3: Clear PATH from shell profiles if FlowWing was added directly
echo "Checking for PATH entries in shell profiles..." | tee -a $LOG_FILE
for profile in ~/.bashrc ~/.bash_profile ~/.zshrc ~/.profile; do
    if [ -f "$profile" ]; then
        if grep -q "$INSTALL_DIR/bin" "$profile"; then
            echo "Removing FlowWing PATH entry from $profile" | tee -a $LOG_FILE
            sed -i.bak "/$INSTALL_DIR\/bin/d" "$profile" && rm -f "${profile}.bak"
            echo "PATH entry removed from $profile." | tee -a $LOG_FILE
        else
            echo "No FlowWing PATH entry found in $profile." | tee -a $LOG_FILE
        fi
    fi
done

# Step 4: Reset the shell to clear cached PATH
echo "Refreshing shell session to clear any cached PATH entries..." | tee -a $LOG_FILE
hash -r

# Step 5: Confirm uninstallation
for binary in "${BINARY_NAMES[@]}"; do
    if command -v "$binary" &>/dev/null; then
        echo "Warning: $binary is still accessible. Try restarting the terminal session or checking for other installations." | tee -a $LOG_FILE
    else
        echo "$binary successfully removed from the system." | tee -a $LOG_FILE
    fi
done

echo "FlowWing uninstallation process completed." | tee -a $LOG_FILE
