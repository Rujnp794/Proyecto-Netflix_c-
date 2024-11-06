#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

struct Pelicula {
    string nombre;
    int duracion; //en minutos
    int cant_generos;
    string generos[100];
    int ano_estreno;
};

struct Capitulo{
    string nombre;
    int duracion; //en minutos
    int temporada;
};

struct Serie{
    string nombre;
    int num_temporadas;
    int cant_generos;
    string generos[100];
    int cant_capitulos;
    Capitulo capitulos[100];
};

//Declaracion Funciones

int leerPeliculas(string nombre_archivo, Pelicula peliculas[]);
int leerSeries(string nombre_archivo, Serie series[]);
void crearPelicula(Pelicula peliculas[]);
void crearSerie(Serie series[]);
bool sonIgualesSinMayusculas(string str1,string str2);
void agregarCapitulo(Serie series[]);
bool existeSerie(string nombre_serie , Serie series[]);

int main() {
    int opcion = 0, cant_peliculas = 0, cant_series = 0;
    string nombre_archivo;
    Pelicula peliculas[100];
    Serie series[100];

    cout << "Bienvenido a Netflix" << endl;
    cout << "¿Que desea hacer?" << endl;   
    cout << "1. Cargar peliculas" << endl;
    cout << "2. Cargar series" << endl;
    cout << "3. Crear pelicula" << endl;
    cout << "4. Crear serie" << endl;
    cout << "5. Agregar capitulo a serie" << endl;
    cout << "6. Salir" << endl;

    cin >> opcion;
    switch(opcion){
    case 1:
        {
            cout << "Digite el nombre del archivo de peliculas." << endl;
            cin >> nombre_archivo;
            cant_peliculas = leerPeliculas(nombre_archivo, peliculas);
        }
        break;
    case 2:
        {
            cout << "Digite el nombre del archivo de series." << endl;
            cin >> nombre_archivo;
            cant_series = leerSeries(nombre_archivo, series);
        }
        break;
    default:
        cout << "Opcion no valida" << endl;
        break;
    case 3:
        {
            Pelicula peliculas[100];
            crearPelicula(peliculas, cant_peliculas);
            cant_peliculas++;
        }
    }

}

//Funcion para leer las peliculas del archivo
int leerPeliculas(string nombre_archivo, Pelicula peliculas[]) {
    ifstream archivo(nombre_archivo);
    string linea;
    int contador = 0;

    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo " << nombre_archivo << endl;
        return;
    }

    // Leer la primera línea que contiene los encabezados
    getline(archivo, linea);

    // Leer cada línea del archivo
    while (getline(archivo, linea) ) {
        stringstream ss(linea);
        string nombre, duracion, ano_estreno, genero;
        int cant_generos = 0;

        // Leer los datos separados por comas
        getline(ss, nombre, ',');
        getline(ss, duracion, ',');
        getline(ss, ano_estreno, ',');

        // Leer el resto de la línea para obtener los generos
        while(getline(ss, genero, ',')){
            peliculas[contador].generos[cant_generos] = genero;
            cant_generos++;
        }

        // Crear una instancia de Pelicula y agregarla al arreglo
        peliculas[contador].nombre = nombre;
        peliculas[contador].duracion = stoi(duracion);
        peliculas[contador].ano_estreno = stoi(ano_estreno);  
        peliculas[contador].cant_generos = cant_generos;
    
        contador++;
    }

    archivo.close();

    return contador;
}

//Funcion para leer las series del archivo
int leerSeries(string nombre_archivo, Serie series[]) {
    ifstream archivo(nombre_archivo);
    string linea;
    int contador = 0;

    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo " << nombre_archivo << endl;
        return;
    }

    // Leer la primera línea que contiene los encabezados
    getline(archivo, linea);

    // Leer cada línea del archivo
    while (getline(archivo, linea) ) {
        stringstream ss(linea);
        string nombre, num_temporadas, genero;
        int cant_generos = 0;

        // Leer los datos separados por comas
        getline(ss, nombre, ',');
        getline(ss, num_temporadas, ',');
        
        // Leer el resto de la línea para obtener los generos
        while(getline(ss, genero, ',')){
            series[contador].generos[cant_generos] = genero;
            cant_generos++;
        }

        // Crear una instancia de Serie y agregarla al arreglo
        series[contador].nombre = nombre;
        series[contador].num_temporadas = stoi(num_temporadas);
        series[contador].cant_generos = cant_generos;

        contador++;
    }

    archivo.close();

    return contador;
}

