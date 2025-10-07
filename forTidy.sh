# create_contest.sh
#!/bin/bash
mkdir -p "$1"
cd "$1"
cat > compile_commands.json << EOF
[
  {
    "directory": "$(pwd)",
    "command": "clang++ -std=c++17 -Wall -Wextra -I. -I.. *.cpp -o program",
    "file": "*.cpp"
  }
]
EOF
