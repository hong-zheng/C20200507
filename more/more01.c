/*
 * more01.c -version 0.1 of more
 * read and print 24 lines then pause for a few special commands
 */
#include <stdio.h>
#include <stdlib.h>
#define PAGELEN 24
#define LINELEN 512
void do_more( FILE* );
int see_more();
int main( int ac , char *av[]){
	FILE* fp ;
	if( ac == 1)
		do_more( stdin);
	else
		while( --ac )
			if( (fp = fopen( *++av , "r") ) != NULL ){
				do_more( fp );
				fclose( fp );
			}else
				exit( 1 );
			
	return 0;
}

void do_more( FILE* fp)
/*
 * read PAGELEN lines,then call see_more() for further instructions
 */
{
 	// LINELEN 每一页为 24 行
 	// LINELEN 一行的数量
	char line[LINELEN] ;
	int num_of_lines = 0 ;
	int see_more() , reply ;
// 每一次读取一行数据 当读取到 n-1 或者 EOF 会结束
	while( fgets( line , LINELEN , fp ) ){		// more input
		if( num_of_lines == PAGELEN){		// full screen ?
			reply = see_more() ;		// y : ask user ?
			if( reply == 0 )
				break ;
			num_of_lines -= reply ;		// reset count
		}
		if( fputs( line , stdout ) == EOF){
			exit(1);
		}
		num_of_lines++;
	}
}

int see_more()
/*
 * print message , wait for response , return # of lines to advance
 * q means no , space means yes , CR means one line
 */
{
	int c ; 
/*
 * VT100终端定义
 * 	VT100是一个终端类型定义，VT100控制码是用来在终端显示的代码，比如在终端上任意坐标用不同的颜色显示字符
 * 	其中所有的控制符都是以"\033"开头（ 即ESC的ASCII码）
 *	用输出字符语句来输出。可以在命令行中用echo输出，也可以在C程序中的printf函数输出VT100控制字符
 *	例如：
 *		echo -e "\033[41;36m something here \033[0m"
 *		41 ：代表底色
 *		36 ：代表字色
 */
	printf( "\033[7m more ? \033[m");		// reverse on a vt100
	while( ( c = getchar() ) != EOF ){ 		// get response
		if( c == 'q' )				// q -> N
			return 0;
		if( c == ' ' )				//' ' -> next page
			return PAGELEN ;
		if( c == '\n' )				// Enter key -> 1 line
			return 1 ;
	}
	return 0;
}

