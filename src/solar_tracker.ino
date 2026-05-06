/**
 * @file solar_tracker.ino
 * @brief Rastreador Solar com LDR e Servo Motor
 *
 * Rastreia a posição do sol ao longo do dia usando dois LDRs e
 * um servo motor. Entra em modo de espera ao anoitecer e retorna
 * à posição leste ao amanhecer.
 *
 * Hardware:
 *   - Arduino Uno / Nano
 *   - 2x LDR (fotoresistores)
 *   - 2x Resistor 10kΩ (divisor de tensão)
 *   - 1x Servo Motor (ex: SG90)
 *
 * Pinos:
 *   - A0 → LDR Direita (Oeste)
 *   - A1 → LDR Esquerda (Leste)
 *   - D9 → Sinal do Servo
 *
 * @author  Seu Nome
 * @version 2.0.0
 * @date    2025
 * @license MIT
 */

#include <Servo.h>
#include "config.h"

// ─── Objeto Global ────────────────────────────────────────────────────────────
Servo servo;

// ─── Estado do Sistema ────────────────────────────────────────────────────────
struct SystemState {
  int  pos;        // Posição atual do servo (graus)
  bool sleeping;   // true = modo noturno
};

static SystemState state = { POS_INICIAL, false };

// ─── Protótipos ───────────────────────────────────────────────────────────────
void handleNightTransition(int mediaLuz);
void handleDawnTransition(int mediaLuz);
void trackSun(int valEsq, int valDir);
void returnToEast();
void printStatus(int valEsq, int valDir, int mediaLuz);

// ─── Setup ────────────────────────────────────────────────────────────────────
void setup() {
  Serial.begin(BAUD_RATE);
  servo.attach(SERVO_PIN);
  servo.write(state.pos);

  Serial.println(F("================================="));
  Serial.println(F("   Rastreador Solar v2.0 iniciado"));
  Serial.println(F("================================="));
}

// ─── Loop Principal ───────────────────────────────────────────────────────────
void loop() {
  const int valEsq  = analogRead(LDR_ESQ_PIN);
  const int valDir  = analogRead(LDR_DIR_PIN);
  const int media   = (valEsq + valDir) / 2;

  printStatus(valEsq, valDir, media);

  handleNightTransition(media);
  handleDawnTransition(media);

  if (!state.sleeping) {
    trackSun(valEsq, valDir);
  }

  delay(LOOP_DELAY_MS);
}

// ─── Funções ──────────────────────────────────────────────────────────────────

/**
 * @brief Verifica se anoiteceu e aciona o modo de espera.
 */
void handleNightTransition(int mediaLuz) {
  if (!state.sleeping && mediaLuz < LIM_LUZ_BAIXA) {
    Serial.println(F("[NOITE] Anoiteceu — retornando ao leste e dormindo..."));
    returnToEast();
    state.sleeping = true;
  }
}

/**
 * @brief Verifica se amanheceu e retoma o rastreamento.
 */
void handleDawnTransition(int mediaLuz) {
  if (state.sleeping && mediaLuz > LIM_LUZ_ALTA) {
    Serial.println(F("[DIA]   Amanheceu — retomando rastreamento..."));
    state.sleeping = false;
    delay(DAWN_STABILIZE_MS);
  }
}

/**
 * @brief Move o servo suavemente para a posição leste (limiteEsq).
 */
void returnToEast() {
  int step = (state.pos > LIM_ESQ) ? -1 : 1;
  while (state.pos != LIM_ESQ) {
    state.pos += step;
    servo.write(state.pos);
    delay(SERVO_SWEEP_DELAY_MS);
  }
}

/**
 * @brief Ajusta a posição do servo de acordo com a diferença entre os LDRs.
 *
 * A diferença (esq - dir) invertida corrige a direção física do rastreamento.
 */
void trackSun(int valEsq, int valDir) {
  const int dif = valEsq - valDir;  // sinal positivo → mover para oeste

  if (abs(dif) > TOLERANCIA) {
    // Mapeia a diferença para um ajuste proporcional de 1–MAX_AJUSTE graus
    const int ajuste = map(abs(dif), TOLERANCIA, 1023, 1, MAX_AJUSTE);

    if (dif > 0 && state.pos > LIM_ESQ) {
      state.pos -= ajuste;
    } else if (dif < 0 && state.pos < LIM_DIR) {
      state.pos += ajuste;
    }

    servo.write(state.pos);
  }
}

/**
 * @brief Exibe leituras e estado atual na porta serial.
 */
void printStatus(int valEsq, int valDir, int mediaLuz) {
  Serial.print(F("Esq:"));    Serial.print(valEsq);
  Serial.print(F(" Dir:"));   Serial.print(valDir);
  Serial.print(F(" Med:"));   Serial.print(mediaLuz);
  Serial.print(F(" Pos:"));   Serial.print(state.pos);
  Serial.print(F("  ["));
  Serial.print(state.sleeping ? F("DORMINDO") : F("RASTREANDO"));
  Serial.println(F("]"));
}
