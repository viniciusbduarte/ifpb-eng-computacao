-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Tempo de geração: 12/12/2025 às 00:20
-- Versão do servidor: 10.4.32-MariaDB
-- Versão do PHP: 8.0.30

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Banco de dados: `santosfc`
--

-- --------------------------------------------------------

--
-- Estrutura para tabela `analisa`
--

CREATE TABLE `analisa` (
  `CPF_CT_FK` varchar(20) DEFAULT NULL,
  `Cod_BID_FK` int(11) DEFAULT NULL,
  `Data` date DEFAULT NULL,
  `Resultado` varchar(20) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Despejando dados para a tabela `analisa`
--

INSERT INTO `analisa` (`CPF_CT_FK`, `Cod_BID_FK`, `Data`, `Resultado`) VALUES
('44444444444', 1, '2025-01-06', 'Apto'),
('44444444444', 2, '2025-01-06', 'Apto'),
('44444444444', 3, '2025-01-06', 'Apto');

-- --------------------------------------------------------

--
-- Estrutura para tabela `colaborador`
--

CREATE TABLE `colaborador` (
  `CPF` varchar(20) NOT NULL,
  `Nome` varchar(100) DEFAULT NULL,
  `Data_Nasc` date DEFAULT NULL,
  `Salario` decimal(10,2) DEFAULT NULL,
  `CPF_Gerente_FK` varchar(20) DEFAULT NULL,
  `Cod_Dpto_FK` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Despejando dados para a tabela `colaborador`
--

INSERT INTO `colaborador` (`CPF`, `Nome`, `Data_Nasc`, `Salario`, `CPF_Gerente_FK`, `Cod_Dpto_FK`) VALUES
('22222222222', 'Paulo Oliveira', '1985-02-02', 12000.00, '11111111111', 1),
('33333333333', 'Marcelo Braga', '1984-05-15', 18000.00, '11111111111', 2),
('44444444444', 'Renato Vieira', '1978-10-20', 20000.00, '11111111111', 3);

-- --------------------------------------------------------

--
-- Estrutura para tabela `contrato`
--

CREATE TABLE `contrato` (
  `Codigo` int(11) NOT NULL,
  `Data` date DEFAULT NULL,
  `TempoContrato` int(11) DEFAULT NULL,
  `Cod_Presidente_FK` varchar(20) DEFAULT NULL,
  `Cod_BID_FK` int(11) DEFAULT NULL,
  `Resultado` varchar(20) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Despejando dados para a tabela `contrato`
--

INSERT INTO `contrato` (`Codigo`, `Data`, `TempoContrato`, `Cod_Presidente_FK`, `Cod_BID_FK`, `Resultado`) VALUES
(1, '2025-01-10', 24, '900100200', 1, 'Aprovado'),
(2, '2025-01-10', 24, '900100200', 2, 'Aprovado'),
(3, '2025-01-10', 24, '900100200', 3, 'Aprovado'),
(4, '2025-01-10', 24, '900100200', 4, 'Aprovado'),
(5, '2025-01-10', 24, '900100200', 5, 'Aprovado'),
(6, '2025-01-10', 24, '900100200', 6, 'Aprovado'),
(7, '2025-01-10', 12, '900100200', 7, 'Aprovado'),
(8, '2025-01-10', 12, '900100200', 8, 'Aprovado'),
(9, '2025-01-10', 36, '900100200', 9, 'Aprovado'),
(10, '2025-01-10', 36, '900100200', 10, 'Aprovado'),
(11, '2025-01-10', 36, '900100200', 11, 'Aprovado'),
(12, '2025-01-10', 36, '900100200', 12, 'Aprovado'),
(13, '2025-01-10', 36, '900100200', 13, 'Aprovado'),
(14, '2025-01-10', 36, '900100200', 14, 'Aprovado'),
(15, '2025-01-10', 36, '900100200', 15, 'Aprovado');

-- --------------------------------------------------------

--
-- Estrutura para tabela `departamento`
--

CREATE TABLE `departamento` (
  `Codigo` int(11) NOT NULL,
  `Nome` varchar(50) DEFAULT NULL,
  `VerbaAnual` decimal(12,2) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Despejando dados para a tabela `departamento`
--

INSERT INTO `departamento` (`Codigo`, `Nome`, `VerbaAnual`) VALUES
(1, 'Scouting', 500000.00),
(2, 'Medico', 800000.00),
(3, 'Comissao Tecnica', 1200000.00);

-- --------------------------------------------------------

--
-- Estrutura para tabela `departamento_avalia_contrato`
--

CREATE TABLE `departamento_avalia_contrato` (
  `Cod_Dpto_FK` int(11) DEFAULT NULL,
  `Cod_Contrato_FK` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Despejando dados para a tabela `departamento_avalia_contrato`
--

INSERT INTO `departamento_avalia_contrato` (`Cod_Dpto_FK`, `Cod_Contrato_FK`) VALUES
(1, 1),
(2, 1),
(3, 1),
(1, 2),
(2, 2),
(3, 2),
(1, 3),
(2, 3),
(3, 3),
(1, 4),
(2, 4),
(3, 4),
(1, 5),
(2, 5),
(3, 5),
(1, 6),
(2, 6),
(3, 6),
(1, 7),
(2, 7),
(3, 7),
(1, 8),
(2, 8),
(3, 8),
(1, 9),
(2, 9),
(3, 9),
(1, 10),
(2, 10),
(3, 10),
(1, 11),
(2, 11),
(3, 11),
(1, 12),
(2, 12),
(3, 12),
(1, 13),
(2, 13),
(3, 13),
(1, 14),
(2, 14),
(3, 14),
(1, 15),
(2, 15),
(3, 15);

-- --------------------------------------------------------

--
-- Estrutura para tabela `dirigente`
--

CREATE TABLE `dirigente` (
  `Nome` varchar(100) DEFAULT NULL,
  `Cod_CBF` varchar(20) NOT NULL,
  `Inicio_Mandato` date DEFAULT NULL,
  `Fim_Mandato` date DEFAULT NULL,
  `Salario` decimal(10,2) DEFAULT NULL,
  `Cod_CG_FK` varchar(20) DEFAULT NULL,
  `CPF_Gerente_FK` varchar(20) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Despejando dados para a tabela `dirigente`
--

INSERT INTO `dirigente` (`Nome`, `Cod_CBF`, `Inicio_Mandato`, `Fim_Mandato`, `Salario`, `Cod_CG_FK`, `CPF_Gerente_FK`) VALUES
('Jo?o Alc?ntara', '900100200', '2024-01-01', '2027-12-31', 45000.00, NULL, '11111111111'),
('Ricardo Freitas', '900100201', '2024-01-01', '2027-12-31', 40000.00, NULL, '11111111111');

-- --------------------------------------------------------

--
-- Estrutura para tabela `equipe`
--

CREATE TABLE `equipe` (
  `Codigo` int(11) NOT NULL,
  `ValorMercado` decimal(12,2) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Despejando dados para a tabela `equipe`
--

INSERT INTO `equipe` (`Codigo`, `ValorMercado`) VALUES
(1, 50000000.00);

-- --------------------------------------------------------

--
-- Estrutura para tabela `examina`
--

CREATE TABLE `examina` (
  `CPF_Medico_FK` varchar(20) DEFAULT NULL,
  `Cod_BID_FK` int(11) DEFAULT NULL,
  `Data` date DEFAULT NULL,
  `Resultado` varchar(20) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Despejando dados para a tabela `examina`
--

INSERT INTO `examina` (`CPF_Medico_FK`, `Cod_BID_FK`, `Data`, `Resultado`) VALUES
('33333333333', 1, '2025-01-07', 'OK'),
('33333333333', 2, '2025-01-07', 'OK'),
('33333333333', 3, '2025-01-07', 'OK');

-- --------------------------------------------------------

--
-- Estrutura para tabela `gerente`
--

CREATE TABLE `gerente` (
  `CPF` varchar(20) NOT NULL,
  `Nome` varchar(100) DEFAULT NULL,
  `Data_Nasc` date DEFAULT NULL,
  `Salario` decimal(10,2) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Despejando dados para a tabela `gerente`
--

INSERT INTO `gerente` (`CPF`, `Nome`, `Data_Nasc`, `Salario`) VALUES
('11111111111', 'Carlos Menezes', '1975-04-10', 25000.00);

-- --------------------------------------------------------

--
-- Estrutura para tabela `jogador`
--

CREATE TABLE `jogador` (
  `Cod_BID` int(11) NOT NULL,
  `Nome` varchar(100) DEFAULT NULL,
  `Numero` int(11) DEFAULT NULL,
  `Data_Nasc` date DEFAULT NULL,
  `ValorMercado` decimal(12,2) DEFAULT NULL,
  `Cod_Equipe` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Despejando dados para a tabela `jogador`
--

INSERT INTO `jogador` (`Cod_BID`, `Nome`, `Numero`, `Data_Nasc`, `ValorMercado`, `Cod_Equipe`) VALUES
(1, 'Gabriel Barbosa', 10, '1996-08-30', 20000000.00, 1),
(2, 'Pedro Rocha', 11, '1994-10-01', 15000000.00, 1),
(3, 'Arrascaeta', 14, '1994-06-01', 30000000.00, 1),
(4, 'Bruno Henrique', 27, '1990-12-30', 18000000.00, 1),
(5, 'Everton Ribeiro', 7, '1989-04-10', 12000000.00, 1),
(6, 'Thiago Maia', 8, '1997-03-23', 10000000.00, 1),
(7, 'David Luiz', 23, '1987-04-22', 5000000.00, 1),
(8, 'Pablo Mar?', 4, '1993-08-31', 8000000.00, 1),
(9, 'Gerson Santos', 20, '1997-05-20', 25000000.00, 1),
(10, 'Luiz Ara?jo', 17, '1996-06-02', 9000000.00, 1),
(11, 'Ayrton Lucas', 6, '1997-06-19', 7000000.00, 1),
(12, 'Matheuzinho', 34, '2000-09-08', 6000000.00, 1),
(13, 'Varela', 2, '1998-03-24', 6000000.00, 1),
(14, 'Wesley Fran?a', 43, '2003-03-06', 4000000.00, 1),
(15, 'Victor Hugo', 29, '2004-06-11', 5000000.00, 1);

-- --------------------------------------------------------

--
-- Estrutura para tabela `medico`
--

CREATE TABLE `medico` (
  `CPF_FK` varchar(20) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Despejando dados para a tabela `medico`
--

INSERT INTO `medico` (`CPF_FK`) VALUES
('33333333333');

-- --------------------------------------------------------

--
-- Estrutura para tabela `membcomissaotec`
--

CREATE TABLE `membcomissaotec` (
  `CPF_FK` varchar(20) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Despejando dados para a tabela `membcomissaotec`
--

INSERT INTO `membcomissaotec` (`CPF_FK`) VALUES
('44444444444');

-- --------------------------------------------------------

--
-- Estrutura para tabela `posicao`
--

CREATE TABLE `posicao` (
  `Cod_BID_FK` int(11) DEFAULT NULL,
  `NomePosicao` varchar(50) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Despejando dados para a tabela `posicao`
--

INSERT INTO `posicao` (`Cod_BID_FK`, `NomePosicao`) VALUES
(1, 'Atacante'),
(2, 'Atacante'),
(3, 'Meia'),
(4, 'Atacante'),
(5, 'Meia'),
(6, 'Volante'),
(7, 'Zagueiro'),
(8, 'Zagueiro'),
(9, 'Volante'),
(10, 'Atacante'),
(11, 'Lateral'),
(12, 'Lateral'),
(13, 'Lateral'),
(14, 'Atacante'),
(15, 'Meia');

-- --------------------------------------------------------

--
-- Estrutura para tabela `presidente`
--

CREATE TABLE `presidente` (
  `Cod_CBF` varchar(20) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Despejando dados para a tabela `presidente`
--

INSERT INTO `presidente` (`Cod_CBF`) VALUES
('900100200'),
('900100201');

-- --------------------------------------------------------

--
-- Estrutura para tabela `recomenda`
--

CREATE TABLE `recomenda` (
  `CPF_Scout_FK` varchar(20) DEFAULT NULL,
  `Cod_BID_FK` int(11) DEFAULT NULL,
  `Data` date DEFAULT NULL,
  `Resultado` varchar(20) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Despejando dados para a tabela `recomenda`
--

INSERT INTO `recomenda` (`CPF_Scout_FK`, `Cod_BID_FK`, `Data`, `Resultado`) VALUES
('22222222222', 1, '2025-01-05', 'Bom'),
('22222222222', 2, '2025-01-05', 'Bom'),
('22222222222', 3, '2025-01-05', 'Excelente');

-- --------------------------------------------------------

--
-- Estrutura para tabela `scout`
--

CREATE TABLE `scout` (
  `CPF_FK` varchar(20) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Despejando dados para a tabela `scout`
--

INSERT INTO `scout` (`CPF_FK`) VALUES
('22222222222');

--
-- Índices para tabelas despejadas
--

--
-- Índices de tabela `analisa`
--
ALTER TABLE `analisa`
  ADD KEY `CPF_CT_FK` (`CPF_CT_FK`),
  ADD KEY `Cod_BID_FK` (`Cod_BID_FK`);

--
-- Índices de tabela `colaborador`
--
ALTER TABLE `colaborador`
  ADD PRIMARY KEY (`CPF`),
  ADD KEY `CPF_Gerente_FK` (`CPF_Gerente_FK`),
  ADD KEY `Cod_Dpto_FK` (`Cod_Dpto_FK`);

--
-- Índices de tabela `contrato`
--
ALTER TABLE `contrato`
  ADD PRIMARY KEY (`Codigo`),
  ADD KEY `Cod_Presidente_FK` (`Cod_Presidente_FK`),
  ADD KEY `Cod_BID_FK` (`Cod_BID_FK`);

--
-- Índices de tabela `departamento`
--
ALTER TABLE `departamento`
  ADD PRIMARY KEY (`Codigo`);

--
-- Índices de tabela `departamento_avalia_contrato`
--
ALTER TABLE `departamento_avalia_contrato`
  ADD KEY `Cod_Dpto_FK` (`Cod_Dpto_FK`),
  ADD KEY `Cod_Contrato_FK` (`Cod_Contrato_FK`);

--
-- Índices de tabela `dirigente`
--
ALTER TABLE `dirigente`
  ADD PRIMARY KEY (`Cod_CBF`),
  ADD KEY `CPF_Gerente_FK` (`CPF_Gerente_FK`);

--
-- Índices de tabela `equipe`
--
ALTER TABLE `equipe`
  ADD PRIMARY KEY (`Codigo`);

--
-- Índices de tabela `examina`
--
ALTER TABLE `examina`
  ADD KEY `CPF_Medico_FK` (`CPF_Medico_FK`),
  ADD KEY `Cod_BID_FK` (`Cod_BID_FK`);

--
-- Índices de tabela `gerente`
--
ALTER TABLE `gerente`
  ADD PRIMARY KEY (`CPF`);

--
-- Índices de tabela `jogador`
--
ALTER TABLE `jogador`
  ADD PRIMARY KEY (`Cod_BID`),
  ADD KEY `Cod_Equipe` (`Cod_Equipe`);

--
-- Índices de tabela `medico`
--
ALTER TABLE `medico`
  ADD PRIMARY KEY (`CPF_FK`);

--
-- Índices de tabela `membcomissaotec`
--
ALTER TABLE `membcomissaotec`
  ADD PRIMARY KEY (`CPF_FK`);

--
-- Índices de tabela `posicao`
--
ALTER TABLE `posicao`
  ADD KEY `Cod_BID_FK` (`Cod_BID_FK`);

--
-- Índices de tabela `presidente`
--
ALTER TABLE `presidente`
  ADD PRIMARY KEY (`Cod_CBF`);

--
-- Índices de tabela `recomenda`
--
ALTER TABLE `recomenda`
  ADD KEY `CPF_Scout_FK` (`CPF_Scout_FK`),
  ADD KEY `Cod_BID_FK` (`Cod_BID_FK`);

--
-- Índices de tabela `scout`
--
ALTER TABLE `scout`
  ADD PRIMARY KEY (`CPF_FK`);

--
-- Restrições para tabelas despejadas
--

--
-- Restrições para tabelas `analisa`
--
ALTER TABLE `analisa`
  ADD CONSTRAINT `analisa_ibfk_1` FOREIGN KEY (`CPF_CT_FK`) REFERENCES `membcomissaotec` (`CPF_FK`),
  ADD CONSTRAINT `analisa_ibfk_2` FOREIGN KEY (`Cod_BID_FK`) REFERENCES `jogador` (`Cod_BID`);

--
-- Restrições para tabelas `colaborador`
--
ALTER TABLE `colaborador`
  ADD CONSTRAINT `colaborador_ibfk_1` FOREIGN KEY (`CPF_Gerente_FK`) REFERENCES `gerente` (`CPF`),
  ADD CONSTRAINT `colaborador_ibfk_2` FOREIGN KEY (`Cod_Dpto_FK`) REFERENCES `departamento` (`Codigo`);

--
-- Restrições para tabelas `contrato`
--
ALTER TABLE `contrato`
  ADD CONSTRAINT `contrato_ibfk_1` FOREIGN KEY (`Cod_Presidente_FK`) REFERENCES `presidente` (`Cod_CBF`),
  ADD CONSTRAINT `contrato_ibfk_2` FOREIGN KEY (`Cod_BID_FK`) REFERENCES `jogador` (`Cod_BID`);

--
-- Restrições para tabelas `departamento_avalia_contrato`
--
ALTER TABLE `departamento_avalia_contrato`
  ADD CONSTRAINT `departamento_avalia_contrato_ibfk_1` FOREIGN KEY (`Cod_Dpto_FK`) REFERENCES `departamento` (`Codigo`),
  ADD CONSTRAINT `departamento_avalia_contrato_ibfk_2` FOREIGN KEY (`Cod_Contrato_FK`) REFERENCES `contrato` (`Codigo`);

--
-- Restrições para tabelas `dirigente`
--
ALTER TABLE `dirigente`
  ADD CONSTRAINT `dirigente_ibfk_1` FOREIGN KEY (`Cod_CBF`) REFERENCES `presidente` (`Cod_CBF`),
  ADD CONSTRAINT `dirigente_ibfk_2` FOREIGN KEY (`CPF_Gerente_FK`) REFERENCES `gerente` (`CPF`);

--
-- Restrições para tabelas `examina`
--
ALTER TABLE `examina`
  ADD CONSTRAINT `examina_ibfk_1` FOREIGN KEY (`CPF_Medico_FK`) REFERENCES `medico` (`CPF_FK`),
  ADD CONSTRAINT `examina_ibfk_2` FOREIGN KEY (`Cod_BID_FK`) REFERENCES `jogador` (`Cod_BID`);

--
-- Restrições para tabelas `jogador`
--
ALTER TABLE `jogador`
  ADD CONSTRAINT `jogador_ibfk_1` FOREIGN KEY (`Cod_Equipe`) REFERENCES `equipe` (`Codigo`);

--
-- Restrições para tabelas `medico`
--
ALTER TABLE `medico`
  ADD CONSTRAINT `medico_ibfk_1` FOREIGN KEY (`CPF_FK`) REFERENCES `colaborador` (`CPF`);

--
-- Restrições para tabelas `membcomissaotec`
--
ALTER TABLE `membcomissaotec`
  ADD CONSTRAINT `membcomissaotec_ibfk_1` FOREIGN KEY (`CPF_FK`) REFERENCES `colaborador` (`CPF`);

--
-- Restrições para tabelas `posicao`
--
ALTER TABLE `posicao`
  ADD CONSTRAINT `posicao_ibfk_1` FOREIGN KEY (`Cod_BID_FK`) REFERENCES `jogador` (`Cod_BID`);

--
-- Restrições para tabelas `recomenda`
--
ALTER TABLE `recomenda`
  ADD CONSTRAINT `recomenda_ibfk_1` FOREIGN KEY (`CPF_Scout_FK`) REFERENCES `scout` (`CPF_FK`),
  ADD CONSTRAINT `recomenda_ibfk_2` FOREIGN KEY (`Cod_BID_FK`) REFERENCES `jogador` (`Cod_BID`);

--
-- Restrições para tabelas `scout`
--
ALTER TABLE `scout`
  ADD CONSTRAINT `scout_ibfk_1` FOREIGN KEY (`CPF_FK`) REFERENCES `colaborador` (`CPF`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
