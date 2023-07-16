#include <iostream>
#include <conio.h>
#include <iomanip>
#include <vector>
#include <windows.h>
#include <fstream>
#include <thread>
#include <algorithm>

#define ENTER 13
#define BACKSPACE 8
#define INTENTOS 5

using namespace std;
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

// PROTOTIPOS DE LAS FUNCIONES
void dibujarCuadro(int x1, int y1, int x2, int y2);
void gotoxy(int x, int y);
void CursorOn(bool visible, DWORD size);
void CursorOff();
void limpia();
void cambio(char a[]);
void login();
void leerPasw(char frase[]);
void menu();

// FUNCION PRINCIPAL MAIN: Aqui dentro de main llamamos a las demas funciones.
int main()
{
    system("cls");
    system("COLOR F0");
    dibujarCuadro(0, 0, 78, 24); // Cuadro grande
    dibujarCuadro(1, 1, 77, 3);  // Cuadro del titulo
    CursorOff();
    gotoxy(16, 2);

    string titulo, usuario, clave, usuaadmi, claveadmi, nuevo_titulo, nuevo_usuario, nueva_clave, nuevo_usuaadmi, nuevo_claveadmi;

    ifstream archivo("credencial.txt");
    getline(archivo, titulo);
    getline(archivo, usuario);
    getline(archivo, clave);
    getline(archivo, usuaadmi);
    getline(archivo, claveadmi);
    cout << "\t\t" << titulo << endl;
    login();

    getch();
    return 0;
}

// FUNCION LOGIN: Se crean 2 variables, de usuario y contraseña y se comparan para mostrar sus respectivos mensajes
void login()
{
    CursorOn(1, 10);
    string titulo, usuario, clave, usuaadmi, claveadmi, nuevo_titulo, nuevo_usuario, nueva_clave, nuevo_usuaadmi, nuevo_claveadmi;

    ifstream archivo("credencial.txt");
    getline(archivo, titulo);
    getline(archivo, usuario);
    getline(archivo, clave);
    getline(archivo, usuaadmi);
    getline(archivo, claveadmi);
    archivo.close();

    char usserr[usuario.length() + 1];
    strcpy(usserr, usuario.c_str());
    char a[10];
    strncpy(a, usserr, 10);

    char contrra[clave.length() + 1];
    strcpy(contrra, clave.c_str());
    char clave1[10];
    strncpy(clave1, contrra, 10);

    
    char user2[20], contra2[20];
    int x = 1000;
    int f = 41;

    gotoxy(35, 6);
    printf("ACCESO");
    dibujarCuadro(18, 9, 60, 15);
    gotoxy(23, 11);
    printf("Usuario: ");
    fgets(user2, 20, stdin);
    cambio(user2);

    gotoxy(23, 13);
    printf("Clave:   ");
    leerPasw(contra2);

    CursorOff();

    for (int i = 0; i < 3; i++)
    {
        gotoxy(33, 19);
        printf("Cargando");
        gotoxy(f, 19);
        printf(".");
        f += 1;
        Sleep(x);
    }

    f = 51;

    if ((strcmp(user2, a)) == 0 && (strcmp(contra2, clave1)) == 0)
    {
        gotoxy(30, 19);
        printf("                                     ");
        for (int i = 0; i < 3; i++)
        {
            gotoxy(30, 19);
            printf("Accediendo al Sistema");
            gotoxy(f, 19);
            printf(".");
            f += 1;
            Sleep(x);
        }
        limpia();
        menu();
    }

    else
    {
        gotoxy(35, 19);
        printf("                                     ");
        gotoxy(30, 19);
        printf("Datos incorrectos");
        gotoxy(18, 20);
        printf("Presione una tecla para volver a ingresar..");
        getch();
        limpia();
        login();
    }
}

// FUNCION LEER CONTRASEñA: proceso que permite mostrar asteriscos en la contraseña
void leerPasw(char frase[])
{
    int i = 0;
    cout.flush();
    int aux = 0;

    do
    {
        frase[i] = (unsigned char)getch();

        if (frase[i] != 8) // no es retroceso
        {
            cout << '*'; // muestra por pantalla
            i++;

            if (frase[i - 1] == 13)
            {
                printf("\b \b");
            }
        }

        else if (i > 0) // es retroceso y hay caracteres
        {
            cout << (char)8 << (char)32 << (char)8;
            i--; // el caracter a borrar e el backspace
        }

        cout.flush();

    } while (frase[i - 1] != 13); // si presiona ENTER

    frase[i - 1] = 0;
}

