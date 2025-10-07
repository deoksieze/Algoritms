#!/bin/bash

EXTENSIONS=(
"jock.svg"
"mushan.vscode-paste-image"
"naumovs.color-highlight"
"shardulm94.trailing-spaces"
"pkief.material-icon-theme"
"shahilkumar.docxreader"
"stkb.rewrap"
"usernamehw.errorlens"
"christian-kohler.path-intellisense"
"codezombiech.gitignore"
"eamodio.gitlens"
"lamartire.git-indicators"
"mhutchie.git-graph"
"qezhu.gitlink"
"zainchen.json"
"redhat.vscode-yaml"
"tamasfe.even-better-toml"
"davidanson.vscode-markdownlint"
"shd101wyy.markdown-preview-enhanced"
"yzhang.markdown-all-in-one"
"streetsidesoftware.code-spell-checker"
"streetsidesoftware.code-spell-checker-russian"
"sanaajani.taskrunnercode" 
"visualstudioexptteam.intellicode-api-usage-examples"
"visualstudioexptteam.vscodeintellicode"
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