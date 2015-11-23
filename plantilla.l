                 /*----- Sección de Declaraciones --------------*/ 
%{
#include <stdio.h>
int nlin=1;

%}
bibliotecas	"#include".+(\"|">")
DefCabeceras	{tipos}+.+"(".*");"
ImpCabeceras	{tipos}+.+"(".*")"[^;]
tipos		"int "|"float "|"char "|"long "|"short "|"signed "|"unsigned "|"double "|"void "|"unsigned "|"typedef "|"static "|"register "|"const "|"const "|"auto "|"extern "
mensajes	\".*\"
comentLin	"//"[^\n]*
int		[0-9]*
blancos		[ -/:-}]
comentMul	\/\*([^*]|[\r\n]|(\*+([^*/]|[\r\n])))*\*+\/
key		"if"|"endif"|"for"|"while"|"do "|"return"|"define"
null		"NULL"|"null"|"exit"

%%
                 /*----- Sección de Reglas ----------------*/ 
{blancos}			{printf("%s",yytext);}
\n				{nlin=nlin+1;printf("%s %d\t",yytext,nlin);}
{bibliotecas}			{fprintf(yyout, "%s\n",yytext);}
{DefCabeceras}			{;}
{ImpCabeceras}			{yyless(yyleng-1);fprintf(yyout,"%s;\n",yytext);printf("\033[0;32m%s",yytext);printf("\033[0;37m");}
{tipos}|{key}			{printf("\033[0;36m%s",yytext);printf("\033[0;37m");}
{mensajes}			{printf("\033[0;32m%s",yytext);printf("\033[0;37m");}
{null}				{printf("\033[0;31m%s",yytext);printf("\033[0;37m");}
{comentMul}|{comentLin}		{printf("\033[0;44m%s",yytext);printf("\033[0;37m");}
{int}				{printf("\033[0;33m%s",yytext);printf("\033[0;37m");}


%%   
                /*----- Sección de Procedimientos --------*/ 

int main (int argc, char *argv[])
{   
  if (argc == 3)   
  {     
    yyin = fopen (argv[1], "rt");     
    yyout = fopen (argv[2],"w");
    if (yyin == NULL)     
    {       
      printf ("El fichero %s de lectura no se puede abrir\n", argv[1]);       
      exit (-1);     
    }   
     
    if (yyout == NULL)     
    {       
      printf ("El fichero %s de escritura no se puede abrir\n", argv[2]);       
      exit (-1);
    }   
  }

  printf("\n");
  printf("\n 1\t");
  fprintf(yyout,"//Archivo .h generado \n");

  yylex (); 
  fclose(yyout);

  return 0; 
}
