-- Criar a tabela de usuários
CREATE TABLE Users (
    user_id SERIAL PRIMARY KEY,
    username VARCHAR(50) NOT NULL UNIQUE,
    password VARCHAR(100) NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- Criar a tabela de sessões SSH
CREATE TABLE SSHSessions (
    session_id SERIAL PRIMARY KEY,
    user_id INT REFERENCES Users(user_id),
    ip_address VARCHAR(45) NOT NULL,
    session_start TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    session_end TIMESTAMP,
    status VARCHAR(20) DEFAULT 'active'
);

-- Criar a tabela de kernels
CREATE TABLE Kernels (
    kernel_id SERIAL PRIMARY KEY,
    kernel_name VARCHAR(50) NOT NULL,
    kernel_version VARCHAR(20) NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    status VARCHAR(20) DEFAULT 'active'
);

-- Criar a tabela de lakes
CREATE TABLE Lakes (
    lake_id SERIAL PRIMARY KEY,
    lake_name VARCHAR(50) NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- Criar a tabela de objetos dentro de cada lake
CREATE TABLE HoloFiObjects (
    object_id SERIAL PRIMARY KEY,
    lake_id INT REFERENCES Lakes(lake_id),
    object_name VARCHAR(50) NOT NULL,
    attribute FLOAT,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- Criar a tabela para armazenar logs de ações
CREATE TABLE ActionLogs (
    log_id SERIAL PRIMARY KEY,
    user_id INT REFERENCES Users(user_id),
    action VARCHAR(255),
    timestamp TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);
