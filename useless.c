/*
Программу написал Силкин Владимир под стандартной лицензией 553 группы.
Из командной строки программу запускаем так: "gcc useless.c -o useless && useless a 2 b 6".
Это значит, что программа "a" запустится через 2 секунды, а программы "b"
черз 6 секунд. Вы можете написать свое время и свои программы в секундах.
*/

#include <stdio.h>
#include <unistd.h> // здесь exec()
#include <string.h> // здесь strerror()
#include <errno.h>  // здесь errno
#include <stdlib.h> // здесь exit()
#include <math.h> // здесь abs()

#include <sys/wait.h> // здесь waitpid()

//Код для обработки ошибок.
void error(char *msg)
{
	fprintf(stderr, "%s: %s\n", msg, strerror(errno)); // strerror преобразует код ошибки в сообщение
	exit(1);
}


int main(int argc, char *argv[]) //в функцию передаем массив строк
{
	char *name_of_program = argv[1]; 	//передаем имя 1 программы
	char *t = argv[2];					//передаем время до запуска 1 программы
	char *name_of_program1 = argv[3];	//передаем имя 2 программы
	char *t1 = argv[4];					//передаем время до запуска 2 программы 

		char cmd[120];	//в сmd будем записывать команды для терминала
		char cmd1[120];
		char cmdd[120];

			sprintf(cmd, "sleep %s", t);  				//печатаем в массив cmd время t
			sprintf(cmd1, "sleep %s", t1);
			sprintf(cmdd, "sleep %d", abs(atoi(t)-atoi(t1)));//сюда запишем разницу времен (difference)


	pid_t pid = fork();



//код выполняется в дочернем процессе
	if(pid==0){
		if(atoi(t)>atoi(t1)){
			system(cmd1);

		if(execl(name_of_program1, name_of_program1, NULL)==-1){
			error("Прости, не могу запустить программу");
			}
		}

		else{
			system(cmd);

		if(execl(name_of_program, name_of_program, NULL)==-1){
			error("Прости, не могу запустить программу");
			}
		}
	}



	int pid_status;
	if(waitpid(pid, &pid_status, 0)==-1){ 	/*функция waitpid не вернет значения, 
												пока не завершится дочерний процесс */
		error("Грустно. Ошибка во время ожидания дочернего процесса");
	}


	system(cmdd); //ждем...

	if(atoi(t)>atoi(t1)){
		if(execl(name_of_program, name_of_program, NULL)==-1)
			error("Прости, не могу запустить программу");
	}
	else{	
		if(execl(name_of_program1, name_of_program1, NULL)==-1)
			error("Прости, не могу запустить программу");
	}	
}