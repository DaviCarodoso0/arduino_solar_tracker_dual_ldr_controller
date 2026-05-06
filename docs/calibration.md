# Guia de Calibração

## 1. Limites do Servo (`LIM_ESQ` e `LIM_DIR`)

Com o **Monitor Serial** aberto, observe o valor de `Pos:` e mova o servo manualmente editando `POS_INICIAL`. Encontre os ângulos em que o painel aponta para:

- **Leste (manhã)** → defina como `LIM_ESQ` (ex: `50`)
- **Oeste (tarde)** → defina como `LIM_DIR` (ex: `125`)

Cuidado para não ultrapassar os limites mecânicos do servo.

---

## 2. Tolerância (`TOLERANCIA`)

A tolerância define o quanto a diferença entre os LDRs precisa ser para o servo se mover.

- **Valor baixo (5–10):** muito sensível, pode causar vibração constante em luz difusa.
- **Valor alto (20–30):** menos reativo, mais estável em dias nublados.

Comece com `15` e ajuste conforme o comportamento observado.

---

## 3. Limiares de Luz (`LIM_LUZ_BAIXA` e `LIM_LUZ_ALTA`)

Abra o Monitor Serial e observe o valor de `Med:` ao longo do dia:

| Condição       | Exemplo de leitura |
|----------------|--------------------|
| Plena luz solar| 700–900            |
| Sombra / nublado| 300–500           |
| Noite / escuro | 0–150              |

- Defina `LIM_LUZ_BAIXA` como um valor um pouco acima da leitura noturna (ex: `250`).
- Defina `LIM_LUZ_ALTA` como um valor que represente o amanhecer confiável (ex: `650`).

A histerese entre os dois valores (`LIM_LUZ_ALTA > LIM_LUZ_BAIXA`) evita transições repetidas em luz limítrofe.

---

## 4. Velocidade de Retorno (`SERVO_SWEEP_DELAY_MS`)

Controla a velocidade ao voltar para o leste à noite.

- Aumente para mover mais devagar (ex: `30 ms`).
- Diminua para retornar mais rápido (ex: `5 ms`), mas evite stresse mecânico.