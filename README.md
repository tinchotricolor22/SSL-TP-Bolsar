# TP WEB SCRAPING

TP de Web scraping para la materia "Sintaxis y semántica de lenguajes" de UTN FRBA.

**Integrantes**:
- Martín Morales
- Pablo Cha

**Cursada**: K2054 Jueves noche

**Repo**: [https://github.com/tinchotricolor22/SSL-TP-Bolsar](https://github.com/tinchotricolor22/SSL-TP-Bolsar "https://github.com/tinchotricolor22/SSL-TP-Bolsar")

## Introducción
Es un programa desarrollado en C que obtiene el archivo html de bolsar (o del link que se configure en la config), para parsearlo y devolver distintos reportes predefinidos. También esta la opción de exportar reportes custom, pudiendo elegir ir por el método online o filesystem, y el tipo de export, que pueden ser: imprimir en pantalla, CSV o HTML.
El comando wget viene incluido en el proyecto, en la carpeta "commands", tanto para unix como windows.

### [Manual de usuario](https://github.com/tinchotricolor22/SSL-TP-Bolsar/blob/master/doc/TP%20WEB%20SCRAPPING%20-%20Morales_Cha.pdf "Manual de usuario")

## Como correr la app?
Desde la terminal:
```bash
sudo ./SSL_TP_Bolsar
```

En modo debug:
```bash
sudo ./SSL_TP_Bolsar --debug
```

## Configuración
Se puede cambiar dentro de `resources/config.properties`:
```Java
fs_data_path = path a donde va a ir a buscar la data en el método por file system
online_data_url = url a donde va a ir a buscar la data en el método online(wget)
exporter_output_path = path donde va a dejar los reportes resultantes
csv_delimiter = delimitador a utilizar en el método de exportación CSV
```

## Arquitectura
[![arquitecture_tp.png](https://raw.githubusercontent.com/tinchotricolor22/SSL-TP-Bolsar/master/doc/images/arquitecture_tp.png "arquitecture_tp.png")](https://raw.githubusercontent.com/tinchotricolor22/SSL-TP-Bolsar/master/doc/images/arquitecture_tp.png "arquitecture_tp.png")

- **main**: punto de entrada. Se encarga de llamar a la ui, obtener las preferences para el reporte que eligió el usuario y con ellas llamar al processor. También se cargan las configuraciones necesarias desde `resources/config.properties`.
- **processor**: es el flujo principal. Se encarga de manejar el input de la respuesta entre componentes.
- **data**: obtiene el FILE* con el método que se elija (FS o WGET).
- **parser**: parsea el archivo a un array de struct de dominio. Recibe los filters necesarios para filtrar los datos que no necesita.
- **filters**: funciones que devuelven un valor booleano dependiendo la casuística de negocio.
- **exporter**: recibe la información y llama al método de exportación seleccionado, aplicando los formatos correspondientes-
- **columns**: Columnas definidas para que exporter forme la salida. Dependen de la casuística de negocio.
- **formatters**: aplica un formato condicional a un componente, dependiendo la lógica de negocio que se provea.

En la struct de dominio nos referimos a leader.h, donde tenemos un estructura para poder manejar durante el flujo del programa.

Idealmente, fuimos modularizando cada parte del proceso con la motivación de que el programa sea escalable, sencillo para agregar cambios y poder tener una mejor trazabilidad de los errores.

En cada módulo, se tiene un `header.h `con el nombre del modulo, y distintas implementaciones `impl.c` que implementan las funciones definidas en ese header.

El programa se probó en macOS, pero debería funcionar en sistemas windows u otra distro de linux. Hay una directiva de precompilación que identifica al SO.

[![directivas.png](https://raw.githubusercontent.com/tinchotricolor22/SSL-TP-Bolsar/master/doc/images/directivas.png "directivas.png")](https://raw.githubusercontent.com/tinchotricolor22/SSL-TP-Bolsar/master/doc/images/directivas.png "directivas.png")

## Compilación

Utilizamos CMake, donde tenemos que configurar el archivo CMakeLists.txt, para que incluya cada uno de los archivos fuente y los recursos en el directorio compilado que genera (cmake-build-debug). Nos pareció ir por el camino de CMake porque ya tenía una integración con el IDE CLion, y acelero el proceso de desarrollo y testing.

Por otro lado, armamos nuestro custom_makefile.sh para ejecutar con shell. El mismo utiliza gcc para compilar todos los archivos .c y genera los .o en el directorio custom_build.

## Testing
Utilizamos CTest, soportado por CMake.

## Conclusiones sobre el TP
Si bien el scope de la consigna no lo decía, nos pareció interesante mantener una mentalidad de abstracción y escalabilidad a la hora de plantear el proyecto. Esto hizo que tal vez se complejize mucho más, y por eso no llegamos a hacer todos los refactor y code smells necesarios para que queda más legible y performante. Por otro lado, nos desafió a buscar soluciones interesantes en C, donde encontramos un enriquecimiento en:
- División de responsabilidades
- Problemáticas del paradigma estructurado
- Manejo de headers
- Directivas de preprocesamiento
- Manejo de ficheros y el posicionador vs manejo de strings
- Manejo de punteros a tipos de datos
- Manejo de punteros a funciones
- Tipo de dato void*
- makefile y problemáticas de compilación

Esto fue algo que sumó, por todos los topes con los que nos encontrábamos y porque no estabamos acostumbrados, ya que los dos programamos en lenguajes con GC y otras herramientas que facilitan muchas de estas cosas.
