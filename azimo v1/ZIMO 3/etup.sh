#!/bin/bash
echo "Configurando o ambiente para o projeto Nordic 7 NSC..."

# Verifica se o Lua está instalado
if ! command -v lua &> /dev/null
then
    echo "Lua não encontrado. Instalando Lua..."
    sudo apt-get install lua5.3
fi

echo "Instalação concluída. Ambiente configurado."
