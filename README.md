# OSiSP BSUIR
# Лабораторная работа 1
1. Изучить теоретическую часть лабораторной работы.
2. Написать программу ввода символов с клавиатуры и записи их в файл (в качестве аргумента при запуске программы вводится имя файла). Для чтения или записи файла использовать функции посимвольного ввода-вывода getc(),putc() или им подобные. Предусмотреть выход после ввода определённого символа (например: ctrl-F). После запуска и отработки программы просмотреть файл. Предусмотреть контроль ошибок открытия/закрытия/чтения файла.
3. Написать программу просмотра текстового файла и вывода его содержимого на экран (в качестве аргумента при запуске программы передаётся имя файла, второй аргумент (N) устанавливает вывод по группам строк (по N –строк) или сплошным текстом (N=0)). Для чтения или записи файла использовать функции посимвольного ввода-вывода getc(),putc() или им подобные.  Предусмотреть контроль ошибок открытия/закрытия/чтения/записи файла.
4. Написать программу копирования одного файла в другой. В качестве параметров при вызове программы передаются имена первого и второго файлов. Для чтения или записи файла использовать функции посимвольного ввода-вывода getc(),putc() или им подобные.  Предусмотреть копирование  прав доступа к файлу и контроль ошибок открытия/закрытия/чтения/записи файла.
5. Написать программу вывода на экран содержимого текущего каталога.
Вывести с использованием данной программы содержимое корневого каталога. Предусмотреть контроль ошибок открытия/закрытия/чтения каталога.
6. Написать программу подсчёта числа отображаемых символов в строках текстового файла и формирование из полученных значений другого текстового файла, в котором будут расположены строки, каждая из которых представляет собой символьное изображение числа символов в данной строке из первого файла. Для чтения или записи файла использовать функции посимвольного ввода-вывода getc(),putc() или им подобные.  Имена файлов передаются в программу в качестве аргументов. Пример вывода программы для текстового файла: 
QWER
REEEt
WEEEEEEERSIIIONN
Файл, полученный в результате работы программы:
  - 4 
  - 5 
  - 16 
итого: 3 строки 25 символов
7. Написать программу поиска заданного пользователем файла в текущем каталоге. Предусмотреть контроль ошибок.
8. Написать программу сравнения двух заданных  пользователем файлов по их содержимому. Предусмотреть контроль ошибок.
9. Написать программу сравнения двух заданных пользователем каталогов.
Предусмотреть контроль ошибок.

# Лабораторная работа 4
1. Изучить теоретическую часть лабораторной работы.
2. Организовать функционирование процессов следующей структуры Отец -> Сын 1 и Отец -> Сын 2
Процессы определяют свою работу выводом сообщений вида : N pid (N – текущий номер сообщения) на экран. “Отец” периодически, по очереди, посылает сигнал SIGUSR1 “сыновьям”. “Сыновья” периодически посылают сигнал SIGUSR2 “отцу”. Написать функции-обработчики сигналов, которые при получении сигнала выводят сообщение о получении сигнала на экран. При получении/посылке сигнала они выводят соответствующее сообщение: N pid  сын n get/put SIGUSRm.
Предусмотреть механизм для определения “отцом”, от кого из “сыновей” получен сигнал.
3. Для процессов написать функции-обработчики сигналов от клавиатуры, которые запрашивали бы подтверждение на завершение работы при получении такого сигнала.

# Лабораторная работа 5
1. Изучить теоретическую часть лабораторной работы.
2. Организовать взаимодействие процессов следующей структуры:
Процесс "ответ" <-> N-ое количество процессов "вопрос"
Процессы «вопрос»(ы) посылают запросы процессу «ответ» по неименованным каналам и получают по ним ответы. Должны быть предусмотрены типы ответов, которые инициируют завершение процессов «вопрос», а также должны быть вопросы, которые инициируют порождение новых процессов.
3. Организовать взаимодействие процессов следующей структуры:
Процесс "управление" <-> N-ое количество процессов процесс "работник", которые также связаны и между собой.
Процессы «работники» по неименованным каналам обмениваются между собой данными. Неименованные каналы существуют также между процессом «Управление» и процессами «работниками». Процесс «Управление» инициирует завершение процессов «работников».
