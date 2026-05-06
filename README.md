# ☀️ Rastreador Solar — Arduino

Rastreador solar de eixo único usando dois LDRs e um servo motor. O sistema segue a luz solar ao longo do dia e entra em modo de espera à noite, retornando automaticamente à posição leste ao amanhecer.

---

## 📋 Funcionalidades

- Rastreamento proporcional (ajuste suavizado pela diferença dos LDRs)
- Modo noturno automático com retorno ao leste
- Retomada automática ao amanhecer
- Todos os parâmetros centralizados em `config.h`
- Log detalhado pela porta serial

---

## 🔧 Hardware Necessário

| Componente         | Quantidade |
|--------------------|:----------:|
| Arduino Uno / Nano | 1          |
| Servo Motor (SG90) | 1          |
| LDR (fotoresistor) | 2          |
| Resistor 10 kΩ     | 2          |
| Jumpers / protoboard | —        |

---

## 🔌 Esquema de Ligação

```
Arduino          Componente
───────          ──────────
A0       ──────  LDR Direita (Oeste)  ── GND
                      ┴
                    10 kΩ
                      ┬
                     5V

A1       ──────  LDR Esquerda (Leste) ── GND
                      ┴
                    10 kΩ
                      ┬
                     5V

D9       ──────  Servo (Sinal)
5V       ──────  Servo (VCC)
GND      ──────  Servo (GND)
```

> **Dica:** Posicione os dois LDRs lado a lado com um divisor físico (papelão, etc.) entre eles para aumentar a sensibilidade direcional.

---

## 🚀 Como Usar

1. Clone o repositório:
   ```bash
   git clone https://github.com/seu-usuario/solar-tracker.git
   ```

2. Abra `src/solar_tracker.ino` na Arduino IDE (versão 1.8+ ou 2.x).

3. Certifique-se de que a biblioteca **Servo** está instalada *(já inclusa na IDE padrão)*.

4. **Calibre** os parâmetros em `src/config.h` para seu hardware:

   | Parâmetro        | Descrição                                    | Padrão |
   |------------------|----------------------------------------------|--------|
   | `LIM_ESQ`        | Limite leste do servo (°)                    | `50`   |
   | `LIM_DIR`        | Limite oeste do servo (°)                    | `125`  |
   | `TOLERANCIA`     | Diferença mínima entre LDRs para mover       | `15`   |
   | `LIM_LUZ_BAIXA`  | Leitura abaixo da qual considera noite        | `250`  |
   | `LIM_LUZ_ALTA`   | Leitura acima da qual considera amanhecer     | `650`  |

5. Faça o upload para o Arduino e abra o **Monitor Serial** a `9600 baud` para acompanhar o status.

---

## 📊 Lógica de Estado

```
              ┌──────────────┐
    início    │   RASTREANDO │ ◄──── luz > LIM_LUZ_ALTA
              └──────┬───────┘
                     │ luz < LIM_LUZ_BAIXA
                     ▼
              ┌──────────────┐
              │   DORMINDO   │  (servo no leste)
              └──────────────┘
```

---

## 📁 Estrutura do Repositório

```
solar-tracker/
├── docs/
│   └── calibration.md      # Guia de calibração
├── src/
│   ├── solar_tracker.ino   # Sketch principal
│   └── config.h            # Parâmetros configuráveis
├── LICENSE
└── README.md
```

---

## 🛠️ Calibração

Veja o guia completo em [`docs/calibration.md`](docs/calibration.md).

---

## 📜 Licença

Distribuído sob a licença **MIT**. Veja [LICENSE](LICENSE) para detalhes.
