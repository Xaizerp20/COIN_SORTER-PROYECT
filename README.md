# Proyecto - Clasificador de Monedas con Microcontroladores

Este proyecto tiene como objetivo diseñar y construir un sistema automatizado de clasificación de monedas utilizando microcontroladores. El sistema será capaz de identificar y separar monedas de diferentes denominaciones y proporcionar información sobre la cantidad y el valor total de las monedas clasificadas.

## Características del Proyecto

### Funcionalidades

1. **Introducción de Monedas:** Los usuarios podrán introducir monedas de diferentes denominaciones en el sistema a través de un teclado (keypad).

2. **Clasificación Automatizada:** El sistema utilizará un motor paso a paso (stepper motor) para mover una plataforma que permitirá que las monedas sean clasificadas en diferentes compartimentos según su valor (1 peso, 5 pesos, 10 pesos, 25 pesos).

3. **Interfaz de Usuario:** El sistema contará con una pantalla LCD que mostrará un menú con opciones seleccionables utilizando el keypad.

4. **Visualización de Información:** Los usuarios podrán ver la cantidad de monedas de cada tipo y el valor total en pesos de las monedas clasificadas a través de la pantalla LCD y una matriz LED.

5. **Mantenimiento:** Se proporcionará una opción de mantenimiento que activará un sistema de enfriamiento para evitar el sobrecalentamiento de los componentes durante un uso continuo simulando condiciones de vida real.

### Componentes Principales

- KEYPAD: Permite a los usuarios seleccionar opciones y valores.
- STEPPERMOTOR: Controla el movimiento de la plataforma de clasificación.
- LCD: Muestra el menú y la información de las monedas clasificadas.
- MATRIZ LED: Indica la dirección del movimiento del motor paso a paso.
- LEDS: Proporciona indicadores visuales, como LEDs rojos y verdes para seguridad.
- BUZZER: Proporciona indicadores auditivos, como un pitido de advertencia.
- SERVOMOTOR: Controla el sistema de enfriamiento y mantenimiento.
- MOTOR DC: Se utiliza en el sistema de enfriamiento.

## Instrucciones de Uso

1. Seleccione la opción deseada del menú utilizando el keypad.
2. Para introducir una moneda, elija la opción A y siga las instrucciones en la pantalla LCD.
3. La plataforma de clasificación se moverá automáticamente para organizar y clasificar las monedas.
4. Los indicadores visuales y auditivos indicarán cuándo no se debe tocar la máquina.
5. Las opciones B y C mostrarán información sobre la cantidad y el valor de las monedas clasificadas.
6. La opción D activará el sistema de mantenimiento y enfriamiento.

## Esquema del Organizador

![Esquema del Organizador](/Imgs/Esquema.jpg)

## Contribuciones

Este proyecto está abierto a contribuciones. Si deseas participar, no dudes en realizar un fork del repositorio y enviar tus propuestas a través de pull requests.

## Créditos

Este proyecto fue propuesto por [Xavier Jimenez @Xaizer20].

