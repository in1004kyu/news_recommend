#include "../d2vlib/d2v.h"
#include <stdlib.h>
#include <stdio.h>
#include "/usr/include/mysql/mysql.h"
int main(){
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char *server = "203.246.112.177";                            //혹은 ip
	char *user = "guest";
	char *password = "guest";
	char *database = "article";
	int row_count;
	int i = 0;
	FILE *out;
	char filePath[40];
	char filename[28] = "../../example/incoming/test";
	char filetype[5] = ".txt";
	
	if( !(conn = mysql_init((MYSQL*)NULL))){        //초기화 함수
		printf("init fail\n");
		exit(1);
	}
	printf("mysql_init sucsess.\n");
	if(!mysql_real_connect(conn, server, user, password, NULL, 3306, NULL, 0)){
		printf("connect error.\n");     //DB접속 (MYSQL*, host, id, pw, null, port, 0)
		exit(1);
	}
	printf("mysql_real_connect suc.\n");
	if(mysql_select_db(conn, database) != 0){
		mysql_close(conn);
		printf("select_db fail.\n");
		exit(1);
	}
	printf("select mydb suc.\n");

	//printf("%d", mysql_query(conn,"select * from testtab" ));   //성공시 0리턴 (false)
	mysql_query(conn, "set names utf8");
//	mysql_query(conn, "set names euckr");

//	if(mysql_query(conn,"select content from news limit 1, 1" )){
	if(mysql_query(conn,"select content from news" )){
		printf("query fail\n");
		exit(1);
	}
	printf("query sucsess\n");
	res = mysql_store_result(conn);                 //쿼리에 대한 결과를 row에 저장
	row_count = (int)mysql_num_rows(res);
	printf("%d res suceese\n", row_count);
	
	
	
	while( (row=mysql_fetch_row(res))!=NULL){
		sprintf(filePath, "%s%d%s", filename, i, filetype);
		i++;
//		printf("%s\n", row[0]);       //이전과 같이 디비테이블을 만들었다면 id와 패스워드값이 나온다.
		out = fopen(filePath, "w");
		fprintf(out, "%s", row[0]);
		fclose(out);
	}
	mysql_free_result(res);
	mysql_close(conn);	
return 0;
}