// FUNCION CAMBIO: Cambia el caracter \n por \0
void cambio(char a[])
{
    int aux;
    aux = strlen(a);
    a[aux - 1] = '\0';
}
//*********************************************
class Caja {
private:
    int id;
    string productoVendido;

public:
    Caja(int id) : id(id) {}

    int getID() const {
        return id;
    }

    string getProductoVendido() const {
        return productoVendido;
    }

    void setProductoVendido(const string& producto) {
        productoVendido = producto;
    }
};
//*********************************************
struct Producto {
    string nombre;
    string codigo;
    double precio;
    double preciocomp;
    int cantidad;
};
//*********************************************
class Tienda {
private:
    vector<Producto> productos;
    string nombreArchivo;

public:
    Tienda(const string& archivo) : nombreArchivo(archivo) {
        productos = leerProductosDesdeArchivo();
    }

    void guardarProductosEnArchivo() {
        ofstream archivo(nombreArchivo);

        if (!archivo.is_open()) {
            cout << "No se pudo abrir el archivo " << nombreArchivo << " para guardar los productos." << endl;
            return;
        }

        for (const Producto& producto : productos) {
            archivo << producto.nombre << " " << producto.codigo << " " << producto.precio << " " << producto.preciocomp << " " << producto.cantidad << endl;
        }
        archivo.close();
    }

    vector<Producto> leerProductosDesdeArchivo() {
        vector<Producto> productos;
        ifstream archivo(nombreArchivo);

        if (!archivo.is_open()) {
            cout << "No se pudo abrir el archivo " << nombreArchivo << endl;
            return productos;
        }

        string nombre;
        string codigo;
        double precio;
        double preciocomp;
        int cantidad;

        while (archivo >> nombre >> codigo >> precio >> preciocomp >> cantidad) {
            Producto producto;
            producto.nombre = nombre;
            producto.codigo = codigo;
            producto.precio = precio;
            producto.preciocomp = preciocomp;
            producto.cantidad = cantidad;
            productos.push_back(producto);
        }

        archivo.close();
        return productos;
    }

    void mostrarRegistro() {
        cout << "=== REGISTRO DE PRODUCTOS ===" << endl;
        if (productos.empty()) {
            cout << "No hay productos registrados." << endl;
            return;
        }

        for (const Producto& producto : productos) {
            cout << "Nombre: " << producto.nombre << endl;
            cout << "Codigo: " << producto.codigo << endl;
            cout << "Precio: " << producto.precio << endl;
            cout << "Precio de compra: " << producto.preciocomp << endl;
            cout << "Cantidad: " << producto.cantidad << endl;
            cout << "---------------------------" << endl;
        }
    }

    int buscarProducto(const string& codigo) {
        for (int i = 0; i < productos.size(); i++) {
            if (productos[i].codigo == codigo) {
                return i;
            }
        }
        return -1;
    }

    void modificarProducto(const string& codigo) {
        int indice = buscarProducto(codigo);

        if (indice != -1) {
            cout << "Producto encontrado." << endl;
            Producto& producto = productos[indice];

            cout << "Nuevo nombre: ";
            cin >> producto.nombre;
            cout << "Nuevo precio: ";
            cin >> producto.precio;
            cout << "Producto modificado exitosamente." << endl;
        } else {
            cout << "Producto no encontrado." << endl;
        }
    }

    void eliminarProducto(const string& codigo) {
        int indice = buscarProducto(codigo);

        if (indice != -1) {
            cout << "Producto encontrado." << endl;
            productos.erase(productos.begin() + indice);
            cout << "Producto eliminado exitosamente." << endl;
        } else {
            cout << "Producto no encontrado." << endl;
        }
    }

    void mostrarBoleta(const vector<Producto>& carrito, double totalVenta) {

        cout << "\tProductos comprados:" << endl;
        cout << setfill('-') << setw(60) << "-" << setfill(' ') << endl;
        cout << setw(10) << left << "\tCodigo" << setw(10) << left << "Nombre" << setw(5) << right << "Precio" << setw(5) << right << "Cantidad" << setw(10) << right << "Total" << endl;
        cout << setfill('-') << setw(60) << "-" << setfill(' ') << endl;
        for (const Producto& producto : carrito) {
            double totalProducto = producto.precio * producto.cantidad;

            cout << "\t" << setw(10) << left << producto.codigo;
            cout << setw(10) << left << producto.nombre;
            cout << setw(5) << right << fixed << setprecision(2) << producto.precio;
            cout << setw(5) << right << producto.cantidad;
            cout << setw(10) << right << fixed << setprecision(2) << totalProducto << endl;
        }

    }

