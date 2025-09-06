# Control de LEDs con Switches y Potenciómetros

Este proyecto implementa una secuencia de encendido de dos LEDs (del módulo doble relé) controlada mediante **switches** y **potenciómetros**, utilizando una placa **Arduino UNO** (o compatible).  
El sistema cuenta con un switch general de activación, dos switches asociados a cada LED, y dos potenciómetros que definen los tiempos de encendido.

---

## 🔧 Componentes necesarios

- 1 × Arduino UNO / Nano / Mega  
- 1 × Módulo doble relé
- 3 × Pulsadores (switch general + 2 asociados a los LEDs)  
- 2 × Potenciómetros de 10kΩ  
- Cables de conexión  
- Protoboard  

---

## ⚙️ Conexiones

- **LED1** → Pin digital **2**  
- **LED2** → Pin digital **3**  
- **Switch general** → Pin digital **4** (con `INPUT_PULLUP`)  
- **Switch LED1** → Pin digital **10** (con `INPUT_PULLUP`)  
- **Switch LED2** → Pin digital **9** (con `INPUT_PULLUP`)  
- **Potenciómetro 1** → Pin analógico **A0**  
- **Potenciómetro 2** → Pin analógico **A1**  

> ⚠️ Los switches están configurados con `INPUT_PULLUP`, por lo que funcionan en lógica invertida:  
> - **Abierto = HIGH**  
> - **Cerrado = LOW**

---

## 🧩 Lógica de funcionamiento

1. **Inicio (primera vez)**  
   - El sistema arranca cuando el switch general está activado.  
   - Si los dos switches asociados (LED1 y LED2) están cerrados al inicio, se enciende el **LED1** durante un tiempo definido por el potenciómetro 1 (`tp1`).  

2. **Ciclo normal**  
   - Si está encendido **LED1** y ambos switches se mantienen cerrados, se apaga LED1 y se enciende **LED2** durante el tiempo `tp2` (definido por el potenciómetro 2).  
   - Si está encendido **LED2** y ambos switches siguen cerrados, se apaga LED2 y se vuelve a encender **LED1** durante `tp1`.  
   - El ciclo se repite indefinidamente mientras los switches estén cerrados y el sistema activo.  

3. **Switch general**  
   - Si se abre el switch general mientras **LED1 está encendido**, el sistema completa el ciclo pasando a **LED2** antes de apagarse.  
   - Si se abre el switch general mientras **LED2 está encendido**, el sistema simplemente termina en LED2 y se apaga.  
   - Esto garantiza que el sistema siempre finalice en LED2 al cortar el switch general.  