// Crear una pelicula
void crearPelicula(Pelicula peliculas[], int cant_peliculas) {
    // Crear una instancia de Pelicula
    Pelicula pelicula;

    // Solicitar un nombre válido para la pelicula
    do {
        cout << "Ingrese el nombre de la pelicula: ";
        cin >> pelicula.nombre;
    } while (!nombreValidoPelicula(pelicula.nombre, peliculas, cant_peliculas));

    // Solicitar una duración válida para la pelicula
    do {
        cout << "Ingrese la duración de la pelicula: ";
        cin >> pelicula.duracion;
    } while (pelicula.duracion <= 0);

    // Solicitar los géneros de la pelicula y preguntar si desea agregar más
    int opcion = 0, i = 0;
    do {
        cout << "Ingrese el genero " << i+1 << " de la pelicula: ";
        cin >> pelicula.generos[i];
        i++;
        cout << "Desea agregar otro genero? (1. Si, 2. No)" << endl;
        cin >> opcion;
    } while (opcion == 1);
    pelicula.cant_generos = i;

    // Solicitar un año de estreno válido para la pelicula
    do {
        cout << "Ingrese el año de estreno de la pelicula: ";
        cin >> pelicula.ano_estreno;
    } while (pelicula.ano_estreno <= 0);
    
    // Todos los datos de la pelicula son validos, entonces podemos agregarla al arreglo
    peliculas[cant_peliculas] = pelicula;
}

// Función para validar que el nombre de la pelicula no esté vacío y no exista ya
bool nombreValidoPelicula(string nombre, Pelicula peliculas[], int cant_peliculas) {
    if (nombre.empty()) {
        cout << "EL NOMBRE DE LA PELICULA NO PUEDE ESTAR VACIO, INTENTE DE NUEVO." << endl;
        return false;
    }
    // Comparar el nombre de la pelicula con los nombres de las peliculas existentes (en minúsculas)
    for (int i = 0; i < cant_peliculas; i++) {
        if (sonIgualesSinMayusculas(peliculas[i].nombre, nombre)) {
            cout << "ESTA PELICULA YA EXISTE, INTENTE DE NUEVO." << endl;
            return false;
        }
    }
    return true;
}

// Función para comparar dos strings sin importar mayúsculas y minúsculas
bool sonIgualesSinMayusculas(string str1, string str2) {
    if (str1.length() != str2.length()) {
        return false;
    }
    for (int i = 0; i < str1.length(); i++) {
        if (tolower(str1[i]) != tolower(str2[i])) {
            return false;
        }
    }
    return true;
}

// Crear una serie
void crearSerie(Serie series[], int cant_series) {
    // Crear una instancia de Serie
    Serie serie;

    // Solicitar un nombre válido para la serie
    do {
        cout << "Ingrese el nombre de la serie: ";
        cin >> serie.nombre;
    } while (!nombreValidoSerie(serie.nombre, series, cant_series));

    // Solicitar un número de temporadas válido para la serie
    do {
        cout << "Ingrese el número de temporadas de la serie: ";
        cin >> serie.num_temporadas;
    } while (serie.num_temporadas <= 0);

    // Solicitar los géneros de la serie y preguntar si desea agregar más
    int opcion = 0, i = 0;
    do {
        cout << "Ingrese el genero " << i+1 << " de la serie: ";
        cin >> serie.generos[i];
        i++;
        cout << "Desea agregar otro genero? (1. Si, 2. No)" << endl;
        cin >> opcion;
    } while (opcion == 1);
    serie.cant_generos = i;
    serie.cant_capitulos = 0;

    // Todos los datos de la serie son validos, entonces podemos agregarla al arreglo
    series[cant_series] = serie;
}

// Función para validar que el nombre de la serie no esté vacío y no exista ya
bool nombreValidoSerie(string nombre, Serie series[], int cant_series) {
    if (nombre.empty()) {
        cout << "EL NOMBRE DE LA SERIE NO PUEDE ESTAR VACIO, INTENTE DE NUEVO." << endl;
        return false;
    }
    // Comparar el nombre de la serie con los nombres de las series existentes (en minúsculas)
    for (int i = 0; i < cant_series; i++) {
        if (sonIgualesSinMayusculas(series[i].nombre, nombre)) {
            cout << "ESTA SERIE YA EXISTE, INTENTE DE NUEVO." << endl;
            return false;
        }
    }
    return true;
}