    void vender()
    {
        auto now = std::chrono::system_clock::now();
        time_t end_time = std::chrono::system_clock::to_time_t(now);

        float total = 0.0;
        bool finalizar = false;
        vector<Producto> carrito;

        while (!finalizar)
        {
            bool encontrado = false;
            string codigo;
            cout << "Ingrese el codigo del producto (0 para finalizar la compra): ";
            cin >> codigo;
            int indice = buscarProducto(codigo);
            int cantidad;
            cout << "Ingrese la cantidad de productos: ";
            cin >> cantidad;
            if (codigo == "0")
            {
                finalizar = true;
            }
            else if (cantidad <= productos[indice].cantidad)
            {

                Producto producto = productos[indice];
                producto.cantidad = cantidad;
                carrito.push_back(producto);
                productos[indice].cantidad -= cantidad;
            }
            else
            {
                cout << "Producto no encontrado." << endl;
            }

        }
        string nomcliente;
        cout << "Ingrese el nombre del cliente: ";
        cin >> nomcliente;

        system("cls");
        cout << "///////////////////////////////////////////" << endl;
        cout << "\tHUANUCO - Leoncio prado - Rupa Rupa" << endl;
        cout << "\tAV.ENRIQUE PIMENTEL - TINGO MARIA" << endl;
        cout << "------------- Boleta de Venta ------------" << endl;
        cout << "\tCliente: " << nomcliente << endl;
        cout << "\tFecha y hora: " << ctime(&end_time) << endl;
        double totalVenta = 0;
        for (const Producto& producto : carrito) {
            double totalProducto = producto.precio * producto.cantidad;
            totalVenta += totalProducto;
        }
        mostrarBoleta(carrito, totalVenta);
        carrito.clear();
        cout << "------------------------------------------" << endl;
        cout << "Solicite su comprobante de pago correspondiente." << endl;
        cout << "Total de la compra: $" << fixed << setprecision(2) << totalVenta << endl;
        cout << "///////////////////////////////////////////" << endl;

        guardarProductosEnArchivo();
    }
    double calcularGastos()
    {
        double gastos = 0.0;

        for (const Producto &producto : productos)
        {
            gastos += producto.preciocomp * producto.cantidad;
        }
        return gastos;
    }

    double calcularIngresos()
    {
        double ingresos = 0.0;
        for (const Producto &producto : productos)
        {
            ingresos += producto.precio * producto.cantidad;
        }
        return ingresos;
    }

    double calcularGanancias()
    {
        double gastos = calcularGastos();
        double ingresos = calcularIngresos();

        return ingresos - gastos;
    }

    void mostrarGastosIngresosGanancias()
    {
        double gastos = calcularGastos();
        double ingresos = calcularIngresos();
        double ganancias = calcularGanancias();

        cout << "=== GASTOS, INGRESOS Y GANANCIAS ===" << endl;
        cout << "Gastos totales: $" << fixed << setprecision(2) << gastos << endl;
        cout << "Ingresos totales: $" << fixed << setprecision(2) << ingresos << endl;
        cout << "Ganancias totales: $" << fixed << setprecision(2) << ganancias << endl;
    }
    void agregarProducto(const Producto& nuevoProducto) {
        productos.push_back(nuevoProducto);
        cout << "Producto agregado exitosamente." << endl;
    }
};
//*********************************************
// Función para guardar las cajas en un archivo
void guardarCajas(const vector<Caja>& cajas) {
    ofstream archivo("caja.txt");

    if (archivo.is_open()) {
        for (const auto& caja : cajas) {
            archivo << caja.getID() << "," << caja.getProductoVendido() << endl;
        }

        archivo.close();
        cout << "Cajas guardadas correctamente." << endl;
    } else {
        cout << "Error al abrir el archivo." << endl;
    }
}

