
EXTENSIONS=(
"llvm-vs-code-extensions.vscode-clangd"
"ms-vscode.cpptools"
"ms-vscode.cpptools-extension-pack"
"ms-vscode.cpptools-themes"
"vadimcn.vscode-lldb"
"xaver.clang-format"
"matepek.vscode-catch2-test-adapter"
"franneck94.c-cpp-runner"
"danielpinto8zz6.c-cpp-compile-run"
"formulahendry.code-runner"
"cschlosser.doxdocgen"
)

for extension in "${EXTENSIONS[@]}"; do
    echo "=== Установка: $extension ==="
    if code --install-extension "$extension"; then
        echo "✓ Успешно: $extension"
    else
        echo "✗ Ошибка: $extension"
    fi
    echo
done

echo "Установка завершена!"