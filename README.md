# GEE
Generador de Excusas de Emergencia, basado en una Raspberry Pi Pico W
![Image Alt text](/images/gee_front.png)
Utilizando ChatGTP se generaron 3 listas de excusas:
- excusaFH.h: excusas debido al mal funcionamiento o problemas relacionados con Hardware y Firmware
- excusasPM.h: excusas relacionadas con el manejo del projecto (Project Managment)
- excusas_fun.h: excusas sin mucho sentido y ocurrentes.

Al presionar el pulsador se genera una nueva excusa y se van eligiendo de forma aleatoria y de manera intercalada una excusa de excusaFH.h y a continuación una de excusas_fun.h. Si se pulsa el botón y se lo mantiene presionado por más de 1 segundo y menos de 5, se generará una excusa aleatoria de la lista excusasPM.h. Si se mantiene presionada el botón por más de 5 segundos se generará una excusa...digamos...subida de tono.

Todas las partes se imprimieron en PLA. Los archivos se encuentran disponible en la carpeta STLs.
<p align="center">
  <img src="/images/front.jpg"  width="500">
</p>

Todas las conecciones se realizaron con cables del tipo Dupont.

<p align="center">
  <img src="/images/back.jpg"  width="500">
</p>
