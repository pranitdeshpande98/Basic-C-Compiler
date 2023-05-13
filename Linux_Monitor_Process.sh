#!/bin/bash

# Define a function to display process information
display_process_info() {
    pid=$1
    user=$(ps -o user= -p "$pid")
    cpu=$(ps -o %cpu= -p "$pid")
    mem=$(ps -o %mem= -p "$pid")
    command=$(ps -o comm= -p "$pid")

    printf "%-10s %-10s %-10s %-10s\n" "$pid" "$user" "$cpu" "$mem"
}

# Get the list of running processes and display their information
echo "PID        USER       CPU        MEMORY"
echo "======================================"
while read -r pid; do
    display_process_info "$pid"
done < <(ps -eo pid=)
