/**
 * @file config.h
 * @brief Configurações do Rastreador Solar
 *
 * Altere os valores abaixo para calibrar o sistema ao seu hardware.
 */

#pragma once

// ─── Pinos ────────────────────────────────────────────────────────────────────
constexpr uint8_t SERVO_PIN   = 9;   ///< Pino PWM do servo
constexpr uint8_t LDR_ESQ_PIN = A1;  ///< LDR lado leste
constexpr uint8_t LDR_DIR_PIN = A0;  ///< LDR lado oeste

// ─── Limites de Movimento do Servo ───────────────────────────────────────────
constexpr int LIM_ESQ    = 50;   ///< Limite leste  (graus) — posição de repouso
constexpr int LIM_DIR    = 125;  ///< Limite oeste  (graus)
constexpr int POS_INICIAL = 90;  ///< Posição inicial (graus)

// ─── Rastreamento ─────────────────────────────────────────────────────────────
constexpr int TOLERANCIA  = 15;  ///< Diferença mínima entre LDRs para mover (0–1023)
constexpr int MAX_AJUSTE  = 5;   ///< Ajuste máximo por ciclo (graus)

// ─── Luminosidade ─────────────────────────────────────────────────────────────
constexpr int LIM_LUZ_BAIXA = 250;   ///< Abaixo → noite  (0–1023)
constexpr int LIM_LUZ_ALTA  = 650;   ///< Acima  → dia    (0–1023)

// ─── Temporização ─────────────────────────────────────────────────────────────
constexpr int LOOP_DELAY_MS       = 10;    ///< Delay do loop principal (ms)
constexpr int SERVO_SWEEP_DELAY_MS = 15;   ///< Delay ao varrer para o leste (ms)
constexpr int DAWN_STABILIZE_MS   = 4000; ///< Aguarda estabilização ao amanhecer (ms)

// ─── Serial ───────────────────────────────────────────────────────────────────
constexpr long BAUD_RATE = 9600;