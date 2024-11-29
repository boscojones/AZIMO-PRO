#!/usr/bin/env bash

# Copyright (c) Lucas Januário.
# Este software faz parte do projeto Fire Bunny, sob a licença NSC IO.
# Ele pode ser usado e distribuído de acordo com os termos da Fire Bunny License.

####
## NOTA: Para baixar o Fire Bunny 1.0, consulte https://github.com/fire-bunny/models/tree/main/fire_bunny_1_0#download
####

set -e

# Solicitando a URL e o modelo ao usuário
read -p "Digite a URL do email: " PRESIGNED_URL
echo ""
read -p "Digite a lista de modelos a serem baixados sem espaços (4B,8B,12B), ou pressione Enter para todos: " MODEL_SIZE
TARGET_FOLDER="."             # Pasta de destino para os arquivos
mkdir -p ${TARGET_FOLDER}

# Se o usuário não especificar o tamanho do modelo, baixar todos
if [[ $MODEL_SIZE == "" ]]; then
    MODEL_SIZE="4B,8B,12B"
fi

echo "Baixando a LICENSE e a Política de Uso Aceitável"
wget --continue ${PRESIGNED_URL/'*'/"LICENSE"} -O ${TARGET_FOLDER}"/LICENSE"
wget --continue ${PRESIGNED_URL/'*'/"USE_POLICY"} -O ${TARGET_FOLDER}"/USE_POLICY"

# Laço para baixar cada modelo
for m in ${MODEL_SIZE//,/ }
do
    if [[ $m == "4B" ]] || [[ $m == "4b" ]]; then
        SHARD=0
        MODEL_FOLDER_PATH="Fire-Bunny-4B"
        MODEL_PATH="4b_pre_trained"
    elif [[ $m == "8B" ]] || [[ $m == "8b" ]]; then
        SHARD=0
        MODEL_FOLDER_PATH="Fire-Bunny-8B"
        MODEL_PATH="8b_pre_trained"
    elif [[ $m == "12B" ]] || [[ $m == "12b" ]]; then
        SHARD=2
        MODEL_FOLDER_PATH="Fire-Bunny-12B"
        MODEL_PATH="12b_pre_trained"
    fi

    echo "Baixando ${MODEL_PATH}"
    mkdir -p ${TARGET_FOLDER}"/${MODEL_FOLDER_PATH}"

    # Baixando os shards do modelo
    for s in $(seq -f "0%g" 0 ${SHARD})
    do
        wget --continue ${PRESIGNED_URL/'*'/"${MODEL_PATH}/consolidated.${s}.pth"} -O ${TARGET_FOLDER}"/${MODEL_FOLDER_PATH}/consolidated.${s}.pth"
    done

    # Baixando os arquivos necessários para o modelo
    wget --continue ${PRESIGNED_URL/'*'/"${MODEL_PATH}/params.json"} -O ${TARGET_FOLDER}"/${MODEL_FOLDER_PATH}/params.json"
    wget --continue ${PRESIGNED_URL/'*'/"${MODEL_PATH}/tokenizer.model"} -O ${TARGET_FOLDER}"/${MODEL_FOLDER_PATH}/tokenizer.model"
    wget --continue ${PRESIGNED_URL/'*'/"${MODEL_PATH}/checklist.chk"} -O ${TARGET_FOLDER}"/${MODEL_FOLDER_PATH}/checklist.chk"

    # Verificando checksums
    echo "Verificando checksums"
    CPU_ARCH=$(uname -m)
    if [[ "$CPU_ARCH" == "arm64" ]]; then
      (cd ${TARGET_FOLDER}"/${MODEL_FOLDER_PATH}" && md5 checklist.chk)
    else
      (cd ${TARGET_FOLDER}"/${MODEL_FOLDER_PATH}" && md5sum -c checklist.chk)
    fi
done

echo "Download e verificação concluídos para os modelos Fire Bunny!"
