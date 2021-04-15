# 42sh
**42sh** is a Unix shell with:<br />
* Redirection and aggregation operators<br />
* cd, echo, exit, and type built-ins<br />
* '&&' and '||' logical operators<br />
* Internal and environmental variable handling<<br />
* Job control monitoring, with built-ins 'jobs', 'fg', 'bg', and the '&' operator<br />
* Signal handling<br />
* Complete management of history including expansions, 'fc' builtin and reverse search<br />
* Complete managament of quotes, double quotes and inhibitors<br />
* Parameter expansion: ${}<br />
* Arithmetic expansion : $(())<br />
* Alias management via built-ins 'alias' and 'unalias'<br />
* Hash table via built-in 'hash'<br />

### Usage
Repository contains a Makefile for:<br /> 
* compiling executable (**make all**)<br />
* removing object files (**make clean**)<br />
* deleting executable (**make fclean**)<br />
* recompiling (**make re**)<br />

#### Notes:
This project was done together with [dthan](https://github.com/xopxop), [ihwang](https://github.com/ihwang) and [VictoriaElisabet](https://github.com/VictoriaElisabet) and is part of my studies at Hive Helsinki.<br />
My part of the code handles the history, arithmetic expansion and line edition of user input. <br />
This project was thoroughly tested by 5 fellow Hive students.
