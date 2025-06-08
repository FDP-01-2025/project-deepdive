# Proyecto de C++ - DeepDive

## Descripción del Proyecto

**"DeepDive"** Consiste en un videojuego desarrollado en C++ que se ejecuta exclusivamente en consola. El Jugador controla un **submarino** que debe esquivar obstáculos como peces y rocas mientras avanza bajo el mar. El juego se maneja mediante menús interactivos y el uso del teclado expecíficamente con las teclas **(W,A,S,D)** para moverse.

**El juego cuenta con dos modos de juego:**
1-**Supervivencia:** resistir el mayor tiempo posible sin hundirse
2-**Misiones o Niveles:** deberá cumplir con objetivos específicos o llegar a un destino.

Los obstáculos se generaran aleatoriamente usando estructuras y la funcion **rand()**, y el submarino tiene un sistemas de **vidas** que le permite resistir varios impactos antes de perder. La interfaz gráfica se basa en caracteres **ASCII**, y se usa la función **kbhit()** de la librería **conio.h** para detectar las teclas presionadas.

Además, se guarda un récord de distancia recorrida en un archivo de texto, permitiendo llevar un seguimiento del progreso del jugador!!!.

## Equipo

- **Nombre del equipo:** Tralaleritos :skull:

### Integrantes del equipo

1. **Nombre completo:** Esteban Alejandro Mate Lúe
   **Carnet:** 00235525

2. **Nombre completo:** Yukio Alberto Ogawa Urquilla
   **Carnet:** 00171625

3. **Nombre completo:** René Alexander Moya Hernández
   **Carnet:** 00090925

4. **Nombre completo:** Javier Gerardo Mangandí Izaguirre
   **Carnet:** 00204125

## Instrucciones de Ejecución

1. Clona este repositorio en tu máquina local:
   ```bash
   git clone [URL del repositorio]
