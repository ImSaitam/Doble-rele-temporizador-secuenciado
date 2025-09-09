# Control de Pistones con Switches y Potenciómetros

Este proyecto implementa una secuencia de **dos pistones** (simulados con LEDs o controlados con un módulo relé) mediante **switches** y **potenciómetros**, utilizando una placa **Arduino UNO** (o compatible).  
El sistema cuenta con un **switch general de activación**, dos **switches asociados a cada pistón**, y dos **potenciómetros** que definen los tiempos de activación.

---

## 🔧 Componentes necesarios

- 1 × Arduino UNO / Nano / Mega  
- 2 × Actuadores (pistones eléctricos o LEDs con resistencias)  
- 1 × Módulo de relés (opcional, si se usan pistones reales)  
- 3 × Pulsadores (switch general + 2 asociados a los pistones)  
- 2 × Potenciómetros de 10kΩ  
- Cables de conexión  
- Protoboard  

---

## ⚙️ Conexiones

- **Pistón 1** → Pin digital **2**  
- **Pistón 2** → Pin digital **3**  
- **Switch general** → Pin digital **4** (con `INPUT_PULLUP`)  
- **Switch Pistón 1** → Pin digital **10** (con `INPUT_PULLUP`)  
- **Switch Pistón 2** → Pin digital **9** (con `INPUT_PULLUP`)  
- **Potenciómetro 1** → Pin analógico **A0**  
- **Potenciómetro 2** → Pin analógico **A1**  

> ⚠️ Los switches están configurados con `INPUT_PULLUP`, por lo que funcionan en lógica invertida:  
> - **Abierto = HIGH**  
> - **Cerrado = LOW**

---

## 🧩 Lógica de funcionamiento

1. **Inicio (primera vez)**  
   - El sistema arranca cuando el **switch general** está activado.  
   - Si los dos switches asociados (Pistón 1 y Pistón 2) están cerrados al inicio, se activa el **Pistón 1** durante un tiempo definido por el potenciómetro 1 (`tp1`).  

2. **Ciclo normal**  
   - Si está activo **Pistón 1** y ambos switches se mantienen cerrados, se desactiva el Pistón 1 y se activa el **Pistón 2** durante el tiempo `tp2`.  
   - Si está activo **Pistón 2** y ambos switches siguen cerrados, se desactiva el Pistón 2 y se vuelve a activar el **Pistón 1** durante `tp1`.  
   - El ciclo se repite indefinidamente mientras los switches estén cerrados y el sistema activo.  

3. **Switch general (apagado controlado)**  
   - Si se abre el switch general mientras **Pistón 1 está activo**, el sistema completa el ciclo pasando a **Pistón 2** antes de apagarse.  
   - Si se abre el switch general mientras **Pistón 2 está activo**, el sistema termina directamente en Pistón 2 y se apaga.  
   - Esto garantiza que el sistema **siempre finalice en Pistón 2 al cortar el switch general**.  

---

## 📊 Resumen

- El **switch general** enciende y apaga todo el sistema.  
- El arranque inicial siempre comienza por **Pistón 1**.  
- El ciclo alterna entre Pistón 1 ↔ Pistón 2, con tiempos configurados por los potenciómetros.  
- El apagado con el switch general **siempre finaliza en Pistón 2**, asegurando un estado de reposo definido.  