//Añadir un nuevo capitulo a una serie que ya existe
void agregarCapitulo(Serie series[], int cant_series) {
    // Crear una instancia de Capitulo
    Capitulo capitulo;
    string nombre_serie;
    bool valido = false;
    int pos_serie = 0, opcion = 0;

    // Solicitar el nombre de la serie a la que se le quiere agregar un capítulo
    do {
        cout << "Ingrese el nombre de la serie a la que desea agregar un capítulo: ";
        cin >> nombre_serie;
        if (nombre_serie.empty()) {
            cout << "EL NOMBRE DE LA SERIE NO PUEDE ESTAR VACIO, INTENTE DE NUEVO." << endl;
        } else {
            pos_serie = buscarSerie(nombre_serie, series, cant_series);
            if (pos_serie == -1) {
                cout << "ESTA SERIE NO EXISTE, INTENTE DE NUEVO." << endl;
            } else {
                valido = true;
            }
        }
    } while (!valido);

    // Solicitar un nuevo capítulo hasta que el usuario decida parar
    do {
        // Solicitar un nombre válido para el capítulo
        do {
            cout << "Ingrese el nombre del capítulo: ";
            cin >> capitulo.nombre;
        } while (!nombreValidoCapitulo(capitulo.nombre, series[pos_serie].capitulos, series[pos_serie].cant_capitulos));
        // Solicitar una duración válida para el capítulo
        do {
            cout << "Ingrese la duración del capítulo: ";
            cin >> capitulo.duracion;
        } while (capitulo.duracion <= 0);
        // Solicitar una temporada válida para el capítulo
        do {
            cout << "Ingrese la temporada del capítulo: ";
            cin >> capitulo.temporada;
        } while (capitulo.temporada <= 0 || capitulo.temporada > series[pos_serie].num_temporadas);
        // Todos los datos del capítulo son válidos, entonces podemos agregarlo a la serie
        series[pos_serie].capitulos[series[pos_serie].cant_capitulos] = capitulo;
        // Y aumentar la cantidad de capítulos de la serie
        series[pos_serie].cant_capitulos++;
        // Preguntar si desea agregar otro capítulo
        cout << "Capítulo(s) agregado(s) exitosamente." << endl;
        cout << "Desea agregar otro capítulo a la serie " << series[pos_serie].nombre << "? (1. Si, 2. No)" << endl;
        cin >> opcion;
    } while (opcion == 1);
}

//Funcion para buscar una serie en la lista de series y retornar su posicion
int buscarSerie(string nombre_serie , Serie series[], int cant_series){
    for(int i = 0; i < cant_series; i++){
        if(sonIgualesSinMayusculas(series[i].nombre, nombre_serie)){
            return i;
        }
    }
    return -1;
}

// Funcion para validar que el nombre del capitulo no este vacio y no exista ya
bool nombreValidoCapitulo(string nombre, Capitulo capitulos[], int cant_capitulos) {
    if (nombre.empty()) {
        cout << "EL NOMBRE DEL CAPITULO NO PUEDE ESTAR VACIO, INTENTE DE NUEVO." << endl;
        return false;
    }
    // Comparar el nombre del capitulo con los nombres de los capitulos existentes (en minúsculas)
    for (int i = 0; i < cant_capitulos; i++) {
        if (sonIgualesSinMayusculas(capitulos[i].nombre, nombre)) {
            cout << "ESTE CAPITULO YA EXISTE, INTENTE DE NUEVO." << endl;
            return false;
        }
    }
    return true;
}

// Función para listar los capítulos de una serie y una temporada
void listarCapitulosPorTemporada(Serie series[], int cant_series) {
    string nombre_serie;
    int temporada;
    bool valido = false;
    int pos_serie = -1;

    // Solicitar el nombre de la serie a la que se le quiere listar los capítulos
    do {
        cout << "Ingrese el nombre de la serie a la que desea listar los capítulos: ";
        cin >> nombre_serie;
        if (nombre_serie.empty()) {
            cout << "EL NOMBRE DE LA SERIE NO PUEDE ESTAR VACIO, INTENTE DE NUEVO." << endl;
        } else {
            pos_serie = buscarSerie(nombre_serie, series, cant_series);
            if (pos_serie == -1) {
                cout << "LA SERIE INGRESADA NO EXISTE, INTENTE DE NUEVO." << endl;
            } else {
                valido = true;
            }
        }
    } while (!valido);

    // Solicitar la temporada de la que se quieren listar los capítulos
    do {
        cout << "Ingrese la temporada de la que desea listar los capítulos: ";
        cin >> temporada;
        if (temporada <= 0 || temporada > series[pos_serie].num_temporadas) {
            cout << "LA TEMPORADA INGRESADA NO EXISTE, INTENTE DE NUEVO." << endl;
        }
    } while (temporada <= 0 || temporada > series[pos_serie].num_temporadas);

    // Si la serie no tiene capítulos, mostrar un mensaje
    if (series[pos_serie].cant_capitulos == 0) {
        cout << "A la serie " << series[pos_serie].nombre << " no le han agregado capítulos aún." << endl;
    } else {
        cout << "Capítulos de la temporada " << temporada << " de la serie " << series[pos_serie].nombre << ":" << endl;
        for (int i = 0; i < series[pos_serie].cant_capitulos; i++) {
            if (series[pos_serie].capitulos[i].temporada == temporada) {
                cout << "Nombre: " << series[pos_serie].capitulos[i].nombre << endl;
                cout << "Duración: " << series[pos_serie].capitulos[i].duracion << " minutos" << endl;
            }
        }
    }
}
