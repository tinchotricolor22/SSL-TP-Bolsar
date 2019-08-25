# TP WEB SCRAPING

TP de Web scraping para la materia "Sintaxis y semántica de lenguajes" de UTN FRBA.

**Integrantes**:
- Martín Morales
- Pablo Cha

**Cursada**: K2054 Jueves noche

**Repo**: [https://github.com/tinchotricolor22/SSL-TP-Bolsar](https://github.com/tinchotricolor22/SSL-TP-Bolsar "https://github.com/tinchotricolor22/SSL-TP-Bolsar")

## Como correr la app?
Desde la terminal:
```bash
sudo ./SSL_TP_Bolsar
```

En modo debug:
```bash
sudo ./SSL_TP_Bolsar --debug
```

### [Manual de usuario](https://github.com/tinchotricolor22/SSL-TP-Bolsar/blob/develop/doc/TP%20WEB%20SCRAPPING%20-%20Morales_Cha.pdf "Manual de usuario")



## Arquitectura
[![arquitecture.png](https://raw.githubusercontent.com/tinchotricolor22/SSL-TP-Bolsar/develop/doc/images/arquitecture_tp.png "arquitecture.png")](https://raw.githubusercontent.com/tinchotricolor22/SSL-TP-Bolsar/develop/doc/images/arquitecture_tp.png "arquitecture.png")

- **main**: punto de entrada. Se encarga de llamar a la ui, obtener las preferences para el reporte que eligió el usuario y con ellas llamar al processor. También se cargan las configuraciones necesarias desde `resources/config.properties`.
- **processor**: es el flujo principal. Se encarga de manejar el input de la respuesta entre componentes.
- **data**: obtiene el FILE* con el método que se elija (FS o WGET). 
- **parser**: parsea el archivo a un array de struct de dominio. Recibe los filters necesarios para filtrar los datos que no necesita.
- **filters**: funciones que devuelven un valor booleano dependiendo la casuística de negocio.
- **exporter**: recibe la información y llama al método de exportación seleccionado, aplicando los formatos correspondientes-
- **columns**: Columnas definidas para que exporter forme la salida. Dependen de la casuística de negocio.
- **formatters**: aplica un formato condicional a un componente, dependiendo la lógica de negocio que se provea.

En la struct de dominio nos referimos a leader.h, donde tenemos un estructura para poder manejar durante el flujo del programa.

El programa se probó en macOS, pero debería funcionar en sistemas windows u otra distro de linux. Hay una directiva de precompilación que identifica el SO.

