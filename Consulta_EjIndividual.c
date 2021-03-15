//programa en C para consultar los datos de la base de datos
//Incluir esta libreria para poder hacer las llamadas en shiva2.upc.es
//#include <my_global.h>
#include <mysql.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
int main(int argc, char **argv)
{
	MYSQL *conn;
	int err;
	//Parámetros para almacenar las consultas correctamente: 
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	char user[10];
	char consulta [80];
	//Conexion al servidor MYSQL 
	conn = mysql_init(NULL);
	if (conn==NULL) {
		printf ("Error al conectarse a la base de datos: %u %s\n", 
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	//inicializar la conexion
	conn = mysql_real_connect (conn, "localhost","root", "mysql", "EjIndividual",0, NULL, 0);
	if (conn==NULL) {
		printf ("Error al conectarse con la base de datos: %u %s\n", 
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	
	
		//Consulta individual: Dime cuál es la contraseña de X usuario registrado
		printf ("Introduce el nombre del jugador del que quieres saber su contraseña:\n"); 
		scanf ("%s", user);
		// construimos consulta SQL
		strcpy (consulta,"SELECT contraseña FROM JUGADORES WHERE usuario = '"); 
		strcat (consulta, user);
		strcat (consulta,"'");
		// hacemos la consulta 
		err=mysql_query (conn, consulta); 
		if (err!=0) {
			printf ("Error al consultar datos de la base %u %s\n",
					mysql_errno(conn), mysql_error(conn));
			exit (1);
		}
		//recogemos el resultado de la consulta 
		resultado = mysql_store_result (conn); 
		row = mysql_fetch_row (resultado);
		if (row == NULL)
			printf ("No existe ningún jugador registrado con ese nombre de usuario\n");
		else
			printf ("La contraseña de ese usuario es: %s\n", row[0] );
		// cerrar la conexion con el servidor MYSQL 
		mysql_close (conn);
		exit(0);
}


