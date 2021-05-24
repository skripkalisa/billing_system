# Биллинговая база оператора связи
## NB! 
Для хранения и обработки данных используется SQLite3. Для успешной компиляции кода необходимо установить пакет 
https://www.sqlite.org/download.html#amalgtarball
Для успешной сборки программы необходимо указать ключи -lm -lsqlite3, например: 
gcc -g /path/to/file/pz2.c -o /path/to/file/pz2 -lm -lsqlite3 
