/******************************************************************************
 * Nome do Arquivo:    mcpwmMultStruct.c
 * Descrição:          Software principal para utilizar funções do MCPWM
 * Autor:              Valdenir Vasconcelos
 * Data de Criação:    23/10/2023
 * Versão:             0.0.1
 *
 * Histórico de Alterações:
 * - Versão 0.0.1 (23/10/2023) - Desenvolvedor: Tiago Barbosa(@barbosatiago)
 *   - Portabilidade do software para a versão 0.0.3 do software completo da máquina de limpeza de bicos.
 *****************************************************************************/

#ifndef MCPWM_MULTS_STRUCT_C_
#define MCPWM_MULTS_STRUCT_C_

#include "mcpwmMultStruct.h"

mcpwm_cmpr_handle_t comparador_injetor_par = NULL;
mcpwm_cmpr_handle_t comparador_led_par = NULL;
mcpwm_timer_handle_t timer_injetor_par = NULL;
mcpwm_timer_handle_t timer_led_par = NULL;
mcpwm_sync_handle_t sync_handle_par = NULL;
mcpwm_oper_handle_t operador_injetor_par = NULL;
mcpwm_oper_handle_t operador_led_par = NULL;
mcpwm_gen_handle_t gerador_injetor_par = NULL;
mcpwm_gen_handle_t gerador_led_par = NULL;

mcpwm_cmpr_handle_t comparador_injetor_impar = NULL;
mcpwm_cmpr_handle_t comparador_led_impar = NULL;
mcpwm_timer_handle_t timer_injetor_impar = NULL;
mcpwm_timer_handle_t timer_led_impar = NULL;
mcpwm_sync_handle_t sync_handle_impar = NULL;
mcpwm_oper_handle_t operador_injetor_impar = NULL;
mcpwm_oper_handle_t operador_led_impar = NULL;
mcpwm_gen_handle_t gerador_injetor_impar = NULL;
mcpwm_gen_handle_t gerador_led_impar = NULL;

/******************************************************************************
 * @brief Cria um identificador de sincronização para um timer PWM em um módulo MCPWM.
 *
 * Esta função cria um identificador de sincronização que permite a sincronização de um timer PWM específico em um módulo MCPWM com base em um evento predefinido.
 *
 * @param in_timer     Um identificador do timer PWM que será sincronizado.
 * @param ret_sync     Um ponteiro para o identificador de sincronização a ser criado e retornado por esta função.
 *
 * @note Certifique-se de que o timer e o módulo MCPWM estejam devidamente configurados antes de chamar esta função.
 *
 * @return Nenhum valor de retorno.
*****************************************************************************/
void criaHandleSincronizacao(mcpwm_timer_handle_t in_timer, mcpwm_sync_handle_t *ret_sync) {

    mcpwm_timer_sync_src_config_t timer_sync_config = {
        .timer_event = MCPWM_TIMER_EVENT_EMPTY,             //posição onde será feito a sincronia.
    };
    mcpwm_new_timer_sync_src(in_timer, &timer_sync_config, ret_sync);
}

/******************************************************************************
 * @brief Sincroniza dois timers PWM em um módulo MCPWM.
 *
 * Esta função permite sincronizar dois timers PWM em um módulo MCPWM, configurando a fase de contagem do timer de destino para coincidir com o valor especificado.
 *
 * @param in_sync      Um identificador do módulo MCPWM que atua como fonte de sincronização.
 * @param in_timer     Um identificador do timer PWM de destino que será sincronizado.
 * @param valorSync    O valor em que o timer de destino será sincronizado.
 *
 * @note Certifique-se de que os timers e o módulo MCPWM estejam devidamente configurados antes de chamar esta função.
 *
 * @return Nenhum valor de retorno.
*****************************************************************************/
void sincronizarTimers(mcpwm_sync_handle_t in_sync, mcpwm_timer_handle_t in_timer, uint32_t valorSync) {
   
    mcpwm_timer_sync_phase_config_t sync_phase_config = {
        .count_value = valorSync,
        .direction = MCPWM_TIMER_DIRECTION_UP,
        .sync_src = in_sync,
    };
    mcpwm_timer_set_phase_on_sync(in_timer, &sync_phase_config);
}

/******************************************************************************
 * @brief Configura a frequência do módulo PWM.
 *
 * Esta função configura a frequência do módulo PWM especificado pelo parâmetro 'timerSet'.
 *
 * @param timerSet     Um ponteiro para a estrutura 'mcpwm_timer_handle_t' que representa o timer PWM a ser configurado.
 * @param frequencia   A frequência desejada em Hertz.
 *
 * @note Certifique-se de que o timer PWM e suas configurações estejam corretamente inicializados antes de chamar esta função.
 * @note A frequência deve ser compatível com a resolução do timer.
 *
 * @return Nenhum valor de retorno.
*****************************************************************************/
void mcpwmSetFrequenci(mcpwm_timer_handle_t timerSet, uint32_t frequencia) {
    if (frequencia != 0) {
        mcpwm_timer_set_period(timerSet, (MCPWM_TIMER_FREQUENCIA/frequencia));
    }
}

#endif