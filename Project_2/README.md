# Project 2 – Scan Directories

## Overview
This program recursively scans a directory hierarchy and computes the total size of all regular files in each directory. It ignores symbolic links and other non-regular file types. Directory totals are printed in post-order so that subdirectories appear before their parent directories.

## Diagram
target_directory (parent, i.e. '..')
    ├── scan_directory (recursive)
    └── current_dir