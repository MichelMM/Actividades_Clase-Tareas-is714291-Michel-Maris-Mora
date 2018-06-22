//Directivas al preprocesador
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Variables Globales y nuevos tipos de datos

FILE * fcliente;
FILE * fcuentas;
FILE * ftransacciones;
int TF;
typedef enum {
	False = 0, True
} bool;
typedef struct {
	int dia;
	int mes;
	int anio;
} Fecha;
typedef struct {
	long ID_Usuario;
	char Nombre[50];
	char ApellidoP[50];
	char ApellidoM[50];
	Fecha FechaNacimiento;
} Usuario;
typedef struct {
	long ID_Cuenta, ID_Usuario, Saldo;
	Fecha FechaApertura;
} Cuenta;
typedef struct {
	long ID_Transaccion, ID_CuentaOrigen, ID_Cuenta_Destino, MontoTransaccion;
	char TipoTransaccion[15];
	Fecha FechaTransaccion;
} Transaccion;
//prototipos de funciones
char* RutaAcceso(FILE *);
void NuevoCliente(char *);
void ImprimirCliente(char *);
long BuscarCliente(char*, long);
bool ComprobarCliente(char*, long);
void EliminarCliente(char*, long, char *);
void NuevaCuenta(char *, char *);
void BuscarCuenta(char *, long);
void ImprimirCuentas(char *);
void EliminarCuenta(char*, long);
bool Deposito(char *, char *, long);
bool ModificarCuenta(char*, long, long);
bool Retiro(char *, char *, long);
bool Transferencia(char *, char *, long, long);
//Funci�n principal
int main() {
	//Configurando el buffer de salida
	setvbuf(stderr, NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);
	//char CL[]={"//Clientes.dat"};
	//char CU[]={"//Cuentas.dat"};
	//char TR[]={"//Transacciones.dat"};

	FILE *Comprobar;
	Comprobar = fopen("mydb.sys", "r");
	int O, Case;
	long B, I;
	char *Ruta = (char *) malloc(sizeof(char *) * 260);
	Ruta = RutaAcceso(Comprobar);

	char * DireccionCliente = (char *) malloc(sizeof(char *) * 260);
	char * DireccionCuentas = (char *) malloc(sizeof(char *) * 260);
	char * DireccionTransacciones = (char *) malloc(sizeof(char *) * 260);
	strcpy(DireccionCliente, Ruta);
	strcpy(DireccionCuentas, Ruta);
	strcpy(DireccionTransacciones, Ruta);
	strcat(DireccionCliente, "\\Clientes.dat");
	strcat(DireccionCuentas, "\\Cuentas.dat");
	strcat(DireccionTransacciones, "\\Transacciones.dat");
	long x = 0, y = 0, z = 0;
	if (TF == False) {
		fcliente = fopen(DireccionCliente, "wb");
		fwrite(&x, sizeof(long), 1, fcliente);
		fclose(fcliente);
		fcuentas = fopen(DireccionCuentas, "wb");
		fwrite(&y, sizeof(long), 1, fcuentas);
		fclose(fcuentas);
		ftransacciones = fopen(DireccionTransacciones, "wb");
		fwrite(&z, sizeof(long), 1, ftransacciones);
		fclose(ftransacciones);
	}

	//printf("%s\n",Ruta);

	do {
		printf(
				"<<Sistema MyBD>>\n[1]Clientes\n[2]Cuentas\n[3]Transacciones\n[4]Salir\n");
		scanf("%d", &O);
		switch (O) {
		case 1:
			printf(
					"Clientes\n[1]Nuevo Cliente\n[2]Buscar Cliente\n[3]Eliminar Cliente\n[4]Imprimir Clientes\n");
			scanf("%d", &Case);
			switch (Case) {
			case 1:
				NuevoCliente(DireccionCliente);
				break;
			case 2:
				printf("Ingrese el ID del usuario que desea buscar: ");
				scanf("%li", &B);
				I = BuscarCliente(DireccionCliente, B);
				break;
			case 3:
				printf(
						"Ingrese el ID del usuario que desea eliminar sus datos:");
				scanf("%li", &B);
				EliminarCliente(DireccionCliente, B, DireccionCuentas);
				break;
			case 4:
				ImprimirCliente(DireccionCliente);
				break;
			default:
				printf("Error, favor de escoger una opci�n valida\n");
			}
			break;
		case 2:
			printf(
					"Cuentas\n[1]Nueva Cuenta\n[2]Buscar Cuenta\n[3]Eliminar Cuenta\n[4]Imprimir Cuenta\n");
			scanf("%d", &Case);
			switch (Case) {
			case 1:
				NuevaCuenta(DireccionCuentas, DireccionCliente);
				break;
			case 2:
				printf("Ingrese el ID de la cuenta que desea buscar: ");
				scanf("%li", &B);
				BuscarCuenta(DireccionCuentas, B);
				break;
			case 3:
				printf("Ingrese el ID de la cuenta que desea eliminar: ");
				scanf("%li", &B);
				EliminarCuenta(DireccionCuentas, B);
				break;
			case 4:
				ImprimirCuentas(DireccionCuentas);
				break;
			default:
				printf("Error, favor de escoger una opci�n valida\n");
			}
			break;
		case 3:
			printf(
					"Transacciones\n[1]Dep�sitos\n[2]Retiro\n[3]Transferencia\n");
			scanf("%d", &Case);
			switch (Case) {
			case 1:
				printf(
						"Ingrese el ID de la cuenta en la que realizar� el dep�sito: ");
				scanf("%li", &B);
				Deposito(DireccionTransacciones, DireccionCuentas, B);
				break;
			case 2:
				printf(
						"Ingrese el ID de la cuenta en la que realizar� el retiro: ");
				scanf("%li", &B);
				Retiro(DireccionTransacciones, DireccionCuentas, B);
				break;
			case 3:
				printf("Ingrese el ID de la cuenta origen: ");
				scanf("%li", &B);
				printf("Ingrese el ID de la cuenta destino");
				scanf("%li", &I);
				Transferencia(DireccionTransacciones, DireccionCuentas, B, I);
				break;
			default:
				printf("Error, favor de escoger una opci�n valida\n");
			}
			break;
		default:
			if (O != 4)
				printf("Error, favor de escoger una opci�n valida\n");
		}
	} while (O != 4);

	return 0;
}
//Desarrollo de funciones
char* RutaAcceso(FILE *Comprobar) {
	char *Ruta = (char *) malloc(sizeof(char *) * 260);
	if (Comprobar != NULL) {
		fgets(Ruta, 260, Comprobar);
		fclose(Comprobar);
		TF = True;
		return Ruta;
	} else {
		fclose(Comprobar);
		Comprobar = fopen("mydb.sys", "w");
		printf(
				"Error al detectar el archivo, favor de ingresar la direccion en la que se encontraran sus archivos\n");
		//C:\Users\Michel\eclipse-workspace\Tarea-03PMD
		fflush(stdin);
		gets(Ruta);
		fputs(Ruta, Comprobar);
		fclose(Comprobar);
		TF = False;
		return Ruta;
	}
}
void NuevoCliente(char*DireccionCliente) {
	Usuario Cliente;
	long i;
	fcliente = fopen(DireccionCliente, "rb");
	fread(&i, sizeof(long), 1, fcliente);
	fclose(fcliente);
	fcliente = fopen(DireccionCliente, "a+b");
	printf("Nombre: ");
	fflush(stdin);
	gets(Cliente.Nombre);
	printf("Apellido Paterno: ");
	fflush(stdin);
	gets(Cliente.ApellidoP);
	printf("Apellido Materno: ");
	fflush(stdin);
	gets(Cliente.ApellidoM);
	printf("Fecha de nacimiento [dd/mm/aaaa]: ");
	scanf("%d/%d/%d", &Cliente.FechaNacimiento.dia,
			&Cliente.FechaNacimiento.mes, &Cliente.FechaNacimiento.anio);
	i++;
	Cliente.ID_Usuario = i;
	fwrite(&Cliente, sizeof(Usuario), 1, fcliente);
	fclose(fcliente);
	fcliente = fopen(DireccionCliente, "r+b");
	fwrite(&i, sizeof(long), 1, fcliente);
	fclose(fcliente);
}
long BuscarCliente(char*DireccionCliente, long ID) {
	long i;
	Usuario Buscar;
	fcliente = fopen(DireccionCliente, "rb");
	fread(&i, sizeof(long), 1, fcliente);
	printf("%li\n", i);
	do {
		fread(&Buscar, sizeof(Usuario), 1, fcliente);
		//printf("%li\n",Buscar.ID_Usuario);
		if (Buscar.ID_Usuario >= i) {
			break;
		}

	} while (Buscar.ID_Usuario != ID);
	//printf("%li",Buscar.ID_Usuario);
	if (ID <= i && ID > 0) {
		printf("%li %s %s %s {%d/%d/%d}\n", Buscar.ID_Usuario, Buscar.Nombre,
				Buscar.ApellidoP, Buscar.ApellidoM, Buscar.FechaNacimiento.dia,
				Buscar.FechaNacimiento.mes, Buscar.FechaNacimiento.anio);
		fclose(fcliente);
		return ID;
	} else {
		printf("Error, el id buscado no existe\n");
		fclose(fcliente);
		return 0;
	}
}
bool ComprobarCliente(char* DireccionCliente, long ID) {
	long i;
	Usuario Comprobar;
	fcliente = fopen(DireccionCliente, "rb");
	fread(&i, sizeof(long), 1, fcliente);
	//printf("%li\n",i);
	//printf("%li \n",i);
	do {
		fread(&Comprobar, sizeof(Usuario), 1, fcliente);
		//printf("%li %s %s %s {%d/%d/%d}\n", Comprobar.ID_Usuario, Comprobar.Nombre,Comprobar.ApellidoP, Comprobar.ApellidoM,Comprobar.FechaNacimiento.dia, Comprobar.FechaNacimiento.mes,Comprobar.FechaNacimiento.anio);
		//printf("%li\n",Comprobar.ID_Usuario);
		if (Comprobar.ID_Usuario >= i)
			break;
	} while (Comprobar.ID_Usuario != ID);
	fclose(fcliente);
	if (ID <= i && ID > 0) {
		//printf("%li \n",I);
		return True;
	} else {
		//printf("%li \n",I);
		return False;
	}
}
void EliminarCliente(char* DireccionCliente, long ID, char * DireccionCuentas) {
	long i, j = 0, icuentas = 0;
	fcuentas = fopen(DireccionCuentas, "rb");
	fread(&i, sizeof(long), 1, fcuentas);
	Cuenta cuentas[i];
	fclose(fcuentas);
	fcliente = fopen(DireccionCliente, "rb");
	fread(&i, sizeof(long), 1, fcliente);
	//printf("%li\n",i);
	//Usuario *Clientes=(Usuario *)malloc(sizeof(Usuario)*i);
	Usuario Clientes[i];
	Usuario Cliente;
	Cuenta cuenta;
	while (fread(&Cliente, sizeof(Usuario), 1, fcliente)) {
		Clientes[j].ID_Usuario = Cliente.ID_Usuario;
		strcpy(Clientes[j].Nombre, Cliente.Nombre);
		strcpy(Clientes[j].ApellidoP, Cliente.ApellidoP);
		strcpy(Clientes[j].ApellidoM, Cliente.ApellidoM);
		Clientes[j].FechaNacimiento.dia = Cliente.FechaNacimiento.dia;
		Clientes[j].FechaNacimiento.mes = Cliente.FechaNacimiento.mes;
		Clientes[j].FechaNacimiento.anio = Cliente.FechaNacimiento.anio;
		j++;
	}
	for (int k = 0; k < j; k++) {
		if (Clientes[k].ID_Usuario == ID) {
			Clientes[k].ID_Usuario = 0;
		}
	}
	fclose(fcliente);
	fcuentas = fopen(DireccionCuentas, "rb");
	fread(&icuentas, sizeof(long), 1, fcuentas);
	long l = 0;
	while (fread(&cuenta, sizeof(Cuenta), 1, fcuentas)) {
		//printf("ID: %li\n", cuenta.Saldo);
		if (cuenta.ID_Usuario == ID) {
			//printf("%li %li\n", cuenta.ID_Cuenta,l);
			cuentas[l].ID_Cuenta = cuenta.ID_Cuenta;
			l++;
		}
		//EliminarCuenta(DireccionCuentas, cuentas.ID_Usuario);
	}
	//printf("%li",j);
	fclose(fcuentas);
	for (int k = 0; k < l; k++) {
		printf("Hola\n");
		EliminarCuenta(DireccionCuentas, cuentas[k].ID_Cuenta);
	}
	fcliente = fopen(DireccionCliente, "wb");
	fwrite(&i, sizeof(long), 1, fcliente);
	for (int k = 0; k < j; k++) {
		Cliente.ID_Usuario = Clientes[k].ID_Usuario;
		strcpy(Cliente.Nombre, Clientes[k].Nombre);
		strcpy(Cliente.ApellidoP, Clientes[k].ApellidoP);
		strcpy(Cliente.ApellidoM, Clientes[k].ApellidoM);
		Cliente.FechaNacimiento.dia = Clientes[k].FechaNacimiento.dia;
		Cliente.FechaNacimiento.mes = Clientes[k].FechaNacimiento.mes;
		Cliente.FechaNacimiento.anio = Clientes[k].FechaNacimiento.anio;
		//printf("%li\n", Clientes[k].ID_Usuario);
		if (Clientes[k].ID_Usuario != 0)
			fwrite(&Cliente, sizeof(Usuario), 1, fcliente);
	}
	fclose(fcliente);
}
void ImprimirCliente(char*DireccionCliente) {
	fcliente = fopen(DireccionCliente, "rb");
	Usuario Cliente;
	long i;
	fread(&i, sizeof(long), 1, fcliente);
	printf("%li\n", i);
	printf("ID Usuario-Nombre-Fecha Nacimiento\n");
	/*while(!feof(fcliente))*/while (fread(&Cliente, sizeof(Usuario), 1,
			fcliente)) {
		//fread(&Cliente,sizeof(Usuario),1,fcliente);
		printf("%li-%s %s %s-{%d/%d/%d}\n", Cliente.ID_Usuario, Cliente.Nombre,
				Cliente.ApellidoP, Cliente.ApellidoM,
				Cliente.FechaNacimiento.dia, Cliente.FechaNacimiento.mes,
				Cliente.FechaNacimiento.anio);
	}
	fclose(fcliente);
}
void NuevaCuenta(char *DireccionCuentas, char *DireccionCliente) {
	Cuenta cuenta;
	long i, IDU = 0;
	fcuentas = fopen(DireccionCuentas, "rb");
	fread(&i, sizeof(long), 1, fcuentas);
	fclose(fcuentas);
	while (!IDU) {
		printf("ID del usuario: ");
		scanf("%li", &cuenta.ID_Usuario);
		IDU = cuenta.ID_Usuario;
		IDU = ComprobarCliente(DireccionCliente, IDU);
		if (IDU == False) {
			printf("Error, Cliente no existente\n");
		}
	}
	printf("Saldo: ");
	scanf("%li", &cuenta.Saldo);
	printf("Fecha de apertura [dd/mm/aaaa]: ");
	scanf("%d/%d/%d", &cuenta.FechaApertura.dia, &cuenta.FechaApertura.mes,
			&cuenta.FechaApertura.anio);
	i++;

	cuenta.ID_Cuenta = i;
	fcuentas = fopen(DireccionCuentas, "a+b");
	fwrite(&cuenta, sizeof(Cuenta), 1, fcuentas);
	fclose(fcuentas);
	fcuentas = fopen(DireccionCuentas, "r+b");
	fwrite(&i, sizeof(long), 1, fcuentas);
	fclose(fcuentas);

}
void BuscarCuenta(char *DireccionCuentas, long ID) {
	long i;
	Cuenta Buscar;
	fcuentas = fopen(DireccionCuentas, "rb");
	fread(&i, sizeof(long), 1, fcuentas);
	//printf("%li\n",i);
	do {
		fread(&Buscar, sizeof(Cuenta), 1, fcuentas);
		if (Buscar.ID_Cuenta >= i)
			break;
	} while (Buscar.ID_Cuenta != ID);
	//printf("%li",Buscar.ID_Usuario);
	if (ID <= i && ID >= 0) {
		printf("%li %li $ %li {%d/%d/%d}\n", Buscar.ID_Cuenta,
				Buscar.ID_Usuario, Buscar.Saldo, Buscar.FechaApertura.dia,
				Buscar.FechaApertura.mes, Buscar.FechaApertura.anio);
		fclose(fcuentas);
	} else {
		printf("Error, el id buscado no existe\n");
		fclose(fcuentas);
	}
}
void ImprimirCuentas(char*DireccionCuentas) {
	fcuentas = fopen(DireccionCuentas, "rb");
	Cuenta Imprimir;
	long i;
	fread(&i, sizeof(long), 1, fcuentas);
	printf("%li\n", i);
	printf("ID Cuenta-ID Usuario-ID Saldo-Fecha Apertura\n");
	/*while(!feof(fcliente))*/while (fread(&Imprimir, sizeof(Cuenta), 1,
			fcuentas)) {
		//fread(&Cliente,sizeof(Usuario),1,fcliente);
		printf("%li-%li-$%li-{%d/%d/%d}\n", Imprimir.ID_Cuenta,
				Imprimir.ID_Usuario, Imprimir.Saldo, Imprimir.FechaApertura.dia,
				Imprimir.FechaApertura.mes, Imprimir.FechaApertura.anio);
	}
	fclose(fcuentas);
}
void EliminarCuenta(char* DireccionesCuentas, long ID) {
	long i, j = 0;
	fcuentas = fopen(DireccionesCuentas, "rb");
	fread(&i, sizeof(long), 1, fcuentas);
	//printf("%li\n",i);
	//Usuario *Clientes=(Usuario *)malloc(sizeof(Usuario)*i);
	Cuenta cuentas[i];
	Cuenta cuenta;
	while (fread(&cuenta, sizeof(Cuenta), 1, fcuentas)) {
		cuentas[j].ID_Cuenta = cuenta.ID_Cuenta;
		cuentas[j].ID_Usuario = cuenta.ID_Usuario;
		cuentas[j].Saldo = cuenta.Saldo;
		cuentas[j].FechaApertura.dia = cuenta.FechaApertura.dia;
		cuentas[j].FechaApertura.mes = cuenta.FechaApertura.mes;
		cuentas[j].FechaApertura.anio = cuenta.FechaApertura.anio;
		j++;
	}
	for (int k = 0; k < j; k++) {
		if (cuentas[k].ID_Cuenta == ID) {
			cuentas[k].ID_Cuenta = 0;
		}
	}
	//printf("%li",j);
	fclose(fcuentas);
	fcuentas = fopen(DireccionesCuentas, "wb");
	fwrite(&i, sizeof(long), 1, fcuentas);
	for (int k = 0; k < j; k++) {
		cuenta.ID_Cuenta = cuentas[k].ID_Cuenta;
		cuenta.ID_Usuario = cuentas[k].ID_Usuario;
		cuenta.Saldo = cuentas[k].Saldo;
		cuenta.FechaApertura.dia = cuentas[k].FechaApertura.dia;
		cuenta.FechaApertura.mes = cuentas[k].FechaApertura.mes;
		cuenta.FechaApertura.anio = cuentas[k].FechaApertura.anio;
		//printf("%li\n", Clientes[k].ID_Usuario);
		if (cuentas[k].ID_Cuenta != 0)
			fwrite(&cuenta, sizeof(Cuenta), 1, fcuentas);
	}
	fclose(fcuentas);
}
bool Deposito(char *DireccionTransacciones, char *DireccionCuentas, long ID) {
	Cuenta Verifica;
	Transaccion Tr;
	long i,j,V=0;
	ftransacciones = fopen(DireccionTransacciones, "rb");
	fread(&i, sizeof(long), 1, ftransacciones);
	fclose(fcliente);
	fcuentas=fopen(DireccionCuentas,"rb");
	fread(&j,sizeof(long),1,fcuentas);
	while(fread(&Verifica,sizeof(Cuenta),1,fcuentas)){
		if(Verifica.ID_Cuenta==ID)
			V++;
	}
	if(V==0){
		printf("El ID de cuenta ingresado es erroneo\n");
		return False;
	}
	fclose(fcuentas);
	strcpy(Tr.TipoTransaccion, "Dep�sito");
	Tr.ID_CuentaOrigen = ID;
	Tr.ID_Cuenta_Destino = (long) NULL;
	printf("Ingrese el monto de la transacci�n: ");
	scanf("%li", &Tr.MontoTransaccion);
	printf("Ingrese la fecha en la que se realiz� el dep�sito [dd/mm/aaaa]: ");
	scanf("%d/%d/%d", &Tr.FechaTransaccion.dia, &Tr.FechaTransaccion.mes,
			&Tr.FechaTransaccion.anio);
	i++;
	Tr.ID_Transaccion = i;
	ftransacciones = fopen(DireccionTransacciones, "a+b");
	fwrite(&Tr, sizeof(Transaccion), 1, ftransacciones);
	fclose(ftransacciones);
	ftransacciones = fopen(DireccionTransacciones, "r+b");
	fwrite(&i, sizeof(long), 1, ftransacciones);
	fclose(ftransacciones);
	ModificarCuenta(DireccionCuentas, ID, Tr.MontoTransaccion);
	return True;
}
bool ModificarCuenta(char* DireccionCuentas, long ID, long Monto) {
	long i, j = 0;
	fcuentas = fopen(DireccionCuentas, "rb");
	fread(&i, sizeof(long), 1, fcuentas);
	//printf("%li\n",i);
	//Usuario *Clientes=(Usuario *)malloc(sizeof(Usuario)*i);
	Cuenta cuentas[i];
	Cuenta cuenta;
	while (fread(&cuenta, sizeof(Cuenta), 1, fcuentas)) {
		cuentas[j].ID_Cuenta = cuenta.ID_Cuenta;
		cuentas[j].ID_Usuario = cuenta.ID_Usuario;
		cuentas[j].Saldo = cuenta.Saldo;
		cuentas[j].FechaApertura.dia = cuenta.FechaApertura.dia;
		cuentas[j].FechaApertura.mes = cuenta.FechaApertura.mes;
		cuentas[j].FechaApertura.anio = cuenta.FechaApertura.anio;
		j++;
	}
	for (int k = 0; k < j; k++) {
		if (cuentas[k].ID_Cuenta == ID) {
			if (cuentas[k].Saldo + Monto < 0)
				return False;
			else
				cuentas[k].Saldo += Monto;
		}
	}
	//printf("%li",j);
	fclose(fcuentas);
	fcuentas = fopen(DireccionCuentas, "wb");
	fwrite(&i, sizeof(long), 1, fcuentas);
	for (int k = 0; k < j; k++) {
		cuenta.ID_Cuenta = cuentas[k].ID_Cuenta;
		cuenta.ID_Usuario = cuentas[k].ID_Usuario;
		cuenta.Saldo = cuentas[k].Saldo;
		cuenta.FechaApertura.dia = cuentas[k].FechaApertura.dia;
		cuenta.FechaApertura.mes = cuentas[k].FechaApertura.mes;
		cuenta.FechaApertura.anio = cuentas[k].FechaApertura.anio;
		//printf("%li\n", Clientes[k].ID_Usuario);
		fwrite(&cuenta, sizeof(Cuenta), 1, fcuentas);
	}
	fclose(fcuentas);
	return True;
}
bool Retiro(char *DireccionTransacciones, char *DireccionCuentas, long ID) {
	Transaccion Tr;
	Cuenta Verifica;
	long i,j,V=0;
	int TrFl = 1;
	ftransacciones = fopen(DireccionTransacciones, "rb");
	fread(&i, sizeof(long), 1, ftransacciones);
	fclose(fcliente);
	fcuentas=fopen(DireccionCuentas,"rb");
		fread(&j,sizeof(long),1,fcuentas);
		while(fread(&Verifica,sizeof(Cuenta),1,fcuentas)){
			if(Verifica.ID_Cuenta==ID)
				V++;
		}
		if(V==0){
			printf("El ID de cuenta ingresado es erroneo\n");
			return False;
		}

	strcpy(Tr.TipoTransaccion, "Retiro");
	Tr.ID_CuentaOrigen = ID;
	Tr.ID_Cuenta_Destino = (long) NULL;
	CR: printf("Ingrese el monto a retirar: ");
	scanf("%li", &Tr.MontoTransaccion);
	Tr.MontoTransaccion *= -1;
	TrFl = ModificarCuenta(DireccionCuentas, ID, Tr.MontoTransaccion);
	if (TrFl == False) {
		printf(
				"Error, el monto seleccionado sobrepasa el retiro que se puede realizar");
		goto CR;
	}
	printf("Ingrese la fecha en la que se realiz� el Retiro [dd/mm/aaaa]: ");
	scanf("%d/%d/%d", &Tr.FechaTransaccion.dia, &Tr.FechaTransaccion.mes,
			&Tr.FechaTransaccion.anio);
	i++;
	Tr.ID_Transaccion = i;
	ftransacciones = fopen(DireccionTransacciones, "a+b");
	fwrite(&Tr, sizeof(Transaccion), 1, ftransacciones);
	fclose(ftransacciones);
	ftransacciones = fopen(DireccionTransacciones, "r+b");
	fwrite(&i, sizeof(long), 1, ftransacciones);
	fclose(ftransacciones);
	return True;
}
bool Transferencia(char *DireccionTransacciones, char *DireccionCuentas,
		long IDOrigen, long IDDestino) {
	Cuenta Verifica;
	Transaccion Tr;
	long i,j,V=0;
	int TrFl = 1;
	ftransacciones = fopen(DireccionTransacciones, "rb");
	fread(&i, sizeof(long), 1, ftransacciones);
	fclose(fcliente);
	fcuentas=fopen(DireccionCuentas,"rb");
		fread(&j,sizeof(long),1,fcuentas);
		while(fread(&Verifica,sizeof(Cuenta),1,fcuentas)){
			if(Verifica.ID_Cuenta==IDOrigen || Verifica.ID_Cuenta==IDDestino)
				V++;
		}
		if(V==0){
			printf("El ID de cuenta ingresado es erroneo\n");
			return False;
		}


	strcpy(Tr.TipoTransaccion, "Transferencia");
	Tr.ID_CuentaOrigen = IDOrigen;
	Tr.ID_Cuenta_Destino = IDDestino;
	CR: printf("Ingrese el monto a que ser� transferido: ");
	scanf("%li", &Tr.MontoTransaccion);
	Tr.MontoTransaccion *= -1;
	TrFl = ModificarCuenta(DireccionCuentas, IDOrigen, Tr.MontoTransaccion);
	if (TrFl == False) {
		printf(
				"Error, el monto seleccionado sobrepasa el retiro que se puede realizar");
		goto CR;
	}
	Tr.MontoTransaccion *= -1;
	TrFl = ModificarCuenta(DireccionCuentas, IDDestino, Tr.MontoTransaccion);
	printf("Ingrese la fecha en la que se realiz� el Retiro [dd/mm/aaaa]: ");
	scanf("%d/%d/%d", &Tr.FechaTransaccion.dia, &Tr.FechaTransaccion.mes,
			&Tr.FechaTransaccion.anio);
	i++;
	Tr.ID_Transaccion = i;
	ftransacciones = fopen(DireccionTransacciones, "a+b");
	fwrite(&Tr, sizeof(Transaccion), 1, ftransacciones);
	fclose(ftransacciones);
	ftransacciones = fopen(DireccionTransacciones, "r+b");
	fwrite(&i, sizeof(long), 1, ftransacciones);
	fclose(ftransacciones);
	return True;
}
