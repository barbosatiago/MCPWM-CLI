/******************************************************************************
 * Empresa:            Multscan Inteligência Tecnológica
 * Nome do Arquivo:    multscan_shell.h
 * Descrição:          Interface que realiza comandos e leitura através do terminal
 * Autor:              Tiago Barbosa
 * Data de Criação:    25/09/2024
 * Versão:             1.0.0
 *
 * Histórico de Alterações:
 * - Versão 1.0.0 (25/09/2024)
 *   - Criação dos arquivos
 * 
 *****************************************************************************/
#ifndef MULTSCAN_SHELL_H
#define MULTSCAN_SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/event_groups.h"
#include "FreeRTOS_CLI.h"

#include "esp_err.h"
#include "esp_log.h"

#include "driver/uart.h"
#include "driver/gpio.h"

#include "mcpwmMultStruct.h"


#define TXD_PIN                        (GPIO_NUM_43)
#define RXD_PIN                        (GPIO_NUM_44)
#define CLI_BUFFER_SIZE 1000  // Tamanho dos buffers de entrada/saída

typedef int multscan_sts;



multscan_sts multscan_inicializa_shell(void);
multscan_sts multscan_envia_msg(const char *mensagem);

static BaseType_t helloCommand(char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString);
static BaseType_t exitCommand(char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString);
static BaseType_t setCommand(char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString);
static BaseType_t helpCommand(char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString);

static BaseType_t ligarPwmParCommand(char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString);
static BaseType_t desligarPwmParCommand(char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString);
static BaseType_t ligarPwmImparCommand(char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString);
static BaseType_t desligarPwmImparCommand(char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString);
static BaseType_t setTempoInjecaoCommand(char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString);

// Função para registrar os comandos CLI
void registerCLICommands(void);
void cli_task(void *pvParameters);


static const CLI_Command_Definition_t helloCommandDefinition = {
    "hello",  // Nome do comando
    "hello: Exibe uma mensagem de saudacao.\r\n",  // Descrição do comando
    helloCommand,  // Função de callback
    0  // Número de argumentos esperados (0 no caso deste comando)
};

// Estrutura que define o comando exit
static const CLI_Command_Definition_t exitCommandDefinition = {
    "exit",  // Nome do comando
    "exit: Sai do terminal CLI.\r\n",  // Descrição do comando
    exitCommand,  // Função de callback
    0  // Número de argumentos esperados (0 neste caso)
};

static const CLI_Command_Definition_t setCommandDefinition = {
    "set_ta",
    "set <param1> <param2>: Exemplo de comando que aceita dois argumentos\r\n",
    setCommand,
    2
};

static const CLI_Command_Definition_t ajudaCommandDefinition = {
    "ajuda",
    "ajuda: Lista todos os comandos disponiveis\r\n",
    helpCommand,
    0
};

static const CLI_Command_Definition_t ligarPwmParDefinition = {
    "ligar pwm par",
    "ligar pwm par: liga os pwms do injetor e led par",
    ligarPwmParCommand,
    2
};


static const CLI_Command_Definition_t desligarPwmParDefinition = {
    "desligar pwm par",
    "desligar pwm par: desliga os pwms do injetor e led par",
    desligarPwmParCommand,
    2
};

static const CLI_Command_Definition_t ligaPwmImparDefinition = {
    "ligar pwm impar",
    "ligar pwm impar: liga os pwms do injetor e led impar",
    ligarPwmImparCommand,
    2
};

static const CLI_Command_Definition_t desligaPwmImparDefinition = {
    "desligar pwm impar",
    "desligar pwm impar: desliga os pwms do injetor e led impar",
    desligarPwmImparCommand,
    2
};

static const CLI_Command_Definition_t setTempoInjecaoDefinition = {
    "set injecao",
    "set injecao <param>: Atualiza tempo de injecao",
    setTempoInjecaoCommand,
    2
};




#endif