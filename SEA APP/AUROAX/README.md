
# 🍄Nebula X UTX🍄 


Nebula X UTX é um projeto inovador que visa criar uma plataforma robusta para transações baseadas em UTXO (Unspent Transaction Output). Com foco em segurança, escalabilidade e facilidade de uso, Nebula X UTX permite que desenvolvedores e usuários finais interajam com uma rede descentralizada de forma eficiente.


## Instalação

Para começar a trabalhar com o Nebula X UTX, siga as instruções abaixo:

### Pré-requisitos

- Python 3.x instalado. Você pode baixar o Python do [site oficial](https://www.python.org/downloads/).
- PostgreSQL instalado e configurado. Consulte a [documentação do PostgreSQL](https://www.postgresql.org/docs/) para instalação.

### Clonando o Repositório

```bash
git clone https://github.com/seuusuario/nebula-x-utx.git
cd nebula-x-utx
```

### Dependências

Instale as dependências necessárias utilizando o comando:

```bash
pip install -r requirements.txt
```

### Configuração do Banco de Dados

1. Crie um banco de dados no PostgreSQL.
2. Edite o arquivo `.env` com as credenciais do seu banco de dados.

## Executando o Projeto

Para iniciar a aplicação, use o seguinte comando:

```bash
python app.py
```

A aplicação estará disponível em `http://localhost:5000`.

## API

### POST /transaction

Este endpoint permite que você envie uma nova transação.

#### Exemplo de Requisição

```bash
curl -X POST http://localhost:5000/transaction -H "Content-Type: application/json" -d '{"from": "endereco_de_origem", "to": "endereco_de_destino", "amount": "valor"}'
```

#### Resposta

- **201 Created**: Retorna detalhes da transação criada.
- **400 Bad Request**: Retorna um erro se a requisição estiver malformada.
- **500 Internal Server Error**: Retorna um erro se houver um problema ao processar a transação.

### Exemplo de Resposta

```json
{
  "transaction_id": "12345",
  "status": "success",
  "message": "Transação criada com sucesso."
}
```

## Contribuição

Contribuições são bem-vindas! Para contribuir, siga estas etapas:

1. Faça um fork do projeto.
2. Crie sua feature branch (`git checkout -b feature/AmazingFeature`).
3. Faça o commit das suas mudanças (`git commit -m 'Add some AmazingFeature'`).
4. Envie para o branch original (`git push origin feature/AmazingFeature`).

## Licença

Este projeto é licenciado sob a [Apache License 2.0](https://www.apache.org/licenses/LICENSE-2.0). Consulte o arquivo [LICENSE](LICENSE) para mais detalhes.

