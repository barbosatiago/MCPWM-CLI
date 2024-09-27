/******************************************************************************
 * Empresa:            Multscan Inteligência Tecnológica
 * Nome do Arquivo:    multscan_shell.c
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
#ifndef MULTSCAN_SHELL_C
#define MULTSCAN_SHELL_C

#include "multscan_shell.h"



multscan_sts multscan_inicializa_shell(void) {
    multscan_sts status = 0;

    const uart_config_t uart = {
        .baud_rate  = 115200,
        .data_bits  = UART_DATA_8_BITS,
        .parity     = UART_PARITY_DISABLE,
        .stop_bits  = UART_STOP_BITS_1,
        .flow_ctrl  = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_DEFAULT,
    };

    // Instalação do driver UART
    if (uart_driver_install(UART_NUM_1, 2048, 2048, 0, NULL, 0) != ESP_OK) {
        status = -1;  // Define um código de erro apropriado
        return status;
    }

    // Configuração dos parâmetros UART
    if (uart_param_config(UART_NUM_1, &uart) != ESP_OK) {
        status = -2;  // Define um código de erro apropriado
        uart_driver_delete(UART_NUM_1);  // Remove o driver instalado
        return status;
    }

    // Configuração dos pinos UART
    if (uart_set_pin(UART_NUM_1, TXD_PIN, RXD_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE) != ESP_OK) {
        status = -3;  // Define um código de erro apropriado
        uart_driver_delete(UART_NUM_1);  // Remove o driver instalado
        return status;
    }

    // Registra os comandos do CLI
    registerCLICommands();

    // Cria a tarefa CLI para gerenciar a UART
    xTaskCreate(cli_task, "CLI Task", 4096, NULL, 5, NULL);

    return status;
}

multscan_sts multscan_envia_msg(const char *mensagem) {
    multscan_sts status = 0;
    uart_write_bytes(UART_NUM_1, mensagem, strlen(mensagem));
    return status;

}

static BaseType_t helloCommand(char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString) {
    const char *message = "Comando recebido: Ola, Mundo!\r\n";
    snprintf(pcWriteBuffer, xWriteBufferLen, "%s", message);
    return pdFALSE;  // pdFALSE indica que não há mais dados para enviar
}

// Função para registrar os comandos CLI
void registerCLICommands(void) {
    FreeRTOS_CLIRegisterCommand(&ajudaCommandDefinition);
    FreeRTOS_CLIRegisterCommand(&ligarPwmParDefinition);
    FreeRTOS_CLIRegisterCommand(&ligaPwmImparDefinition);
    FreeRTOS_CLIRegisterCommand(&desligaPwmImparDefinition);
    FreeRTOS_CLIRegisterCommand(&setTempoInjecaoDefinition);
}



void cli_task(void *pvParameters) {
    char inputBuffer[CLI_BUFFER_SIZE] = {0};
    char outputBuffer[CLI_BUFFER_SIZE] = {0};
    int bytesRead = 0;
    int cursor = 0;
    uart_write_bytes(UART_NUM_1, "\nmultscan-shell>> ", strlen("\nmultscan-shell>> "));

    while (1) {
        
        // Leitura da UART
        bytesRead = uart_read_bytes(UART_NUM_1, &inputBuffer[cursor], 1, pdMS_TO_TICKS(1000));

        if (bytesRead > 0) {
            // Verifica se o usuário pressionou ENTER (código ASCII 13)
            if (inputBuffer[cursor] == '\r') {
                inputBuffer[cursor] = '\0';  // Termina a string

                // Processa o comando
                FreeRTOS_CLIProcessCommand(inputBuffer, outputBuffer, CLI_BUFFER_SIZE);

                // Envia a resposta pela UART
                uart_write_bytes(UART_NUM_1, outputBuffer, strlen(outputBuffer));

                // Limpa o buffer de entrada
                memset(inputBuffer, 0, CLI_BUFFER_SIZE);
                cursor = 0;  // Reseta o cursor
                uart_flush(UART_NUM_1);
                uart_write_bytes(UART_NUM_1, "\nmultscan-shell>> ", strlen("\nmultscan-shell>> "));
            } else {
                cursor++;  // Incrementa o cursor para o próximo caractere
                if (cursor >= CLI_BUFFER_SIZE) {
                    cursor = CLI_BUFFER_SIZE - 1;  // Evita estouro de buffer
                }
            }
        }
    }
}

static BaseType_t exitCommand(char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString) {
    const char *message = "Comando recebido: Saindo do CLI...\r\n";
    snprintf(pcWriteBuffer, xWriteBufferLen, "%s", message);

    // // Finaliza a tarefa CLI
    // if (cliTaskHandle != NULL) {
    //     vTaskDelete(cliTaskHandle);
    //     cliTaskHandle = NULL;
    // }
    return pdFALSE;
}


static BaseType_t setCommand(char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString) {
    const char *param1;
    const char *param2;
    BaseType_t xParamLen1, xParamLen2, xResult;


    // Extraindo o primeiro argumento (param1)
    param1 = FreeRTOS_CLIGetParameter(pcCommandString, 1, &xParamLen1);
    // Extraindo o segundo argumento (param2)
    param2 = FreeRTOS_CLIGetParameter(pcCommandString, 2, &xParamLen2);


    if (param1 == NULL || param2 == NULL) {
        snprintf(pcWriteBuffer, xWriteBufferLen, "Erro: parâmetros inválidos.\r\n");
    } else {
        // Aqui você pode adicionar a lógica para lidar com os argumentos
        int numero1 = atoi(param1);
        int numero2 = atoi(param2);

        int resultado = numero1 + numero2;

        snprintf(pcWriteBuffer, xWriteBufferLen, "Comando set recebido: Resultado: %d\r\n", resultado);
    }

    return pdFALSE;  // pdFALSE indica que não há mais dados a serem enviados
}

static BaseType_t helpCommand(char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString) {
    const char *message = 
    "+-------------------------------------------------------------------------+\r\n"
    "| Lista de Comandos do Sistema                                            |\r\n"
    "+-------------------------------------------------------------------------+\r\n"
    "| ajuda:             | Lista todos os comandos disponíveis.               |\r\n"
    "| ligar_pwm_par:     | liga os pwms do injetor e led par.                 |\r\n"
    "| desligar_pwm_par:  | desliga os pwms do injetor e led par.              |\r\n"
    "| ligar_pwm_impar:   | liga os pwms do injetor e led impar.               |\r\n"
    "| desligar_pwm_impar:| Lista todos os comandos disponíveis.               |\r\n"
    "+-------------------------------------------------------------------------+\r\n";

    snprintf(pcWriteBuffer, xWriteBufferLen, "%s", message);
    
    return pdFALSE;
}


static BaseType_t ligarPwmParCommand(char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString){
    const char *message = "Ligando PWM do LED e do Injetor PAR\r\n";
    snprintf(pcWriteBuffer, xWriteBufferLen, "%s", message);

    mcpwm_timer_start_stop(timer_led_par, MCPWM_TIMER_START_NO_STOP);
    mcpwm_timer_start_stop(timer_injetor_par, MCPWM_TIMER_START_NO_STOP);

    return pdFALSE;

}

static BaseType_t desligarPwmParCommand(char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString) {
    const char *message = "Desligando PWM do Led e do Injetor PAR\r\n";
    snprintf(pcWriteBuffer, xWriteBufferLen, "%s", message);

    mcpwm_timer_start_stop(timer_led_par, MCPWM_TIMER_STOP_FULL);
    mcpwm_timer_start_stop(timer_injetor_par, MCPWM_TIMER_STOP_FULL);

    return pdFALSE;

}

static BaseType_t ligarPwmImparCommand(char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString){
    const char *message = "Ligando PWM do LED e do Injetor Impar\r\n";
    snprintf(pcWriteBuffer, xWriteBufferLen, "%s", message);

    mcpwm_timer_start_stop(timer_led_impar, MCPWM_TIMER_START_NO_STOP);
    mcpwm_timer_start_stop(timer_injetor_impar, MCPWM_TIMER_START_NO_STOP);

    return pdFALSE;

}

static BaseType_t desligarPwmImparCommand(char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString) {
    const char *message = "Desligando PWM do Led e do Injetor Impar\r\n";
    snprintf(pcWriteBuffer, xWriteBufferLen, "%s", message);

    mcpwm_timer_start_stop(timer_led_impar, MCPWM_TIMER_STOP_FULL);
    mcpwm_timer_start_stop(timer_injetor_impar, MCPWM_TIMER_STOP_FULL);

    return pdFALSE;

}

static BaseType_t setTempoInjecaoCommand(char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString) {
    uint32_t tempoInjecaoUs;
    const char *param1;
    BaseType_t xParamLen1, xParamLen2, xResult;


    // // Extraindo o primeiro argumento (param1)
    param1 = FreeRTOS_CLIGetParameter(pcCommandString, 1, &xParamLen1);
    // Extraindo o segundo argumento (param2)
    tempoInjecaoUs = FreeRTOS_CLIGetParameter(pcCommandString, 2, &xParamLen2);


    if (param1 == NULL || tempoInjecaoUs == NULL) {
        snprintf(pcWriteBuffer, xWriteBufferLen, "Erro: parâmetros inválidos.\r\n");
    } else {
        // Aqui você pode adicionar a lógica para lidar com os argumentos
        uint32_t numero1 = (uint32_t)atoi(tempoInjecaoUs);
        
        snprintf(pcWriteBuffer, xWriteBufferLen, "Tempo de injecao recebido: %ld\r\n", numero1);

        mcpwm_comparator_set_compare_value(comparador_injetor_par, numero1);
        mcpwm_comparator_set_compare_value(comparador_injetor_impar, numero1);
    }


    
    return pdFALSE;
}


#endif