// Función para cargar las cajas desde un archivo
vector<Caja> cargarCajas() {
    vector<Caja> cajas;
    ifstream archivo("caja.txt");

    if (archivo.is_open()) {
        string linea;
        while (getline(archivo, linea)) {
            string idStr, producto;
            istringstream iss(linea);
            getline(iss, idStr, ',');
            getline(iss, producto);

            int id = stoi(idStr);
            cajas.push_back(Caja(id));
            cajas.back().setProductoVendido(producto);
        }

        archivo.close();
        cout << "Cajas cargadas correctamente." << endl;
    } else {
        cout << "Error al abrir el archivo. No se cargaron cajas." << endl;
    }

    return cajas;
}
//*********************************************
//  ESTA FUNCION LA HICE DE PRUEBA SOLO PARA MOSTRAR MENSAJES, AQUI DEBEN COLOCAR EL PROGRAMA QUE USTEDES DESEAN
void menu()
{
    system("cls");
    system("color 70");
    int ep,gf,cj,ec;
    int admip, cuentap;
    int opcion, opcion2, opcion3;
    int nprdts = 0, opcion_prdts;
    string usuarioIngresado, contrasenaIngresada;
    
    bool usuarioValido = false;
    
    string titulo, usuario, clave, usuaadmi, claveadmi, nuevo_titulo, nuevo_usuario, nuevo_clave, nuevo_usuaadmi, nuevo_claveadmi;

    ifstream archivo("credencial.txt");
    getline(archivo, titulo);
    getline(archivo, usuario);
    getline(archivo, clave);
    getline(archivo, usuaadmi);
    getline(archivo, claveadmi);
    archivo.close();

    string usuari, password, usua;

	Tienda tienda("producto.txt");
    vector<Caja> cajas = cargarCajas();
    vector<Producto> carrito;
    
    int contador = 0;
    bool ingresa = false;

    do
    {
        system("cls");
        cout << "\n\t\t\t   SISTEMA DE VENTAS    \n"; /* elegir lo que desea realizar */
        cout << "\t\t\t  -------------------\n\n";
        cout << "\t(1) administrador\n"; /* es una cuenta privada */
        cout << "\t(2) caja\n";
        cout << "\t(3) salir\n";
        cin >> opcion;

        switch (opcion)
        {

        case 1:
        	
            	do {
        			
        			cout << "Ingrese su nombre de usuario: ";
        			cin >> usuarioIngresado;
        			cout << "Ingrese su contrasena: ";
        
        			
        			char caracter;
        			contrasenaIngresada = "";
        			while ((caracter = _getch()) != '\r') { 
            			if (caracter == '\b') { 
                			if (contrasenaIngresada.length() > 0) {
                    			contrasenaIngresada.erase(contrasenaIngresada.length() - 1);
                    			cout << "\b \b"; 
                			}
            			} else {
                			contrasenaIngresada += caracter;
                			cout << "*"; 
            			}
        			}
        			cout << endl;
        
        			if (usuarioIngresado == usuaadmi && contrasenaIngresada == claveadmi) {
            			cout << "Cargando";
            			for (int i = 0; i < 3; i++) {
                			this_thread::sleep_for(chrono::seconds(1));
                			cout << ".";
                			cout.flush();
            			}
            			cout << endl;
            			cout << "Bienvenido, " << usuarioIngresado << endl;
            			usuarioValido = true;
        			} else {
            			cout << "Nombre de usuario o contrasena incorrectos. Intente nuevamente." << endl;
        			}
        
    			} while (!usuarioValido);
			do
            {
                // lo que administrador desea realizar
                system("cls");
                cout << "\n\tADMINISTRADOR\n";
            	cout << "\t(1) PERFIL(tienda)\n";
                cout << "\t(2) CUENTA(edit)\n";
                cout << "\t(3) ESTABLECIMIENTO DE PRECIOS\n";
                cout << "\t(4) GESTION FINANCIERO\n";
                cout << "\t(5) GESTION DE INVENTARIO\n";
                cout << "\t(6) edit(CAJA)\n";
                cout << "\t(7) atras\n";
                cout << "\n\tQue desea realizar?\t";
                cin >> opcion_prdts;
                switch (opcion_prdts)
                {
                case 1:
                    do{
                        system("cls");
                        cout << "\n\tPERFIL\n";
                        cout << "\t(1)EDITAR NOMBRE(TIENDA)\n";
                        cout << "\t(2)EDITAR INICIO SESSION (usuario y clave)\n";
                        cout << "\t(3) atras\n";
                        cin >> admip;
                        switch (admip)
                        {
                        case 1:
                        	system("cls");
                            cout << "\n\tN: tienda\n";
                            cout << "titulo actual: " << titulo << endl;
                            cout << "Ingrese un nuevo titulo: ";
                            cin >> titulo;

                            do{
                            	system("cls");
                            	cout << "\n\t(1) ATRAS";
                            	cin >> opcion3;
                            	opcion2 = 1;
							}while(opcion3 !=1);
                            
                            break;
                        case 2:
                        	system("cls");
                            cout << "\n\t(usuario y contraseña)\n";
                            cout << "Nombre de usuario actual: " << usuario << endl;
                            cout << "clave actual: " << clave << endl;
                            cout << "Ingrese un nuevo nombre de usuario: ";
                            cin >>usuario;
                            cout << "Ingrese una nueva clave: ";
                            cin >> clave;
                            
                            do{
                            	system("cls");
                            	cout << "\n\t(1) ATRAS";
                            	cin >> opcion3;
                            	opcion2 = 1;
							}while(opcion3 !=1);
                            
                            break;
                        case 3:
                        	opcion3 = 2;
                    		opcion2 = 1;
                    		break;
                        }
                        
                    }while (admip!=3);
                   
                    break;
                case 2:
                    do{
                        system("cls");
                        cout << "\n\tCUENTAS\n";
                        cout << "\t(1)EDITAR ADMINITRADOR\n";
                        cout << "\t(2) atras\n";
                        cin >> cuentap;
                        switch (cuentap)
                        {
                        case 1:
                            cout << "\n\tEDITAR(administrador)\n";
                            cout << "Nombre de usuario actual: " << usuaadmi << endl;
                            cout << "clave actual: " << claveadmi << endl;
                            cout << "Ingrese un nuevo nombre de usuario1: ";
                            cin >> usuaadmi;
                            cout << "Ingrese una nueva clave : ";
                            cin >> claveadmi;
                            
                            do{
                            	system("cls");
                            	cout << "\n\t(1) ATRAS";
                            	cin >> opcion3;
                            	opcion2 = 1;
							}while(opcion3 !=1);
                            
                        	break;
                        case 2:
							opcion3 = 2;
							opcion2 = 1;
                            break;
                        }
                    }while (cuentap != 2);
                	
                    break;
				case 3:
					do{
						system("cls");
						cout << "\n\tESTABLECIMIENTO DE PRECIOS(productos)\n";
                    	cout << "\t(1)AGREGAR(producto)\n";
                    	cout << "\t(2)MODIFICRA(producto)\n";
                    	cout << "\t(3)ELIMINAR(producto)\n";
                		cout << "\t(4) atras\n";
                	    cin>>ep;
                	    switch(ep){
                	    case 1:
                	    	{
                	    		system("cls");
                    			Producto nuevoProducto;
                    			cout << "Ingrese el nombre del producto: ";
                    			cin >> nuevoProducto.nombre;
                    			cout << "Ingrese el codigo del producto: ";
                    			cin >> nuevoProducto.codigo;
                    			cout << "Ingrese el precio del producto: ";
                    			cin >> nuevoProducto.precio;
                    			cout << "Ingrese el precio de compra del producto: ";
                    			cin >> nuevoProducto.preciocomp;
                    			cout << "Ingrese la cantidad deseada del producto: ";
                    			cin >> nuevoProducto.cantidad;

                    			tienda.agregarProducto(nuevoProducto);
                    			cout << "Producto agregado exitosamente." << endl;
                			}
                	    	do{
                	    		
                            	system("cls");
                            	cout << "\n\t(1) ATRAS";
                            	cin >> opcion3;
                            	opcion2 = 1;
							}while(opcion3 !=1);
                	    	break;
                	    case 2:
                	    	{
                	    		system("cls");
                    			string codigo;
                    			cout << "Ingrese el codigo del producto a modificar: ";
                    			cin >> codigo;
                    			tienda.modificarProducto(codigo);
                			}
                	    	do{
                            	system("cls");
                            	cout << "\n\t(1) ATRAS";
                            	cin >> opcion3;
                            	opcion2 = 1;
							}while(opcion3 !=1);
                	    	break;
                	    case 3:{
                	    	string codigo;
                    		cout << "Ingrese el codigo del producto a eliminar: ";
                    		cin >> codigo;
                    		tienda.eliminarProducto(codigo);
                	    	break;
							}
                	    case 4:
                	    	opcion3 = 2;
                        	opcion2 = 1;
                	    	break;
						}
					}while (ep != 4);
					
					break;
				case 4:
					do{
						system("cls");
						cout << "\n\tGESTION FINANCIERO\n";
                	    cout << "\t(1)GASTOS, INGRESO Y GANANCIA\n";
                	    cout << "\t(2)VER VENTAS DE UNA CAJA\n";//ojo--*-*-*-*-*-*
                	    cout << "\t(3) atras\n";
                	    
                	    cin>>gf;
                	    switch(gf){
                	    case 1:
                	    	tienda.mostrarGastosIngresosGanancias();
                	    	system("pause");
                	    	do{
                            	system("cls");
                            	cout << "\n\t(1) ATRAS";
                            	cin >> opcion3;
                            	opcion2 = 1;
							}while(opcion3 !=1);
                	    	break;

                	    case 2:{
                	    	system("cls");
                			int id;
                			cout << "Ingrese el ID de la caja: ";
                			cin >> id;
							double totalVenta;
                			auto it = find_if(cajas.begin(), cajas.end(), [id](const Caja& caja) {
                    			return caja.getID() == id;
                			});

                			if (it != cajas.end()) {
                				
                    			cout << "Ventas de la caja " << it->getID() << ": " << it->getProductoVendido() << endl;
                    			tienda.mostrarBoleta(carrito,totalVenta);
                    			
                			} else {
                    			cout << "No se encontro la caja con ID " << id << endl;
                			}
                			system("pause");
                			do{
                            	system("cls");
                            	cout << "\n\t(1) ATRAS";
                            	cin >> opcion3;
                            	opcion2 = 1;
							}while(opcion3 !=1);
                
            				}
                	    	break;
                	    case 3:
                	    	opcion3 = 2;
                        	opcion2 = 1;
                        	break;
						}
					}while(gf!=3);
					
					break;
					
				case 5:
					system("cls");
					cout << "\n\tGESTION DE INVENTARIO\n";
					tienda.mostrarRegistro();
                    system("pause");
                    do{
                        system("cls");
                        cout << "\n\t(1) ATRAS";
                        cin >> opcion3;
                        opcion2 = 1;
					}while(opcion3 !=1);
					break;
				case 6:
					do{
						
					
						system("cls");
						cout << "\n\tEDIT(CAJA)\n";
						cout << "1. Crear caja" << endl;
        				cout << "2. Borrar caja" << endl;
        				cout << "3. Mostrar cantidad de cajas creadas" << endl;
        				cout << "4. atras"<<endl;
        				cout << "Ingrese una opcion: ";
        				cin>>ec;
        				switch(ec){
        					case 1:{
        						system("cls");
        						int id;
                				cout << "Ingrese el ID de la caja: ";
                				cin >> id;
                				cajas.push_back(Caja(id));
                				cout << "Caja creada correctamente." << endl;
                				do{
                      		  		system("cls");
                        			cout << "\n\t(1) ATRAS";
                        			cin >> opcion3;
                        			opcion2 = 1;
								}while(opcion3 !=1);
                				break;
                			
							}
        					case 2:{
        						system("cls");
        						int id;
                				cout << "Ingrese el ID de la caja a borrar: ";
                				cin >> id;

                				auto it = find_if(cajas.begin(), cajas.end(), [id](const Caja& caja) {
                    				return caja.getID() == id;
                				});

                				if (it != cajas.end()) {
                				    cajas.erase(it);
                				    cout << "Caja borrada correctamente." << endl;
                				} else {
                				    cout << "No se encontro la caja con ID " << id << endl;
                				}
                				do{
                        			system("cls");
                        			cout << "\n\t(1) ATRAS";
                        			cin >> opcion3;
                        			opcion2 = 1;
								}while(opcion3 !=1);
								break;
							}	
        					case 3:
        						system("cls");
        						cout << "Cantidad de cajas creadas: " << cajas.size() << endl;
        						system("pause");
        						do{
                        			system("cls");
                        			cout << "\n\t(1) ATRAS";
                        			cin >> opcion3;
                       		 		opcion2 = 1;
								}while(opcion3 !=1);
								break;	
        					case 4:
        						opcion3 = 2;
                        		opcion2 = 1;
        						break;
						}	
					}while(ec !=4);
					break;	
                case 7:
                	opcion3 = 2;
                    opcion2 = 1;
                    break;
                }
            }while (opcion_prdts != 7);
            break;

        case 2:
            /* caja */
            do{
            	system("cls");
				cout << "\n\tCAJA\n";
        	    cout << "\t(1)realizar ventas\n";
        	    cout << "\t(2)buscar producto\n";
        	    cout << "\t(3) atras\n";
        	    cin>>cj;
        	    switch(cj){
        	    case 1:{
                	int id;
                	cout << "Ingrese el ID de la caja: ";
                	cin >> id;

                	auto it = find_if(cajas.begin(), cajas.end(), [id](const Caja& caja) {
                	    return caja.getID() == id;
                	});

                	if (it != cajas.end()) {
                	    tienda.vender();
                	    cout << "Venta registrada correctamente." << endl;
                	} else {
                	    cout << "No se encontro la caja con ID " << id << endl;
                	}
                	system("pause");
                	do{
                    	system("cls");
                        cout << "\n\t(1) ATRAS";
                        cin >> opcion3;
                        opcion2 = 1;
					}while(opcion3 !=1);
        	    	break;
            	}
                	
        	    case 2:
        	    	{
            		string codigo;
            		cout << "Ingrese el codigo del producto a buscar: ";
            		cin >> codigo;
            		int indice = tienda.buscarProducto(codigo);
            		if (indice != -1)
            		{
            		    cout << "Producto encontrado en el indice: " << indice << endl;
            		    // Realizar las acciones correspondientes con el producto encontrado
            		}
            		else
            		{
            		    cout << "Producto no encontrado." << endl;
            		}
            		do{
                        system("cls");
                        cout << "\n\t(1) ATRAS";
                        cin >> opcion3;
                        opcion2 = 1;
					}while(opcion3 !=1);
        	    	break;
        		}	
        	    case 3:
        	    	opcion3 = 2;
                    opcion2 = 1;
        	    	break;
				}
			}while(cj !=3);
            
            break;
        case 3:
			guardarCajas(cajas);
            ofstream archivo_salida("credencial.txt");
    		archivo_salida << titulo << endl;
    		archivo_salida << usuario << endl;
    		archivo_salida << clave << endl;
    		archivo_salida << usuaadmi << endl;
    		archivo_salida << claveadmi << endl;
    		archivo_salida.close();
        	exit(0);
        	break;
        }
        
    }while (opcion2 == 1);
    
}
    //************************************FUNCIONES ADICIONALES************************************************************

    // FUNCION GOTOXY: Permite posicionar en pantalla mediante coordenadas X/Y
    void gotoxy(int x, int y)
    {
        HANDLE hcon;
        hcon = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD dwPos;
        dwPos.X = x;
        dwPos.Y = y;
        SetConsoleCursorPosition(hcon, dwPos);
    }

    // FUNCION DIBUJAR CUADRO
    void dibujarCuadro(int x1, int y1, int x2, int y2)
    {

        int i;
        for (i = x1; i < x2; i++)
        {
            gotoxy(i, y1);
            printf("-"); // linea horizontal superior
            gotoxy(i, y2);
            printf("-"); // linea horizontal inferior
        }

        for (i = y1; i < y2; i++)
        {
            gotoxy(x1, i);
            printf("|"); // linea vertical izquierda
            gotoxy(x2, i);
            printf("|"); // linea vertical derecha
        }
        gotoxy(x1, y1);
        printf("|");
        gotoxy(x1, y2);
        printf("|");
        gotoxy(x2, y1);
        printf("|");
        gotoxy(x2, y2);
        printf("|");
    }

    // FUNCION LIMPIAR PANTALLA
    void limpia()
    {
        int i, j;
        for (i = 5; i <= 23; i++)
        {
            for (j = 3; j <= 76; j++)
            {
                gotoxy(j, i);
                printf(" ");
            }
        }
    }

    // FUNCION PARA OCULTAR EL CURSOR
    void CursorOff()
    {
        CONSOLE_CURSOR_INFO cursor = {1, FALSE};
        SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
    }
    // FUNCION PARA APARECER EL CURSOR
    void CursorOn(bool visible, DWORD size) // set bool visible = 0 - invisible, bool visible = 1 - visible
    {
        if (size == 0)
        {
            size = 20; // default cursor size Changing to numbers from 1 to 20, decreases cursor width

            CONSOLE_CURSOR_INFO lpCursor;
            lpCursor.bVisible = visible;
            lpCursor.dwSize = size;
            SetConsoleCursorInfo(console, &lpCursor);
        }
    }