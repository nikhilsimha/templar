// define a grammar called Hello
grammar Hello;

struct : 's';
r   : 'hello' ID;
ID  : [a-z]+ ;
WS  : [ \t\r\n]+ -> skip ;

