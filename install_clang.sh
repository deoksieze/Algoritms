

    CLANG_VERSION=20
     
    mkdir clang
    cd clang
    curl -O https://apt.llvm.org/llvm.sh # or wget
    chmod +x llvm.sh
    sudo ./llvm.sh -${CLANG_VERSION}
    sudo apt-get install \
      clangd-${CLANG_VERSION} \
      clang-tidy-${CLANG_VERSION} \
      clang-format-${CLANG_VERSION}
     
    sudo apt-get autoremove
    sudo update-alternatives --install /usr/bin/clang clang /usr/bin/clang-${CLANG_VERSION} ${CLANG_VERSION} \
      --slave /usr/bin/clang++ clang++ /usr/bin/clang++-${CLANG_VERSION} \
      --slave /usr/bin/clang-tidy clang-tidy /usr/bin/clang-tidy-${CLANG_VERSION} \
      --slave /usr/bin/clang-format clang-format /usr/bin/clang-format-${CLANG_VERSION} \
      --slave /usr/bin/clangd clangd /usr/bin/clangd-${CLANG_VERSION}

